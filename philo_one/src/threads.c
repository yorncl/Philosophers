/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 11:25:14 by user42            #+#    #+#             */
/*   Updated: 2020/08/03 11:40:48 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_one.h>

int		init_params(t_p1 *p)
{
	int			i;

	i = -1;
	pthread_mutex_init(&p->isdying, 0); // CHECK FOR ERROR
	p->someonedied = 0;
	p->forks = malloc(sizeof(pthread_mutex_t) * p->nb); // CHECK FOR ERROR
	while (++i < p->nb)
		pthread_mutex_init(&p->forks[i], 0);
	i = -1;
	p->params = malloc(sizeof(t_params) * p->nb); // CHECK FOR ERROR
	while (++i < p->nb)
	{
		(&p->params[i])->id = i;
		(&p->params[i])->nbmeal = 0;
		(&p->params[i])->p = p;
		(&p->params[i])->last_eaten = 0;
	}
	return (0);
}

int		init_threads(t_p1 *p)
{
	int			i;

	init_params(p);
	p->threads = malloc(sizeof(pthread_t) * p->nb); // CHECK FOR ERROR
	i = -1;
	gettimeofday(&p->time_start, 0);
	p->timestampstart = get_timestamp(p);
	while (++i < p->nb)
	{
		pthread_create(
					&p->threads[i], NULL, &a_philo, (void*)&p->params[i]);
		usleep(1000);
	}
	return (0);
}

void	free_params(t_p1 *p)
{
	free(p->threads);
	free(p->forks);
	free(p->params);
}