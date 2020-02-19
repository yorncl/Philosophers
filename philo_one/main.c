#include <philo_one.h>

#include <stdio.h>

pthread_mutex_t print_mutex;

void	print_msg(int timestamp, int id, char *string)
{
	pthread_mutex_lock(&print_mutex);
	ft_putnbr_fd(1 ,timestamp);
	write(1, " ",1);
	ft_putnbr_fd(1, id);
	write(1, " ",1);
	ft_putstr_fd(1, string, ft_strlen(string));
	pthread_mutex_unlock(&print_mutex);
}

void	*a_philo(void *arg)
{
	// int time;
	t_params *p;

	p = (t_params*) arg;
	while (1)
	{
		//Eat
		// get_forks(p);
		print_msg(500, p->id, "is living\n");
		usleep(p->p->toeat * 1000);
		// put_forks(p);
		//Sleep
		// usleep(p->p->tosleep);
		//Think
		// usleep(p->p->tothink);
	}
	return (0);
}

int		init_threads(t_p1 *p)
{
	int			i;

	i = -1;
	pthread_mutex_init(&p->isdead, 0); // CHECK FOR ERROR
	pthread_mutex_lock(&p->isdead);
	p->forks = malloc(sizeof(pthread_mutex_t) * p->nb); // CHECK FOR ERROR
	while (++i < p->nb)
		pthread_mutex_init(&p->forks[i], 0);
	i = -1;
	p->params = malloc(sizeof(t_params) * p->nb); // CHECK FOR ERROR
	while (++i < p->nb)
	{
		(&p->params[i])->id = i;
		(&p->params[i])->p = p;
	}
	p->threads = malloc(sizeof(pthread_t) * p->nb); // CHECK FOR ERROR
	i = -1;
	while (++i < p->nb)
		pthread_create(
					&p->threads[i], NULL, &a_philo, (void*)&p->params[i]);
	
	return (0);
}

int		ft_atoi(char *s)
{
	int r;

	r = 0;
	while (*s >= '0' && *s <= '9')
	{
		r = r * 10 + *s - '0';
		s++;
	}
	return (r);
}

void	parse_arg(t_p1 *p, char **av)
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


int		main(int ac, char **av)
{
	t_p1			philo;
	// struct timeval	start;

	if (ac < 5)
		return (-1);
	parse_arg(&philo, av); // CHECK IF 0
	pthread_mutex_init(&print_mutex, 0);
	// gettimeofday(&start, 0);
	printf("OK ARGS nb:%d todie:%d toeat:%d tosleep:%d musteat:%d\n", philo.nb, philo.todie, philo.toeat, philo.tosleep, philo.musteat);
	init_threads(&philo);
	pthread_mutex_lock(&philo.isdead);
	
	return (0);
}