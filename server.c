/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbronevy <vbronevy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 20:08:23 by vbronevy          #+#    #+#             */
/*   Updated: 2025/07/07 20:39:12 by vbronevy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	decode_signal_ft(int sig, pid_t sender_pid);

static void	handler(int sig, siginfo_t *info, void *more_info)
{
	static pid_t	client = 0;

	(void)more_info;
	if (info->si_pid)
		client = info->si_pid;
	decode_signal_ft(sig, client);
}

static void	decode_signal_ft(int sig, pid_t sender_pid)
{
	static char	c = 0;
	static int	bit = 0;

	if (sig == SIGUSR1)
		c |= (0x80 >> bit);
	else if (sig == SIGUSR2)
		c &= ~(0x80 >> bit);
	bit++;
	if (bit == CHAR_BIT)
	{
		bit = 0;
		if (c == '\0')
		{
			write(STDOUT_FILENO, "\n", 1);
			kill_ft(sender_pid, SIGUSR2);
			c = 0;
			return ;
		}
		write(STDOUT_FILENO, &c, 1);
		c = 0;
	}
	kill_ft(sender_pid, SIGUSR1);
}

int	main(int ac, char **av)
{
	(void)av;
	if (ac != 1)
	{
		fputs("Usage: ./server\n", stderr);
		return (EXIT_FAILURE);
	}
	printf("Server PID: %d\n", getpid());
	signal_ft(SIGUSR1, handler, true);
	signal_ft(SIGUSR2, handler, true);
	while (1337)
		pause();
	return (EXIT_SUCCESS);
}
