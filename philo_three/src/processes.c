/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 11:25:14 by user42            #+#    #+#             */
/*   Updated: 2020/08/06 00:45:17 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_three.h>

static int	init_params(t_p3 *p)
{
	int			i;

	if ((p->isdying = sem_open("isdying", O_CREAT, 777, 1)) == SEM_FAILED)
		return (-1);
	if ((p->forks = sem_open("forks", O_CREAT, 777, p->nb)) == SEM_FAILED)
		return (-1);
	sem_unlink("isdying");
	sem_unlink("forks");
	p->isfull = 0;
	p->someonedied = 0;
	i = -1;
	if ((p->params = malloc(sizeof(t_params) * p->nb)) == 0)
		return (-1);
	while (++i < p->nb)
	{
		(&p->params[i])->id = i;
		(&p->params[i])->nbmeal = 0;
		(&p->params[i])->p = p;
		(&p->params[i])->last_eaten = 0;
	}
	if ((p->processes = malloc(sizeof(pid_t) * p->nb)) == 0)
		return (-1);
	return (0);
}

int			init_processes(t_p3 *p)
{
	int			i;

	if (init_params(p))
	{
		free_params(p);
		return (-1);
	}
	gettimeofday(&p->time_start, 0);
	p->timestampstart = get_timestamp(p);
	i = 0;
	while (i < p->nb)
	{
		p->processes[i] = fork();
		if (p->processes[i] == 0)
		{
			exit(a_philo(&p->params[i]));
		}
		else if (p->processes[i] == -1)
		{
			// panic
		}
		i++;
		usleep(5000);
	}
	return (0);
}

void	wait_processes(t_p3 *p)
{
	int i;
	int status;

	i = -1;
	while (++i < p->nb)
	{
		waitpid(-1, &status, 0);
		if (WEXITSTATUS(status) == IDIED)
		{
			i = -1;
			while (++i < p->nb)
				kill(p->processes[i], SIGINT);
			break ;
		}
	}
}

void		free_params(t_p3 *p)
{
	sem_close(p->forks);
	sem_close(p->isdying);
	sem_close(p->print_sem);
	free(p->processes);
	free(p->params);
}
