#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct	s_p1 t_p1;

typedef struct	s_params
{
	int				id;
	int				nbmeal;
	struct timeval	last_eaten;
	t_p1			*p;
	pthread_t		monitor;
}				t_params;

typedef struct	s_p1
{
	int				start;
	int				nb;
	int				todie;
	int				toeat;
	int				tosleep;
	int				musteat;
	int				someonedied;
	pthread_t		*threads;
	pthread_mutex_t isdying;
	pthread_mutex_t print_mutex;
	pthread_mutex_t *forks;
	t_params		*params;
	struct timeval	time_start;
	struct timeval	time_now;
}				t_p1;



int		ft_strlen(char *str);
void	ft_putstr_fd(int fd, char *str, int len);
void	ft_putunsigned_fd(int fd, unsigned long long int nb);


int		main(int ac, char **av);
#endif