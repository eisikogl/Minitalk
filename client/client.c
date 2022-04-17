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
    while (i < 8)
    {
        if (message[i] == 1)
        {
            if (kill(pid, SIGUSR1) == -1)
                printf("SIGUSR1 FAILED");   
        }
        else if (message[i] == 0)
        {
            if (kill(pid, SIGUSR2) == -1)
                printf("SIGUSR1 FAILED"); 
        }
        i++;
        usleep(500);
    }
    free(message);
}

int *encoder(char c)
{
    int *coded_char;
    int char_to_bit;
    int i;

    coded_char = malloc(sizeof(*coded_char) * 8);
    char_to_bit = (int)c;
    i = 7;
    while(char_to_bit)
    {
        coded_char[i] = char_to_bit % 2;
        char_to_bit /= 2;
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
        message = encoder(argv[2][i]);
        sender(message, pid);
        i++;
    }
}