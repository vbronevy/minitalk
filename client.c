/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaddrul <hbaddrul@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 17:58:19 by hbaddrul          #+#    #+#             */
/*   Updated: 2021/11/24 16:06:30 by hbaddrul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include "utils.h"

static volatile sig_atomic_t   g_ack = 0;

static void     action(int sig)
{
        static int      received = 0;
        static int      bits = 0;

        if (sig == SIGUSR1)
        {
                if (++bits == 8)
                {
                        ++received;
                        bits = 0;
                }
                g_ack = 1;
        }
        else
        {
                ft_putnbr_fd(received, 1);
                ft_putchar_fd('\n', 1);
                exit(0);
        }
}


static void	mt_kill(int pid, char *str)
{
	int		i;
	char	c;

	while (*str)
	{
		i = 8;
		c = *str++;
		while (i--)
		{
                        if (c >> i & 1)
                                kill(pid, SIGUSR2);
                        else
                                kill(pid, SIGUSR1);
                        while (!g_ack)
                                pause();
                        g_ack = 0;
                }
        }
        i = 8;
        while (i--)
        {
                kill(pid, SIGUSR1);
                while (!g_ack)
                        pause();
                g_ack = 0;
        }
}

int	main(int argc, char **argv)
{
	if (argc != 3 || !ft_strlen(argv[2]))
		return (1);
	ft_putstr_fd("Sent    : ", 1);
	ft_putnbr_fd(ft_strlen(argv[2]), 1);
	ft_putchar_fd('\n', 1);
	ft_putstr_fd("Received: ", 1);
	signal(SIGUSR1, action);
	signal(SIGUSR2, action);
	mt_kill(ft_atoi(argv[1]), argv[2]);
	while (1)
		pause();
	return (0);
}
