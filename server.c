/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eisikogl <eisikogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 17:37:34 by eisikogl          #+#    #+#             */
/*   Updated: 2022/08/28 18:26:17 by eisikogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>

void	ft_itoa(pid_t pid)
{
	char	c;

	if (pid >= 10)
		ft_itoa(pid / 10);
	c = (pid % 10) + 48;
	write(1, &c, 1);
}

char	bits_to_char(char *str)
{
	int		i;
	int		num;

	i = 0;
	num = 0;
	while (i < 8)
		num = num * 2 + str[i++];
	return ((char)num);
}

void	get_bits(int signum)
{
	static int	i = 0;
	char		str[8];
	char		m;

	if (signum == SIGUSR1)
		str[i++] = 1;
	else if (signum == SIGUSR2)
		str[i++] = 0;
	if (i == 8)
	{
		m = bits_to_char(str);
		write(1, &m, 1);
		i = 0;
	}
}

int	main(void)
{
	write (1, "Server Pid: ", 13);
	ft_itoa (getpid());
	write (1, "\n", 1);
	while (1)
	{
		signal(SIGUSR1, get_bits);
		signal(SIGUSR2, get_bits);
		pause();
	}
}
