/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yorn <yorn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 16:11:32 by user42            #+#    #+#             */
/*   Updated: 2021/01/28 14:16:05 by yorn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_two.h>

static int		parse_arg(char **av)
{
	g_philo.nb_philo = ft_atoi(av[1]);
	g_philo.time_to_die = ft_atoi(av[2]);
	g_philo.time_to_eat = ft_atoi(av[3]);
	g_philo.time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		g_philo.nb_musteat = ft_atoi(av[5]);
	else
		g_philo.nb_musteat = -1;
	if (
		g_philo.nb_philo < 2 ||
		g_philo.time_to_die < 0 ||
		g_philo.time_to_eat < 0 ||
		g_philo.time_to_sleep < 0 ||
		(av[5] && g_philo.nb_musteat <= 0))
		return (1);
	return (0);
}

static int		are_numbers(int ac, char **av)
{
	int i;

	while (--ac > 0)
	{
		i = 0;
		while (av[ac][i])
		{
			if (av[ac][i] < '0' || av[ac][i] > '9')
				return (0);
			i++;
		}
	}
	return (1);
}

static int		init_global(void)
{
	if ((g_philo.print_mutex = sem_open("prnt", O_CREAT, 777, 1)) == SEM_FAILED
		|| sem_unlink("prnt")
		|| (g_philo.isdying = sem_open("dying", O_CREAT, 777, 1)) == SEM_FAILED
		|| sem_unlink("dying")
		|| (g_philo.forks = sem_open("forks", O_CREAT,
						777, g_philo.nb_philo)) == SEM_FAILED
		|| sem_unlink("forks"))
		return (1);
	if ((g_philo.protection = malloc(sizeof(sem_t*) * g_philo.nb_philo)) == 0)
		return (1);
	if (create_semaphores())
		return (1);
	g_philo.monitors = malloc(sizeof(pthread_t) * g_philo.nb_philo);
	g_philo.philosophers = malloc(sizeof(pthread_t) * g_philo.nb_philo);
	g_philo.params = malloc(sizeof(t_params) * g_philo.nb_philo);
	memset(g_philo.params, 0, sizeof(t_params) * g_philo.nb_philo);
	if (!g_philo.monitors || !g_philo.philosophers
					|| !g_philo.params || !g_philo.forks)
		return (1);
	return (0);
}

static void		destroy_global(void)
{
	int i;

	if (g_philo.print_mutex)
		sem_close(g_philo.print_mutex);
	if (g_philo.isdying)
		sem_close(g_philo.isdying);
	if (g_philo.forks)
		sem_close(g_philo.forks);
	if (g_philo.monitors)
		free(g_philo.monitors);
	if (g_philo.philosophers)
		free(g_philo.philosophers);
	i = -1;
	if (g_philo.protection)
	{
		while (++i < g_philo.nb_philo)
			if (g_philo.protection[i])
				sem_close(g_philo.protection[i]);
		free(g_philo.protection);
	}
	if (g_philo.params)
		free(g_philo.params);
	memset(&g_philo, 0, sizeof(t_p1));
}

int				main(int ac, char **av)
{
	memset(&g_philo, 0, sizeof(t_p1));
	if (ac < 5 || ac > 6)
	{
		write(2, "Invalid number of arguments.\n", 29);
		return (1);
	}
	if (!are_numbers(ac, av) || parse_arg(av))
	{
		write(2, "Aguments are invalid in some way.\n", 34);
		return (1);
	}
	if (init_global() == 0)
		launch_sim();
	destroy_global();
	return (0);
}
