/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 11:28:37 by user42            #+#    #+#             */
/*   Updated: 2020/08/03 11:36:36 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_one.h>


static void	get_forks(t_params *p)
{
	int id;

	id = p->id;
	pthread_mutex_lock(&p->p->forks[id]);	
	if (id == p->p->nb - 1)
		pthread_mutex_lock(&p->p->forks[0]);
	else
		pthread_mutex_lock(&p->p->forks[id + 1]);
	p->last_eaten = get_timestamp(p->p); // check for error ?
}

static void	put_forks(t_params *p)
{
	int id;

	id = p->id;
	pthread_mutex_unlock(&p->p->forks[id]);	
	if (id == p->p->nb - 1)
		pthread_mutex_unlock(&p->p->forks[0]);
	else
		pthread_mutex_unlock(&p->p->forks[id + 1]);
}

static int	is_full(t_params *p)
{
	return (p->nbmeal == p->p->musteat && p->p->musteat != -1);
}

void	*a_philo(void *arg)
{
	t_params *p;

	p = (t_params*) arg; // check for error ?
	pthread_create(&p->monitor, NULL, &a_monitor, arg);//check error ?
	while (1)
	{
		get_forks(p);
		if (p->p->someonedied)
			break;
		print_msg(p, p->id, " is eating\n", 11);
		usleep(p->p->toeat * 1000);
		put_forks(p);
		p->nbmeal++;
		if (p->p->someonedied || is_full(p))
			break;
		print_msg(p, p->id, " is sleeping\n", 13);
		usleep(p->p->tosleep * 1000);
		if (p->p->someonedied)
			break;
		print_msg(p, p->id, " is thinking\n", 13);
	}
	pthread_join(p->monitor, 0);
	return (0);
}