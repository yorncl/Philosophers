/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 11:25:14 by user42            #+#    #+#             */
/*   Updated: 2020/10/09 00:39:43 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_one.h>

static void		init_params(void)
{
	int i;

	i = -1;
	while (++i < g_philo.nb_philo)
	{
		g_philo.params[i].id = i;
	}
}

static void		init_threads(void)
{
	int			i;

	gettimeofday(&g_philo.time_now, 0);
	g_philo.timestampstart = get_timestamp();
	i = 0;
	while (i < g_philo.nb_philo)
	{
		pthread_create(&g_philo.philosophers[i], NULL,
						&a_philo, (void*)&g_philo.params[i]);
		pthread_create(&g_philo.monitors[i], NULL,
						&a_monitor, (void*)&g_philo.params[i]);
		i += 2;
	}
	usleep(g_philo.nb_philo * 5000);
	i = 1;
	while (i < g_philo.nb_philo)
	{
		pthread_create(&g_philo.philosophers[i], NULL,
						&a_philo, (void*)&g_philo.params[i]);
		pthread_create(&g_philo.monitors[i], NULL,
						&a_monitor, (void*)&g_philo.params[i]);
		i += 2;
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
