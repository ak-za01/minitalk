/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anktiri <anktiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 23:43:03 by anktiri           #+#    #+#             */
/*   Updated: 2025/03/18 16:42:08 by anktiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

static void	handle_signal(int sig, siginfo_t *info, void *context)
{
	static int	bit_count = 0;
	static char	c = 0;
	static int	current_pid = 0;

	(void)context;
	if (current_pid != info->si_pid)
		bit_count = ((c = 0, current_pid = info->si_pid), 0);
	if (sig == SIGUSR1)
		c = (c << 1);
	else
		c = (c << 1) | 1;
	if (++bit_count == 8)
	{
		if (c == 1)
			ft_putstr_fd("\n\e[94m## New message ##\n\e[92m", 1);
		else if (c == '\0')
		{
			ft_putstr_fd("\n\e[0m", 1);
			kill(info->si_pid, SIGUSR1);
		}
		else
			write(1, &c, 1);
		bit_count = 0;
		c = 0;
	}
}

int	main(void)
{
	struct sigaction	sa;

	ft_putstr_fd("\e[92mserver [PID = ", 1);
	ft_putnbr(getpid());
	ft_putstr_fd("]\n\e[0m", 1);
	sa.sa_sigaction = handle_signal;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}
