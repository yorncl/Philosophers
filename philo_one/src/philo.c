/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 11:28:37 by user42            #+#    #+#             */
/*   Updated: 2020/10/09 01:00:28 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_one.h>

static void		get_forks(t_params *p)
{
	pthread_mutex_lock(&g_philo.forks[p->id]);
	print_msg(p->id, TAKE_FORK);
	if (p->id + 1 == g_philo.nb_philo)
		pthread_mutex_lock(&g_philo.forks[0]);
	else
		pthread_mutex_lock(&g_philo.forks[p->id + 1]);
	print_msg(p->id, TAKE_FORK);
	pthread_mutex_lock(&g_philo.protection[p->id]);
	p->last_eaten = get_timestamp();
	p->nbmeal++;
}

static void		put_forks(t_params *p)
{
	pthread_mutex_unlock(&g_philo.forks[p->id]);
	if (p->id == g_philo.nb_philo - 1)
		pthread_mutex_unlock(&g_philo.forks[0]);
	else
		pthread_mutex_unlock(&g_philo.forks[p->id + 1]);
	pthread_mutex_unlock(&g_philo.protection[p->id]);
}

void			*a_philo(void *arg)
{
	t_params *p;

	p = (t_params*)arg;
	while (!g_philo.someonedied)
	{
		get_forks(p);
		print_msg(p->id, EAT);
		ft_sleep(g_philo.time_to_eat);
		put_forks(p);
		if (p->nbmeal == g_philo.nb_musteat && g_philo.nb_musteat != -1)
			break ;
		print_msg(p->id, SLEEP);
		ft_sleep(g_philo.time_to_sleep);
		print_msg(p->id, THINK);
	}
	return (0);
}
