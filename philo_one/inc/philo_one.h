/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 13:51:13 by user42            #+#    #+#             */
/*   Updated: 2020/10/09 00:59:47 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <string.h>

typedef struct	s_params
{
	int				id;
	int				nbmeal;
	unsigned int	last_eaten;
}				t_params;

struct			s_p1
{
	int					nb_philo;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					nb_musteat;
	int					someonedied;
	pthread_t			*monitors;
	pthread_t			*philosophers;
	pthread_mutex_t		isdying;
	pthread_mutex_t		print_mutex;
	pthread_mutex_t		*forks;
	pthread_mutex_t		*protection;
	t_params			*params;
	struct timeval		time_now;
	unsigned long int	timestampstart;
	char				output[4096];
}				t_p1;

typedef	enum	e_message
{
	DIE,
	TAKE_FORK,
	THINK,
	EAT,
	SLEEP
}				t_message;

struct s_p1		g_philo;

int				ft_strlen(char *str);
unsigned int	ft_atoi(char *s);
void			ft_sleep(unsigned int milis);
unsigned int	get_timestamp(void);

void			launch_sim();

void			print_msg(unsigned int id, t_message msg);

void			*a_monitor(void *arg);

void			*a_philo(void *arg);
#endif
