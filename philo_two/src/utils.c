/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yorn <yorn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 11:28:59 by user42            #+#    #+#             */
/*   Updated: 2021/01/27 00:34:22 by yorn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_two.h>

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

void			ft_sleep(unsigned int milis)
{
	unsigned int start;

	start = get_timestamp();
	while (get_timestamp() < start + milis)
	{
		usleep(500);
	}
}

unsigned int	get_timestamp(void)
{
	gettimeofday(&g_philo.time_now, 0);
	return ((g_philo.time_now.tv_sec * 1000 + g_philo.time_now.tv_usec / 1000)
			- g_philo.timestampstart);
}

void			ft_strcpy(char *dest, char *src)
{
	while (*src)
		*dest++ = *src++;
	*dest = 0;
}
