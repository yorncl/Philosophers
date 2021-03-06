/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yorn <yorn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 13:51:13 by user42            #+#    #+#             */
/*   Updated: 2021/01/28 15:05:11 by yorn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_THREE_H
# define PHILO_THREE_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <string.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>

# define EXIT_DIED 69

typedef struct	s_params
{
	int				id;
	int				nbmeal;
	unsigned int	last_eaten;
	pthread_t		monitor;

}				t_params;

struct			s_p1
{
	int					nb_philo;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					nb_musteat;
	int					someonedied;
	pid_t				*philosophers;
	sem_t				*isdying;
	sem_t				*print_mutex;
	sem_t				*forks;
	sem_t				**protection;
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
void			ft_sleep(unsigned int milis);
void			ft_strcpy(char *dest, char *src);
unsigned int	unsigned_copy(char *dest, unsigned long long int nb);
unsigned int	ft_uintlen(unsigned long long int n);
char			*get_name(unsigned int i);
int				create_semaphores(void);
void			destroy_global(void);

void			launch_sim();

void			print_msg(unsigned int id, t_message msg);

void			*a_monitor(void *arg);

void			a_philo(void *arg);
#endif
