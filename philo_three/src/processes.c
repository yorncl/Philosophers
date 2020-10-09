/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 11:25:14 by user42            #+#    #+#             */
/*   Updated: 2020/10/08 11:21:01 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_three.h>

static void		init_params(void)
{
	int i;

	i = -1;
	while (++i < g_philo.nb_philo)
	{
		g_philo.params[i].id = i;
	}
}

static void		kill_processes(void)
{
	int i;
	int status;

	i = -1;
	while (++i < g_philo.nb_philo)
	{
		waitpid(-1, &status, 0);
		if (WEXITSTATUS(status) == EXIT_DIED)
		{
			i = -1;
			while (++i < g_philo.nb_philo)
				if (g_philo.philosophers[i])
					kill(g_philo.philosophers[i], SIGINT);
			break ;
		}
	}
}

static int		init_processes(void)
{
	int			i;

	gettimeofday(&g_philo.time_now, 0);
	g_philo.timestampstart = get_timestamp();
	i = -1;
	while (++i < g_philo.nb_philo)
	{
		if ((g_philo.philosophers[i] = fork()) == 0)
			a_philo(&g_philo.params[i]);
		else if (g_philo.philosophers[i] == -1)
		{
			kill_processes();
			return (1);
		}
		if (i == g_philo.nb_philo / 2)
			usleep(9000);
	}
	return (0);
}

void			launch_sim(void)
{
	init_params();
	if (init_processes())
	{
		write(2, "Error creating the processes\n", 29);
		return ;
	}
	kill_processes();
}
