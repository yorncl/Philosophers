/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 11:25:59 by user42            #+#    #+#             */
/*   Updated: 2020/09/17 00:16:08 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_one.h>

static void		parse_arg(char **av)
{
	g_philo.nb_philo = ft_atoi(av[1]);
	g_philo.time_to_die = ft_atoi(av[2]);
	g_philo.time_to_eat = ft_atoi(av[3]);
	g_philo.time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		g_philo.nb_musteat = ft_atoi(av[5]);
	else
		g_philo.nb_musteat = -1;
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

static int		init_global(char **av)
{
	int i;

	memset(&g_philo, 0, sizeof(t_p1));
	parse_arg(av);
	pthread_mutex_init(&g_philo.print_mutex, 0); //check error
	pthread_mutex_init(&g_philo.isdying, 0); // check error
	g_philo.monitors = malloc(sizeof(pthread_t) * g_philo.nb_philo); //Check error
	g_philo.philosophers = malloc(sizeof(pthread_t) * g_philo.nb_philo); //Check error
	g_philo.params = malloc(sizeof(t_params) * g_philo.nb_philo); //Check error
	memset(g_philo.params, 0, sizeof(t_params) * g_philo.nb_philo);
	g_philo.forks = malloc(sizeof(pthread_mutex_t) * g_philo.nb_philo);
	i = -1;
	while (++i < g_philo.nb_philo)
		pthread_mutex_init(&g_philo.forks[i], 0);
	return (0);
}

static void		destroy_global()
{
	int i;

	pthread_mutex_destroy(&g_philo.print_mutex);
	pthread_mutex_destroy(&g_philo.isdying);
	memset(g_philo.monitors, 0, sizeof(pthread_t) * g_philo.nb_philo);
	free(g_philo.monitors);
	memset(g_philo.philosophers, 0, sizeof(pthread_t) * g_philo.nb_philo);
	free(g_philo.philosophers);
	memset(g_philo.params, 0, sizeof(t_params) * g_philo.nb_philo);
	free(g_philo.params);
	i = -1;
	while (++i < g_philo.nb_philo)
		pthread_mutex_destroy(&g_philo.forks[i]);
	memset(g_philo.forks, 0, sizeof(pthread_mutex_t*) * g_philo.nb_philo);
	free(g_philo.forks);
	memset(&g_philo, 0, sizeof(t_p1));
}

int				main(int ac, char **av)
{
	if (ac < 5 || ac > 6)
	{
		write(2, "INVALID NUMBER OF ARGUMENTS\n", 21);
		return (1);
	}
	if (!are_numbers(ac, av))
	{
		write(2, "INVALID ARGUMENTS\n", 18);
		return (1);
	}
	init_global(av); // check error
	launch_sim(); // check error
	destroy_global();
	return (0);
}
