/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 11:28:37 by user42            #+#    #+#             */
/*   Updated: 2020/08/19 15:18:39 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_three.h>

static void		get_forks(t_params *p)
{
	sem_wait(p->p->forks);
	sem_wait(p->p->forks);
	p->last_eaten = get_timestamp(p->p);
}

static void		put_forks(t_params *p)
{
	sem_post(p->p->forks);
	sem_post(p->p->forks);
}

static int		is_full(t_params *p)
{
	if (p->p->musteat != -1 && p->nbmeal == p->p->musteat)
	{
		p->p->isfull = 1;
		return (1);
	}
	return (0);
}

int				a_philo(t_params *p)
{
	pthread_create(&p->monitor, NULL, &a_monitor, p);
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
	return (p->p->someonedied ? IDIED : 0);
}
