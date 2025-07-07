/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbronevy <vbronevy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 20:08:16 by vbronevy          #+#    #+#             */
/*   Updated: 2025/07/07 21:27:21 by vbronevy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

#define BUSY 0
#define READY 1

static sig_atomic_t	client_state(int set)
{
	static volatile sig_atomic_t	state = BUSY;

	if (set != -1)
		state = set;
	return (state);
}

static void	end_handler(int sig)
{
	(void)sig;
	fputs("\n\t✅ Message received ✅\n", stdout);
	exit(EXIT_SUCCESS);
}

static void	ack_handler(int sig)
{
	(void)sig;
	client_state(READY);
}

static void	send_char(char c, pid_t kingkai)
{
	int	bit;

	bit = 0;
	while (bit < CHAR_BIT)
	{
		if (c & (0x80 >> bit))
			kill_ft(kingkai, SIGUSR1);
		else
			kill_ft(kingkai, SIGUSR2);
		bit++;
		while (client_state(-1) == BUSY)
			usleep(42);
		client_state(BUSY);
	}
}

int	main(int ac, char **av)
{
	pid_t	kingkai;
	char	*message;
	int		i;

	if (ac != 3)
	{
		fputs("Usage: ./client <kingkai> \"message\"\n", stderr);
		return (EXIT_FAILURE);
	}
	kingkai = atoi(av[1]);
	message = av[2];
	signal_ft(SIGUSR1, ack_handler, false);
	signal_ft(SIGUSR2, end_handler, false);
	i = 0;
	while (message[i])
		send_char(message[i++], kingkai);
	send_char('\0', kingkai);
	return (EXIT_SUCCESS);
}
