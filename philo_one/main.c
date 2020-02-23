#include <philo_one.h>

#include <stdio.h>

unsigned long int get_time(struct timeval *t)
{
	return ((unsigned long int)(t->tv_sec * 1000 + t->tv_usec / 1000));
}

unsigned int get_timestamp(t_params *p)
{
	gettimeofday(&p->p->time_now, 0);
	return ((unsigned int)(get_time(&p->p->time_now) - get_time(&p->p->time_start)));
}

unsigned long long int get_timenow(t_params *p)
{
	gettimeofday(&p->p->time_now, 0);
	return (get_time(&p->p->time_now));
}

void	print_msg(t_params *p, unsigned int id, char *string)
{
	pthread_mutex_lock(&p->p->print_mutex);
	ft_putunsigned_fd(1, get_timestamp(p));
	write(1, " ",1);
	ft_putunsigned_fd(1, id);
	write(1, " ",1);
	ft_putstr_fd(1, string, ft_strlen(string));
	pthread_mutex_unlock(&p->p->print_mutex);
}

void	get_forks(t_params *p)
{
	int id;

	id = p->id;
	pthread_mutex_lock(&p->p->forks[id]);	
	if (id == p->p->nb - 1)
		pthread_mutex_lock(&p->p->forks[0]);
	else
		pthread_mutex_lock(&p->p->forks[id + 1]);
	gettimeofday(&p->last_eaten, 0); // check for error ?
}

void	put_forks(t_params *p)
{
	int id;

	id = p->id;
	pthread_mutex_unlock(&p->p->forks[id]);	
	if (id == p->p->nb - 1)
		pthread_mutex_unlock(&p->p->forks[0]);
	else
		pthread_mutex_unlock(&p->p->forks[id + 1]);
}


int is_full(t_params *p)
{
	return (p->nbmeal == p->p->musteat && p->p->musteat != -1);
}

void	*a_monitor(void *arg)
{
	t_params *p;

	p = (t_params*) arg;
	unsigned int	tmp;
	while (!p->p->someonedied)
	{
		tmp = get_timenow(p) - get_time(&p->last_eaten);
		if (tmp >= (unsigned int)p->p->todie)
		{
			pthread_mutex_lock(&p->p->isdying);
			if (!p->p->someonedied)
			{
				p->p->someonedied = 1;
				print_msg(p, p->id, "is dying\n");
			}
			pthread_mutex_unlock(&p->p->isdying);
			break ;
		}
	}
	return (0);
}

void	*a_philo(void *arg)
{
	t_params *p;

	p = (t_params*) arg;
	gettimeofday(&p->last_eaten, 0); // check for error ?
	pthread_create(&p->monitor, NULL, &a_monitor, arg);//check error ?
	while (1)
	{
		get_forks(p);
		if (p->p->someonedied)
			break;
		print_msg(p, p->id, "is eating\n");
		usleep(p->p->toeat * 1000);
		put_forks(p);
		p->nbmeal++;
		if (p->p->someonedied || is_full(p))
			break;
		print_msg(p, p->id, "is sleeping\n");
		usleep(p->p->tosleep * 1000);
		if (p->p->someonedied)
			break;
		print_msg(p, p->id, "is thinking\n");
	}
	pthread_join(p->monitor, 0);
	return (0);
}


int		init_threads(t_p1 *p)
{
	int			i;

	i = -1;
	pthread_mutex_init(&p->isdying, 0); // CHECK FOR ERROR
	p->someonedied = 0;
	p->forks = malloc(sizeof(pthread_mutex_t) * p->nb); // CHECK FOR ERROR
	while (++i < p->nb)
		pthread_mutex_init(&p->forks[i], 0);
	i = -1;
	p->params = malloc(sizeof(t_params) * p->nb); // CHECK FOR ERROR
	while (++i < p->nb)
	{
		(&p->params[i])->id = i;
		(&p->params[i])->nbmeal = 0;
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
	int				i;

	if (ac < 5)
		return (-1);
	parse_arg(&philo, av); // CHECK IF 0
	pthread_mutex_init(&philo.print_mutex, 0);
	gettimeofday(&philo.time_start, 0);
	printf("OK ARGS nb:%d todie:%d toeat:%d tosleep:%d musteat:%d\n", philo.nb, philo.todie, philo.toeat, philo.tosleep, philo.musteat);
	init_threads(&philo);
	i =-1;
	while (++i < philo.nb)
		pthread_join(philo.threads[i], 0);
	return (0);
}