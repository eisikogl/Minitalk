#include <signal.h>
#include <stdio.h>
#include <stdlib.h> 
#include <unistd.h>

char *message;
int	ft_atoi(char *str)
{
	int	number;

	number = 0;
	while (*str)
		number = (10 * number) + (*str++ - 48);
	return (number);
}

void sender(int *message, int pid)
{
    int i = 0;  
    while (i < 7)
    {
        if (message[i] == 1)
            kill(pid, SIGUSR1);   
        else if (message[i] == 0)
            kill(pid, SIGUSR2);
        i++;
        usleep(500);
    }
    free(message);
}

int *encoder(char c)
{
    int *coded_char;
    int cd;
    int i;

    coded_char = malloc(sizeof(*coded_char) * 8);
    cd = (int)c;
    i = 7;
    while(cd)
    {
        coded_char[i] = cd % 2;
        cd /= 2;
        i--;
    }
    while(i >= 0)
    {
        coded_char[i] = 0;
        i--;
    }
    return (coded_char);
}

int main(int argc, char **argv)
{
    int pid;
    int i;
    int *message;

    i = 0;
    pid = ft_atoi(argv[1]);
    
    while(argv[2][i])
    {
        printf("Successfully sent characters: %d\n",i);
        message = encoder(argv[2][i]);
        sender(message, pid);
        i++;
    }
    sleep(5);
    
}