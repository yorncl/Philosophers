/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 11:31:35 by user42            #+#    #+#             */
/*   Updated: 2020/10/02 11:40:58 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_one.h>

static int		unsigned_copy(char *dest, unsigned int nb)
{
	int						i;
	unsigned int	size;
	unsigned int	tmp;

	size = 1;
	while (nb > (tmp = size * 10))
		size = tmp;
	i = 0;
	while (size > 0)
	{
		dest[i] = '0' + (nb / size % 10);
		size /= 10;
		i++;
	}
	return (i);
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
