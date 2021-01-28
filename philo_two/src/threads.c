/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yorn <yorn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 11:25:14 by user42            #+#    #+#             */
/*   Updated: 2021/01/28 14:34:04 by yorn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_two.h>

static void		init_params(void)
{
	int i;

	i = -1;
	while (++i < g_philo.nb_philo)
	{
		g_philo.params[i].id = i;
	}
}


#include <stdio.h>
static void		init_threads(void)
{
	int			i;

	gettimeofday(&g_philo.time_now, 0);
	g_philo.timestampstart = g_philo.time_now.tv_sec * 1000 + g_philo.time_now.tv_usec / 1000;
	i = 0;
	while (i < g_philo.nb_philo)
	{
		g_philo.params[i].last_eaten = g_philo.timestampstart;
		pthread_create(&g_philo.philosophers[i], NULL,
						&a_philo, (void*)&g_philo.params[i]);
		pthread_create(&g_philo.monitors[i], NULL,
				&a_monitor, (void*)&g_philo.params[i]);
		usleep(1000);
		i++;
	}
}

static void		join_threads(void)
{
	int i;

	i = -1;
	while (++i < g_philo.nb_philo)
	{
		pthread_join(g_philo.philosophers[i], 0);
		pthread_join(g_philo.monitors[i], 0);
	}
}

void			launch_sim(void)
{
	init_params();
	init_threads();
	join_threads();
}
