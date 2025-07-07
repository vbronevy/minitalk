/* ************************************************************************** */
/*									  */
/*							:::	 ::::::::   */
/*   utils.c											:+:   :+:	:+:   */
/*						  +:+ +:+	   +:+	*/
/*   By: vbronevy <vbronevy@student.42.fr>	  +#+  +:+	   +#+	*/
/*						+#+#+#+#+#+   +#+	 */
/*   Created: 2025/07/07 20:08:28 by vbronevy		#+#  #+#		  */
/*   Updated: 2025/07/07 20:34:04 by vbronevy	   ###   ########.fr	*/
/*									  */
/* ************************************************************************** */

#include "minitalk.h"

void	signal_ft(int sig, void *handler, bool use_siginfo)
{
	struct sigaction	sa;

	sa = (struct sigaction){0};
	if (use_siginfo)
	{
		sa.sa_sigaction = handler;
		sa.sa_flags = SA_SIGINFO;
	}
	else
		sa.sa_handler = handler;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGUSR1);
	sigaddset(&sa.sa_mask, SIGUSR2);
	if (sigaction(sig, &sa, NULL) < 0)
	{
		perror("signal handler setup failed");
		exit(EXIT_FAILURE);
	}
}

void	kill_ft(pid_t pid, int signum)
{
	if (kill(pid, signum) < 0)
	{
		perror("signal transmission failed");
		exit(EXIT_FAILURE);
	}
}

void	print_pending_signals(void)
{
	sigset_t	pending;
	int			i;

	i = 1;
	if (sigpending(&pending) == -1)
	{
		perror("sigpending");
		exit(EXIT_FAILURE);
	}
	printf("\n=== Pending signals ===\n");
	while (i < NSIG)
	{
		if (sigismember(&pending, i))
		{
			printf("signal %d (%s) is pending\n", i, strsignal(i));
		}
		i++;
	}
	printf("=======================\n\n");
}

void	print_blocked_signals(void)
{
	sigset_t	blocked;
	int			i;

	i = 1;
	if (sigprocmask(SIG_BLOCK, NULL, &blocked) == -1)
	{
		perror("sigprocmask");
		exit(EXIT_FAILURE);
	}
	printf("\n=== Blocked signals ===\n");
	while (i < NSIG)
	{
		if (sigismember(&blocked, i))
		{
			printf("signal %d (%s) is blocked\n", i, strsignal(i));
		}
		i++;
	}
	printf("=======================\n");
}
