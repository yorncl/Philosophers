/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yorn <yorn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 11:30:43 by user42            #+#    #+#             */
/*   Updated: 2021/01/27 16:59:25 by yorn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_three.h>

void	*a_monitor(void *arg)
{
	t_params *p;

	p = (t_params*)arg;
	while (!g_philo.someonedied && p->nbmeal != g_philo.nb_musteat)
	{
		sem_wait(g_philo.protection[p->id]);
		if (get_timestamp() > g_philo.time_to_die + p->last_eaten)
		{
			sem_wait(g_philo.isdying);
			print_msg(p->id, DIE);
			sem_post(g_philo.isdying);
			sem_post(g_philo.protection[p->id]);
			break ;
		}
		sem_post(g_philo.protection[p->id]);
		usleep(8000);
	}
	return (0);
}

