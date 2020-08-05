/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 11:25:14 by user42            #+#    #+#             */
/*   Updated: 2020/08/05 23:32:21 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_two.h>

static int	init_params(t_p2 *p)
{
	int			i;

	if ((p->isdying = sem_open("isdying", O_CREAT, 777, 1)) == SEM_FAILED)
		return (-1);
	if ((p->forks = sem_open("forks", O_CREAT, 777, p->nb)) == SEM_FAILED)
		return (-1);
	sem_unlink("isdying");
	sem_unlink("forks");
	p->someonedied = 0;
	p->someonefull = 0;
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
	if ((p->threads = malloc(sizeof(pthread_t) * p->nb)) == 0)
		return (-1);
	return (0);
}

int			init_threads(t_p2 *p)
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
		pthread_create(
					&p->threads[i], NULL, &a_philo, (void*)&p->params[i]);
		i += 2;
	}
	usleep(p->nb * 5000);
	i = 1;
	while (i < p->nb)
	{
		pthread_create(
					&p->threads[i], NULL, &a_philo, (void*)&p->params[i]);
		i += 2;
	}
	return (0);
}

void		free_params(t_p2 *p)
{
	sem_close(p->forks);
	sem_close(p->isdying);
	sem_close(p->print_sem);
	free(p->threads);
	free(p->params);
}
