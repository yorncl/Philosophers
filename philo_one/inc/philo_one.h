/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 13:51:13 by user42            #+#    #+#             */
/*   Updated: 2020/08/03 14:01:26 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_p1		t_p1;

typedef struct	s_params
{
	int				id;
	int				nbmeal;
	unsigned int	last_eaten;
	t_p1			*p;
	pthread_t		monitor;
}				t_params;

struct			s_p1
{
	int					start;
	int					nb;
	unsigned int		todie;
	unsigned int		toeat;
	unsigned int		tosleep;
	int					musteat;
	int					someonedied;
	int					someonefull;
	pthread_t			*threads;
	pthread_mutex_t		isdying;
	pthread_mutex_t		print_mutex;
	pthread_mutex_t		*forks;
	t_params			*params;
	struct timeval		time_start;
	unsigned long int	timestampstart;
	struct timeval		time_now;
};

int				ft_strlen(char *str);
void			ft_putstr_fd(int fd, char *str, int len);
void			ft_putunsigned_fd(int fd, unsigned long long int nb);
unsigned int	ft_atoi(char *s);
unsigned int	get_timestamp(t_p1 *p);

int				init_threads(t_p1 *p);
void			free_params(t_p1 *p);

void			print_msg(t_params *p, unsigned int id, char *string, int len);

void			*a_monitor(void *arg);

void			*a_philo(void *arg);
#endif
