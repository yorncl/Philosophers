/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 11:25:59 by user42            #+#    #+#             */
/*   Updated: 2020/08/05 23:32:53 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_two.h>

static void		parse_arg(t_p2 *p, char **av)
{
	p->nb = ft_atoi(av[1]);
	p->todie = ft_atoi(av[2]);
	p->toeat = ft_atoi(av[3]);
	p->tosleep = ft_atoi(av[4]);
	if (av[5])
		p->musteat = ft_atoi(av[5]);
	else
		p->musteat = -1;
	
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

#include <stdio.h>
int				main(int ac, char **av)
{
	t_p2	philo;
	int		i;

	if (ac < 5 || ac > 6)
	{
		write(2, "INVALID NUMBER OF ARGUMENTS\n", 21);
		return (-1);
	}
	if (!are_numbers(ac, av))
	{
		write(2, "INVALID ARGUMENTS\n", 18);
		return (-1);
	}
	if ((philo.print_sem = sem_open("print_sem", O_CREAT, 777, 1)) == SEM_FAILED)
		return (-1);
	sem_unlink("print_sem");
	parse_arg(&philo, av);
	if (init_threads(&philo))
		write(2, "AN ERROR HAS OCCURED\n", 21);
	i = -1;
	while (++i < philo.nb)
		pthread_join(philo.threads[i], 0);
	free_params(&philo);
	return (0);
}
