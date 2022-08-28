/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eisikogl <eisikogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 17:37:25 by eisikogl          #+#    #+#             */
/*   Updated: 2022/08/28 18:19:24 by eisikogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>

int	ft_atoi(char *str)
{
	long	num;
	int		i;

	i = 0;
	num = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
		num = num * 10 + (str[i++] - 48);
	return (num);
}

void	send_message(char message, int pid)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		if ((((message << i) & 128)))
			kill (pid, SIGUSR1);
		if (!((message << i) & 128))
			kill (pid, SIGUSR2);
		i++;
		usleep(80);
	}
}

int	main(int argc, char **argv)
{
	int	i;

	i = 0;
	if (argc == 3)
		while (argv[2][i])
			send_message(argv[2][i++], ft_atoi(argv[1]));
	else
		write (1, "./NAME (PID) (MESSAGE)", 22);
	return (0);
}
