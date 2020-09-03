/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 11:25:14 by user42            #+#    #+#             */
/*   Updated: 2020/09/03 23:33:14 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_one.h>

static void	init_params()
{
	int i;

	i = -1;
	while (++i < g_philo.nb_of_philo)
	{
		g_philo.params[i].id = i;
	}
}

static	int	init_threads()
{
	// int			i;

	gettimeofday(&g_philo.time_now, 0);
	g_philo.timestampstart = get_timestamp();
	// i = 0;
	// while (i < g_philo.nb_of_philo)
	// {
	// 	pthread_create(
	// 				&g_philo.philophers[i], NULL, &a_philo, (void*)&g_philo.params[i]);
	// 	pthread_create(
	// 				&g_philo.monitors[i], NULL, &a_monitor, (void*)&g_philo.params[i]);
	// 	i += 2;
	// }
	// usleep(g_philo.nb_of_philo * 5000);
	// i = 1;
	// while (i < g_philo.nb_of_philo)
	// {
	// 	pthread_create(
	// 				&g_philo.philophers[i], NULL, &a_philo, (void*)&g_philo.params[i]);
	// 	pthread_create(
	// 				&g_philo.monitors[i], NULL, &a_monitor, (void*)&g_philo.params[i]);
	// 	i += 2;
	// }
	return (0);
}

int				launch_sim()
{
	init_params();
	init_threads(); // check error
	return (0);
}