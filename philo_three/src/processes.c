/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 11:25:14 by user42            #+#    #+#             */
/*   Updated: 2020/09/21 18:49:04 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_three.h>

static void		init_params(void)
{
	int i;

	i = -1;
	while (++i < g_philo.nb_philo)
	{
		g_philo.params[i].id = i;
	}
}

static void		init_processes(void)
{
	int			i;

	gettimeofday(&g_philo.time_now, 0);
	g_philo.timestampstart = get_timestamp();
	i = -1;
	while (++i < g_philo.nb_philo)
	{
		if ((g_philo.philosophers[i] = fork()) == 0)
			a_philo(g_philo.params);
		else if(g_philo.philosophers == -1)
		{
			/* code */
		}
	}
}

static void		kill_processes(void)
{
	int i;
	int status;

	i = -1;
	while (++i < g_philo.nb_philo)
	{
		waitpid(g_philo.philosophers[i], );
	}
}

void			launch_sim(void)
{
	init_params();
	init_processes();
	kill_processes();
}
