/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 13:51:13 by user42            #+#    #+#             */
/*   Updated: 2020/09/03 23:19:06 by user42           ###   ########.fr       */
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
	int					nb_of_philo;
	unsigned int		time_to_die;
	unsigned int		time_to_eat;
	unsigned int		time_to_sleep;
	int					nb_musteat;
	int					someonedied;
	pthread_t			*monitors;
	pthread_t			*philosophers;
	pthread_mutex_t		isdying;
	pthread_mutex_t		print_mutex;
	pthread_mutex_t		*forks;
	t_params			*params;
	struct timeval		time_now;
	unsigned long int	timestampstart;
}				t_p1;

struct s_p1		g_philo;

int				ft_strlen(char *str);
void			ft_putstr_fd(int fd, char *str, int len);
void			ft_putunsigned_fd(int fd, unsigned long long int nb);
unsigned int	ft_atoi(char *s);
unsigned int	get_timestamp();

int				launch_sim();

void			print_msg(unsigned int id, char *string, int len);

void			*a_monitor(void *arg);

void			*a_philo(void *arg);
#endif
