/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 11:31:35 by user42            #+#    #+#             */
/*   Updated: 2020/08/03 11:39:03 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_one.h>

void	print_msg(t_params *p, unsigned int id, char *string, int len)
{
	pthread_mutex_lock(&p->p->print_mutex);
	ft_putunsigned_fd(1, get_timestamp(p->p));
	write(1, " ",1);
	ft_putunsigned_fd(1, id);
	ft_putstr_fd(1, string, len);
	pthread_mutex_unlock(&p->p->print_mutex);
}
