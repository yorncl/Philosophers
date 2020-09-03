/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 11:28:37 by user42            #+#    #+#             */
/*   Updated: 2020/09/03 22:35:17 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_one.h>

static void		get_forks(t_params *p)
{
	pthread_mutex_lock(&g_philo.forks[p->id]);
	if (p->id + 1 == g_philo.nb)
		pthread_mutex_lock(&g_philo.forks[0]);
	else
		pthread_mutex_lock(&g_philo.forks[p->id + 1]);
	p->last_eaten = get_timestamp(p->p);
}

static void		put_forks(t_params *p)
{
	pthread_mutex_unlock(&g_philo.forks[p->id]);
	if (p->id == g_philo.nb - 1)
		pthread_mutex_unlock(&g_philo.forks[0]);
	else
		pthread_mutex_unlock(&g_philo.forks[p->id + 1]);
}

void			*a_philo(void *arg)
{
	t_params *p;

	p = (t_params*)arg;
	while (1)
	{
		get_forks(p);
		print_msg(p, p->id, " is eating\n", 11);
		usleep(g_philo.time_to_eat * 1000);
		put_forks(p);
		if (p->nbmeal == g_philo.nb_musteat && g_philo.nb_musteat != -1)
			break ;
		print_msg(p, p->id, " is sleeping\n", 13);
		usleep(g_philo.time_to_sleep * 1000);
		print_msg(p, p->id, " is thinking\n", 13);
	}
	pthread_join(p->monitor, 0);
	return (0);
}
