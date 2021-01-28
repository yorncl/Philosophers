/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yorn <yorn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 11:31:35 by user42            #+#    #+#             */
/*   Updated: 2021/01/28 13:55:24 by yorn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_one.h>

unsigned int	ft_uintlen(unsigned long long int n)
{
	int size;

	if (n == 0)
		return (1);
	size = 0;
	while (n != 0)
	{
		n /= 10;
		size++;
	}
	return (size);
}

unsigned int	unsigned_copy(char *dest, unsigned long long int nb)
{
	unsigned int	size;
	unsigned int	i;

	size = ft_uintlen(nb);
	i = size;
	while (i != 0)
	{
		dest[i - 1] = '0' + (nb % 10);
		nb /= 10;
		i--;
	}
	return (size);
}

static void		ft_strcpy(char *dest, char *src)
{
	while (*src)
		*dest++ = *src++;
	*dest = 0;
}

static void		copy_msg(int offset, t_message msg)
{
	if (msg == DIE)
	{
		g_philo.someonedied = 1;
		ft_strcpy(g_philo.output + offset, "is dying\n");
	}
	else if (msg == TAKE_FORK)
		ft_strcpy(g_philo.output + offset, "has taken a fork\n");
	else if (msg == THINK)
		ft_strcpy(g_philo.output + offset, "is thinking\n");
	else if (msg == EAT)
		ft_strcpy(g_philo.output + offset, "is eating\n");
	else if (msg == SLEEP)
		ft_strcpy(g_philo.output + offset, "is sleeping\n");
}

void			print_msg(unsigned int id, t_message msg)
{
	int offset;

	pthread_mutex_lock(&g_philo.print_mutex);
	if (g_philo.someonedied)
	{
		pthread_mutex_unlock(&g_philo.print_mutex);
		return ;
	}
	offset = 0;
	offset = unsigned_copy((char*)g_philo.output + offset, get_timestamp());
	g_philo.output[offset] = ' ';
	offset++;
	offset += unsigned_copy((char*)g_philo.output + offset, id + 1);
	g_philo.output[offset] = ' ';
	offset++;
	copy_msg(offset, msg);
	write(1, g_philo.output, ft_strlen(g_philo.output));
	pthread_mutex_unlock(&g_philo.print_mutex);
}
