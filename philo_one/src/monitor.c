/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 11:30:43 by user42            #+#    #+#             */
/*   Updated: 2020/08/03 13:04:09 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_one.h>

void	*a_monitor(void *arg)
{
	t_params *p;

	p = (t_params*) arg;
	while (!p->p->someonedied && !p->p->someonefull)
	{
		if (get_timestamp(p->p)  - p->last_eaten > p->p->todie)
		{
			pthread_mutex_lock(&p->p->isdying);
			if (!p->p->someonedied)
			{
				p->p->someonedied = 1;
				print_msg(p, p->id, " is dying\n", 10);
			}
			pthread_mutex_unlock(&p->p->isdying);
			break ;
		}
		usleep(2000);
	}
	return (0);
}
