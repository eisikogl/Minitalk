#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	ft_itoa(pid_t pid)
{
	char	c;

	if (pid >= 10)
		ft_itoa(pid / 10);
	c = (pid % 10) + 48;
	write(1, &c, 1);
}

char decoder(int *its_a_byte)
{
	int i;
	int n;
	int sum;

	sum = 0;
	n = 7;
	i = 0;
	while(i < 8)
	{
		sum += its_a_byte[i] * (2^n);
		n--;
		i++;
	}
	return (char)sum;
}

void get_char(int signum)
{
	static int decode_this[8];
	static int	i = 0;
	char	c;

	if (signum == SIGUSR1)
    {
		decode_this[i++] = 1;
    }
    else if(signum == SIGUSR2)
    {
		decode_this[i++] = 0;
    }
	if (i == 8)
	{
		c = decoder(decode_this);
		write(1, &c, 1);
		i = 0;
	}
}

int main()
{
	write(1, "Server Pid: ", 13);
	ft_itoa(getpid());
	write(1, "\n", 1);
	while(1)
	{
		signal(SIGUSR1,get_char);
		signal(SIGUSR2,get_char);
	}
	pause();
}