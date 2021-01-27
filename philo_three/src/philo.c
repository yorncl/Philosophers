/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yorn <yorn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 11:28:37 by user42            #+#    #+#             */
/*   Updated: 2021/01/27 21:39:17 by yorn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_three.h>

static void		get_forks(t_params *p)
{
	sem_wait(g_philo.forks);
	print_msg(p->id, TAKE_FORK);
	sem_wait(g_philo.forks);
	print_msg(p->id, TAKE_FORK);
	sem_wait(g_philo.protection[p->id]);
	p->last_eaten = get_timestamp();
	p->nbmeal++;
	sem_post(g_philo.protection[p->id]);
}

static void		put_forks(void)
{
	sem_post(g_philo.forks);
	sem_post(g_philo.forks);
}

void			a_philo(void *arg)
{
	t_params *p;

	p = (t_params*)arg;
	pthread_create(&p->monitor, NULL, &a_monitor, arg);
	pthread_detach(p->monitor);
	while (!g_philo.someonedied)
	{
		get_forks(p);
		print_msg(p->id, EAT);
		ft_sleep(g_philo.time_to_eat);
		put_forks();
		if (p->nbmeal == g_philo.nb_musteat && g_philo.nb_musteat != -1)
			break ;
		print_msg(p->id, SLEEP);
		ft_sleep(g_philo.time_to_sleep);
		print_msg(p->id, THINK);
	}
	exit(g_philo.someonedied ? EXIT_DIED : 0);
}
