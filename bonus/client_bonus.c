/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anktiri <anktiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 23:43:08 by anktiri           #+#    #+#             */
/*   Updated: 2025/03/18 16:26:25 by anktiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

static void	acknowledge_signal(int sig)
{
	if (sig == SIGUSR1)
		ft_putstr_fd("\e[92m## server has acknowledge your message ##\n\e[0m", 1);
	exit(0);
}

static void	send_char(int pid, char c)
{
	int	i;

	i = 7;
	while (i >= 0)
	{
		if ((c >> i) & 1)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		usleep(150);
		i--;
	}
}

static void	send_string(int pid, const char *str)
{
	send_char(pid, 1);
	while (*str)
	{
		send_char(pid, *str);
		str++;
	}
	send_char(pid, '\0');
}

int	main(int argc, char **argv)
{
	int	pid;

	if (argc != 3)
	{
		ft_putstr_fd("\e[31m## error - incorrect syntax ##\n\e[0m", 1);
		ft_putstr_fd("\e[92m./client <the server PID> <the string to send>\n\e[0m",
			1);
		return (1);
	}
	pid = ft_atoi(argv[1]);
	if (pid == -1 || kill(pid, 0) < 0)
	{
		ft_putstr_fd("\e[31m## error - PID is invalid ##\n\e[0m", 2);
		return (1);
	}
	signal(SIGUSR1, acknowledge_signal);
	send_string(pid, argv[2]);
	pause();
	return (0);
}
