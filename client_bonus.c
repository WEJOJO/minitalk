/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhwang <nhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 11:26:44 by nhwang            #+#    #+#             */
/*   Updated: 2022/06/16 15:46:54 by nhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

t_glist	g_list;

int	ft_checknum(char str)
{
	if ((48 <= str) && (str <= 57))
		return (1);
	return (0);
}

int	ft_atoi(const char *s)
{
	const char	*st;
	int			buho;
	long long	num;

	num = 0;
	st = s;
	buho = 1;
	while (*st && ft_checknum(*st))
	{
		if (num * buho > 2147483647)
			return (-1);
		if (num * buho < -2147483648)
			return (0);
		num = (num * 10) + ((int)(*st) - 48);
		st++;
	}
	return ((int)num * buho);
}

void	handler(int sig, siginfo_t *info, void *context)
{
	(void)context;
	if (sig == SIGUSR2)
	{
		write(1, "second client", 14);
		exit(0);
	}
	else
		g_list.sv_pid = info->si_pid;
}

void	handler2(int sig, siginfo_t *info, void *context)
{
	static int	bitidx = 8;

	(void)context;
	(void)info;
	if (sig == SIGUSR2)
	{
		write(1, "complete from server", 21);
		exit(0);
	}
	if (bitidx <= 0)
	{
		g_list.string++;
		bitidx = 8;
		usleep(200);
	}
	if ((*(g_list.string) >> --bitidx) & 1)
		kill(g_list.sv_pid, SIGUSR2);
	else
		kill(g_list.sv_pid, SIGUSR1);
	usleep(200);
}

int	main(int argc, char *argv[])
{
	struct sigaction	sa;

	if (argc != 3)
		return (0);
	sa.sa_sigaction = handler;
	sa.sa_flags = SA_SIGINFO;
	sigaddset(&sa.sa_mask, SIGUSR1);
	sigaddset(&sa.sa_mask, SIGUSR2);
	if (sigaction(SIGUSR1, &sa, NULL) || sigaction(SIGUSR2, &sa, NULL))
		return (0);
	kill(ft_atoi(argv[1]), SIGUSR1);
	pause();
	sa.sa_sigaction = handler2;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGUSR1);
	sigaddset(&sa.sa_mask, SIGUSR2);
	if (sigaction(SIGUSR1, &sa, NULL) || sigaction(SIGUSR2, &sa, NULL))
		return (0);
	g_list.string = argv[2];
	kill(getpid(), SIGUSR1);
	while (1)
		pause();
}
