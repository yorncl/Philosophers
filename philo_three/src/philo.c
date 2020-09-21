/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 11:28:37 by user42            #+#    #+#             */
/*   Updated: 2020/09/21 18:24:41 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_three.h>

static void		get_forks(t_params *p)
{
	sem_wait(g_philo.forks);
	print_msg(p->id, TAKE_FORK);
	sem_wait(g_philo.forks);
	p->last_eaten = get_timestamp();
	print_msg(p->id, TAKE_FORK);
	p->nbmeal++;
}

static void		put_forks(void)
{
	sem_post(g_philo.forks);
	sem_post(g_philo.forks);
}

void			*a_philo(void *arg)
{
	t_params *p;

	p = (t_params*)arg;
	while (!g_philo.someonedied)
	{
		get_forks(p);
		print_msg(p->id, EAT);
		usleep(g_philo.time_to_eat * 1000);
		put_forks();
		if (p->nbmeal == g_philo.nb_musteat && g_philo.nb_musteat != -1)
			break ;
		print_msg(p->id, SLEEP);
		usleep(g_philo.time_to_sleep * 1000);
		print_msg(p->id, THINK);
	}
	return (0);
}
