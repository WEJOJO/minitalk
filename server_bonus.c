/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhwang <nhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 11:26:40 by nhwang            #+#    #+#             */
/*   Updated: 2022/06/16 16:03:16 by nhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

int	ft_putnbr_fd(int n, int fd, int len)
{
	char	c;

	if (n < 0)
	{
		if (n == -2147483648)
		{
			write(fd, "-2147483648", 11);
			return (11);
		}
		write(fd, "-", 1);
		len++;
		n = n * (-1);
	}
	if (n >= 10)
	{
		len = ft_putnbr_fd(n / 10, fd, len);
		c = (n % 10) + '0';
	}
	else
		c = n + '0';
	write(fd, &c, 1);
	len++;
	return (len);
}

void	ft_end(t_person *list)
{
	kill(list->si_pid, SIGUSR2);
	list->si_pid = 0;
	write(1, "\nFinish\n", 9);
}

void	sa_handler_user(int sig, siginfo_t *info, void *context)
{
	static t_person	list;

	(void)context;
	if (list.si_pid == 0)
	{
		list.si_pid = info->si_pid;
		kill(info->si_pid, SIGUSR1);
		return ;
	}
	if (list.si_pid == info->si_pid)
	{
		list.buf <<= 1;
		if (sig == SIGUSR2)
			list.buf = list.buf + 1;
		if (++list.index == 8)
		{
			write (1, &list.buf, 1);
			list.index = 0;
			if (list.buf == '\0')
				return (ft_end(&list));
		}
		kill(info->si_pid, SIGUSR1);
	}
	else
		kill(info->si_pid, SIGUSR2);
}

int	main(void)
{
	pid_t					test;
	struct sigaction		sa;

	test = getpid();
	ft_putnbr_fd(test, 1, 0);
	write(1, "\n", 2);
	sa.sa_sigaction = sa_handler_user;
	sa.sa_flags = SA_SIGINFO;
	sigaddset(&sa.sa_mask, SIGUSR1);
	sigaddset(&sa.sa_mask, SIGUSR2);
	if (sigaction(SIGUSR1, &sa, NULL) || sigaction(SIGUSR2, &sa, NULL))
		return (0);
	while (1)
		pause();
	return (0);
}
