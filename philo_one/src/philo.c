/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 11:28:37 by user42            #+#    #+#             */
/*   Updated: 2020/08/05 23:47:31 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_one.h>

static void		get_forks(t_params *p)
{
	int id;

	id = p->id;
	pthread_mutex_lock(&p->p->forks[id]);
	if (id + 1 == p->p->nb)
		pthread_mutex_lock(&p->p->forks[0]);
	else
		pthread_mutex_lock(&p->p->forks[id + 1]);
	p->last_eaten = get_timestamp(p->p);
}

static void		put_forks(t_params *p)
{
	int id;

	id = p->id;
	pthread_mutex_unlock(&p->p->forks[id]);
	if (id == p->p->nb - 1)
		pthread_mutex_unlock(&p->p->forks[0]);
	else
		pthread_mutex_unlock(&p->p->forks[id + 1]);
}

static int		is_full(t_params *p)
{
	if (p->nbmeal == p->p->musteat && p->p->musteat != -1)
	{
		p->p->someonefull = 1;
		return (1);
	}
	return (0);
}

void			*a_philo(void *arg)
{
	t_params *p;

	p = (t_params*)arg;
	pthread_create(&p->monitor, NULL, &a_monitor, arg);
	while (1)
	{
		get_forks(p);
		if (p->p->someonedied)
			break ;
		print_msg(p, p->id, " is eating\n", 11);
		usleep(p->p->toeat * 1000);
		put_forks(p);
		p->nbmeal++;
		if (p->p->someonedied || is_full(p))
			break ;
		print_msg(p, p->id, " is sleeping\n", 13);
		usleep(p->p->tosleep * 1000);
		if (p->p->someonedied)
			break ;
		print_msg(p, p->id, " is thinking\n", 13);
	}
	pthread_join(p->monitor, 0);
	return (0);
}
