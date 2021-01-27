/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sem.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yorn <yorn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 16:11:32 by user42            #+#    #+#             */
/*   Updated: 2021/01/27 15:57:47 by yorn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_three.h>

char		*get_name(unsigned int i)
{
	char	*name;
	int		len;

	len = ft_uintlen(i);
	if ((name = malloc(sizeof(char) * (10 + len + 1))) == NULL)
		return (NULL);
	ft_strcpy(name, "philo_sem_");
	unsigned_copy(name + 10, (unsigned long long int)i);
	name[10 + len] = 0;
	return (name);
}

int			create_semaphores(void)
{
	int		i;
	char	*name;

	i = -1;
	while (++i < g_philo.nb_philo)
	{
		name = get_name(i);
		if ((g_philo.protection[i] = sem_open(name,
				O_CREAT | O_EXCL, 777, 1)) == SEM_FAILED || sem_unlink(name))
			return (1);
		free(name);
	}
	return (0);
}
