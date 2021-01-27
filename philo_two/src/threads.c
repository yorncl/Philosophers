/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yorn <yorn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 11:25:14 by user42            #+#    #+#             */
/*   Updated: 2021/01/27 02:48:04 by yorn             ###   ########.fr       */
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

static void		init_threads(void)
{
	int			i;

	gettimeofday(&g_philo.time_now, 0);
	g_philo.timestampstart = get_timestamp();
	i = -1;
	while (++i < g_philo.nb_philo)
	{
		pthread_create(&g_philo.philosophers[i], NULL,
						&a_philo, (void*)&g_philo.params[i]);
		pthread_create(&g_philo.monitors[i], NULL,
				&a_monitor, (void*)&g_philo.params[i]);
		i++;
		usleep(1000);
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
