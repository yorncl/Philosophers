#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct	s_p1 t_p1;

typedef struct	s_params
{
	int		id;
	t_p1	*p;
}				t_params;

typedef struct	s_p1
{
	int				start;
	int				nb;
	int				todie;
	int				toeat;
	int				tosleep;
	int				musteat;
	pthread_t		*threads;
	pthread_mutex_t isdead;
	pthread_mutex_t *forks;
	t_params		*params;
	struct timeval	time_start;
}				t_p1;



int		ft_strlen(char *str);
void	ft_putstr_fd(int fd, char *str, int len);
void	ft_putnbr_fd(int fd, int nb);


int		main(int ac, char **av);
#endif