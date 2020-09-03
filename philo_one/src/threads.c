/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 11:25:14 by user42            #+#    #+#             */
/*   Updated: 2020/09/03 22:53:05 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_one.h>

static int	init_params()
{
	int i;

	i = -1;
	while (++i < g_philo.nb_of_philo)
	{
		g_philo.params[i]->id = i;
	}
}

int			init_threads(t_p1 *p)
{
	int			i;

	if (init_params())
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
					&p->philophers[i], NULL, &a_philo, (void*)&p->params[i]);
		pthread_create(
					&p->monitors[i], NULL, &a_monitor, (void*)&p->params[i]);
		i += 2;
	}
	usleep(p->nb * 5000);
	i = 1;
	while (i < p->nb)
	{
		pthread_create(
					&p->philophers[i], NULL, &a_philo, (void*)&p->params[i]);
		pthread_create(
					&p->monitors[i], NULL, &a_monitor, (void*)&p->params[i]);
		i += 2;
	}
	return (0);
}