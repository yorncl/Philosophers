/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 11:30:43 by user42            #+#    #+#             */
/*   Updated: 2020/08/19 15:18:38 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_three.h>

void	*a_monitor(void *arg)
{
	t_params *p;

	p = (t_params*)arg;
	while (!p->p->isfull)
	{
		if (get_timestamp(p->p) - p->last_eaten > p->p->todie)
		{
			sem_wait(p->p->isdying);
			if (!p->p->someonedied)
			{
				p->p->someonedied = 1;
				print_msg(p, p->id, " is dying\n", 10);
			}
			break ;
		}
		usleep(2000);
	}
	return (0);
}
