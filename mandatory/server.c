/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anktiri <anktiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 16:43:34 by anktiri           #+#    #+#             */
/*   Updated: 2025/03/18 01:43:47 by anktiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	handle_signal(int sig)
{
	static int	bit_count = 0;
	static char	c = 0;

	if (sig == SIGUSR1)
		c = (c << 1);
	else if (sig == SIGUSR2)
		c = (c << 1) | 1;
	bit_count++;
	if (bit_count == 8)
	{
		if (c == 1)
			ft_putstr_fd("\n\e[94m## New message ##\n\e[92m", 1);
		else if (c == '\0')
			ft_putstr_fd("\n\e[0m", 1);
		else
		{
			ft_putstr_fd("\e[92m", 1);
			write(1, &c, 1);
		}
		bit_count = 0;
		c = 0;
	}
}

int	main(void)
{
	ft_putstr_fd("\e[92mserver [PID = ", 1);
	ft_putnbr(getpid());
	ft_putstr_fd("]\n\e[0m", STDOUT_FILENO);
	signal(SIGUSR1, handle_signal);
	signal(SIGUSR2, handle_signal);
	while (1)
		pause();
	return (0);
}
