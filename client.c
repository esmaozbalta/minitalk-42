#include "minitalk.h"

static	int	ft_atoi(const char	*str)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	result = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = (result * 10) + (str[i] - 48);
		i++;
	}
	return (sign * result);
}

static	void	send_signal(pid_t	id, char	*message)
{
	int	i;
	int	j;
	char	result;

	i = 0;
	while (message[i] != '\0')
	{
		j = 7; //index 0 1 2 3 4 5 6 7 (8 bit)
		while (j >= 0)
		{
			result = (message[i] >> j) & 1; // (>> j kadar saga kaydirma) j inci indexi alir ve 1 e esit ise 1 dondurur.
			if (result == 1)
				kill(id, SIGUSR1); //sinyali gonderir
			else if (result == 0)
				kill(id, SIGUSR2);
			usleep(500); //yarim milisaniye bekler
			j--;
		}
		i++;
	}
}

int	main(int ac, char *av[])
{
	pid_t	server_pid;

	if (ac == 3)
	{
		server_pid = ft_atoi(av[1]); //pid degerini int e cevirir server_pid e atar
		send_signal(server_pid, av[2]); //pid degerini ve girilen mesaji send_signale yollar
	}
	else
		write(1, "Error\n", 6);
	return (0);
}