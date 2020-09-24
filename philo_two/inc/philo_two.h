/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 13:51:13 by user42            #+#    #+#             */
/*   Updated: 2020/09/21 18:17:50 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_TWO_H
# define PHILO_TWO_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <string.h>
# include <semaphore.h>
# include <fcntl.h>

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
	sem_t				*isdying;
	sem_t				*print_mutex;
	sem_t				*forks;
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
unsigned int	get_timestamp(void);

void			launch_sim();

void			print_msg(unsigned int id, t_message msg);

void			*a_monitor(void *arg);

void			*a_philo(void *arg);
#endif
