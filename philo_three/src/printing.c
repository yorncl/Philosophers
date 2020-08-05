/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 11:31:35 by user42            #+#    #+#             */
/*   Updated: 2020/08/05 23:56:16 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_three.h>

void	print_msg(t_params *p, unsigned int id, char *string, int len)
{
	sem_wait(p->p->print_sem);
	ft_putunsigned_fd(1, get_timestamp(p->p));
	write(1, " ", 1);
	ft_putunsigned_fd(1, id + 1);
	ft_putstr_fd(1, string, len);
	sem_post(p->p->print_sem);
}
