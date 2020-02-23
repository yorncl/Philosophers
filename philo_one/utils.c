#include <philo_one.h>

int		ft_strlen(char *str)
{
	int len;

	len = 0;
	while (*str)
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
void	ft_putunsigned_fd(int fd, unsigned long long int nb)
{
	char c;

	if (nb >= 10)
		ft_putunsigned_fd(fd, nb / 10);
	c = '0' + nb % 10;
	write(fd, &c, 1);
}