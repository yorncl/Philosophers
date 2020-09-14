/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 11:31:35 by user42            #+#    #+#             */
/*   Updated: 2020/09/14 14:09:13 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_one.h>

void	print_msg(unsigned int id, char *string, int len)
{
	if (g_philo.someonedied)
		return ;
	pthread_mutex_lock(&g_philo.print_mutex);
	ft_putunsigned_fd(1, get_timestamp());
	write(1, " ", 1);
	ft_putunsigned_fd(1, id + 1);
	ft_putstr_fd(1, string, len);
	pthread_mutex_unlock(&g_philo.print_mutex);
}
