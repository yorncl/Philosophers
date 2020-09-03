/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 13:51:13 by user42            #+#    #+#             */
/*   Updated: 2020/08/05 23:49:10 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_THREE_H
# define PHILO_THREE_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <semaphore.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>

# define IDIED 151

typedef struct s_p3		t_p3;

typedef struct	s_params
{
	int				id;
	int				nbmeal;
	unsigned int	last_eaten;
	t_p3			*p;
	pthread_t		monitor;
}				t_params;

struct			s_p3
{
	int					start;
	int					nb;
	unsigned int		todie;
	unsigned int		toeat;
	unsigned int		tosleep;
	int					musteat;
	pid_t				*processes;
	int					isfull;
	int					someonedied;
	sem_t				*forks;
	sem_t				*print_sem;
	sem_t				*isdying;
	t_params			*params;
	struct timeval		time_start;
	unsigned long int	timestampstart;
	struct timeval		time_now;
};

int				ft_strlen(char *str);
void			ft_putstr_fd(int fd, char *str, int len);
void			ft_putunsigned_fd(int fd, unsigned long long int nb);
unsigned int	ft_atoi(char *s);
unsigned int	get_timestamp(t_p3 *p);

int				init_processes(t_p3 *p);
void			wait_processes(t_p3 *p);
void			free_params(t_p3 *p);

void			print_msg(t_params *p, unsigned int id, char *string, int len);

void			*a_monitor(void *arg);

int				a_philo(t_params *p);
#endif
