/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 11:30:43 by user42            #+#    #+#             */
/*   Updated: 2020/09/14 13:54:01 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_one.h>

void	*a_monitor(void *arg)
{
	t_params *p;

	p = (t_params*)arg;
	while (!g_philo.someonedied)
	{
		if (get_timestamp() - p->last_eaten > g_philo.time_to_die)
		{
			pthread_mutex_lock(&g_philo.isdying);
			print_msg(p->id, " is dying\n", 10);
			g_philo.someonedied = 1;
			pthread_mutex_unlock(&g_philo.isdying);
			break ;
		}
		usleep(2000);
	}
	return (0);
}
