/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esozbalt <esozbalt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 18:59:40 by esozbalt          #+#    #+#             */
/*   Updated: 2024/07/01 20:46:46 by esozbalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static void	control_signal(int signal)
{
	static char	c;
	static int	i;

	i++;
	if (signal == SIGUSR1)
		c = c | 1;
	if (i == 8)
	{
		write (1, &c, 1);
		i = 0;
		c = 0;
	}
	c = c << 1;
}

int	main(void)
{
	pid_t	server_pid;

	server_pid = getpid();
	write_pid(server_pid);
	write(1, "\n", 1);
	signal(SIGUSR1, control_signal);
	signal(SIGUSR2, control_signal);
	while (1)
	{
		pause();
	}
	return (0);
}
