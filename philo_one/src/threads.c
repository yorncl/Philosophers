/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 11:25:14 by user42            #+#    #+#             */
/*   Updated: 2020/08/03 13:49:05 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_one.h>

static int	init_params(t_p1 *p)
{
	int			i;

	i = -1;
	if (pthread_mutex_init(&p->isdying, 0))
		return (-1);
	p->someonedied = 0;
	p->someonefull = 0;
	p->forks = malloc(sizeof(pthread_mutex_t) * p->nb);
	while (++i < p->nb)
		if  (pthread_mutex_init(&p->forks[i], 0))
			return (-1);
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

int			init_threads(t_p1 *p)
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
		i +=2;
	}
	usleep(p->nb * 5000);
	i = 1;
	while (i < p->nb)
	{
		pthread_create(
					&p->threads[i], NULL, &a_philo, (void*)&p->params[i]);
		i +=2;
	}
	return (0);
}

void	free_params(t_p1 *p)
{
	int			i;

	i = -1;
	while (++i < p->nb)
	{
		pthread_mutex_unlock(&p->forks[i]);
		pthread_mutex_destroy(&p->forks[i]);
	}
	free(p->threads);
	free(p->forks);
	free(p->params);
}