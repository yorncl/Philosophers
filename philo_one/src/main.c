/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 11:25:59 by user42            #+#    #+#             */
/*   Updated: 2020/08/03 11:25:59 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_one.h>


static void	parse_arg(t_p1 *p, char **av)
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


#include <stdio.h>
int		main(int ac, char **av)
{
	t_p1			philo;
	int				i;

	if (ac < 5 || ac > 6)
	{
		write(2, "INVALID NUMBER OF ARGUMENTS\n", 21);
		return (-1);
	}
	parse_arg(&philo, av); // CHECK IF 0
	pthread_mutex_init(&philo.print_mutex, 0);
	printf("OK ARGS nb:%d todie:%d toeat:%d tosleep:%d musteat:%d\n", philo.nb, philo.todie, philo.toeat, philo.tosleep, philo.musteat);
	if (init_threads(&philo))
		write(2, "AN ERROR HAS OCCURED\n", 21);
	i = -1;
	while (++i < philo.nb)
		pthread_join(philo.threads[i], 0);
	free_params(&philo);
	return (0);
}