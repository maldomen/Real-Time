#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int count = 0;
char buff[128];

void handler(int sig)
{
	if (sig == SIGALRM)
	{
		if (count == 0)
		{
			sprintf(buff, "Aqui estamos...\n");
		}
		else
		{
			sprintf(buff, "Aqui seguimos...\n");
		}
		write(1, &buff, strlen(buff));
		count++;
	}
	else if (sig == SIGINT)
	{
		sprintf(buff, "\nSe han mostrado %d mensajes\n", count);
		write(1, &buff, strlen(buff));
		exit(0);
	}
}

int main()
{
	struct sigaction new;
	new.sa_flags = 0;
	sigemptyset(&new.sa_mask);
	new.sa_handler = handler;
	sigaction(SIGINT, &new, NULL);
	sigaction(SIGALRM, &new, NULL);
	
	while(1) 
	{
		alarm(2);
		pause();
	}
}
