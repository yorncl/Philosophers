/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 11:28:59 by user42            #+#    #+#             */
/*   Updated: 2020/09/03 21:47:47 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_one.h>

int				ft_strlen(char *str)
{
	int len;

	len = 0;
	while (*str)
	{
		len++;
		str++;
	}
	return (len);
}

void			ft_putstr_fd(int fd, char *str, int len)
{
	write(fd, str, len);
}

void			ft_putunsigned_fd(int fd, unsigned long long int nb)
{
	char c;

	if (nb >= 10)
		ft_putunsigned_fd(fd, nb / 10);
	c = '0' + nb % 10;
	write(fd, &c, 1);
}

unsigned int	ft_atoi(char *s)
{
	unsigned int r;

	r = 0;
	while (*s >= '0' && *s <= '9')
	{
		r = r * 10 + *s - '0';
		s++;
	}
	return (r);
}

unsigned int	get_timestamp()
{
	gettimeofday(&g_time_now, 0);
	return ((g.philo.g_time_now.tv_sec * 1000 + g.philo.g_time_now.tv_usec / 1000)
			- g_philo.timestampstart);
}
