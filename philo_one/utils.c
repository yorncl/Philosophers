#include <philo_one.h>

int		ft_strlen(char *str)
{
	int len;

	len = 0;
	while (str)
	{
		len++;
		str++;
	}
	return (len);
}

void	ft_putstr_fd(int fd, char *str, int len)
{
	write(fd, str, len);
}
//No neg for now
void	ft_putnbr_fd(int fd, int nb)
{
	if (nb > 10)
		ft_putnbr_fd(fd, nb / 10);
	write(fd, &('0' + nb), 1 );
}