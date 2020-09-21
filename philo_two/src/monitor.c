/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 11:30:43 by user42            #+#    #+#             */
/*   Updated: 2020/09/17 16:07:47 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_two.h>

void	*a_monitor(void *arg)
{
	t_params *p;

	p = (t_params*)arg;
	while (!g_philo.someonedied && p->nbmeal != g_philo.nb_musteat)
	{
		if (get_timestamp() > g_philo.time_to_die + p->last_eaten)
		{
			sem_wait(g_philo.isdying);
			print_msg(p->id, DIE);
			sem_post(g_philo.isdying);
			break ;
		}
		usleep(2000);
	}
	return (0);
}
