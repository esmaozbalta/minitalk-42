#include "minitalk.h"

static	void	write_pid(pid_t	n)
{
	char	c;

	if (n > 9)
	{
		write_pid(n / 10);
		write_pid(n % 10);
	}
	else
	{
		c = 48 + n;
		write(1, &c, 1);
	}
}

static	void	control_signal(int	signal)
{
	static	char	c;
	static	int		i;

	i++;
	if (signal == SIGUSR1)
		c = c | 1; //karaktere 1 bit ekle
	if (i == 8) //8 bitin hepsi aktarildiysa
	{
		write(1, &c, 1); //ekrana yazdir
		i = 0; //bit i sifirla
		c = 0; //karakteri sifirla
	}
	c = c << 1; //bit i sola kaydirir
}

int	main(void)
{
	pid_t	server_pid;

	server_pid = getpid(); //pid degerini ata
	write_pid(server_pid); //pid degerini ekrana yazdir
	write(1, "\n", 1);
	signal(SIGUSR1, control_signal);//Program SIGUSR1 sinyalini aldığında, control_signal fonksiyonu otomatik olarak çalıştırılır.
	signal(SIGUSR2, control_signal);
	while(1)
	{
		write(1, "sinyal\n", 7);
		pause();
	}
	return (0);
}