#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sched.h>

int num = 0;
int ready = 0;

void handler(int s)
{
	if (s == 10)
	{
		num++;
		kill(getppid(), SIGHUP);
	}
	else if (s == 12)
	{
		printf("Se han enviado SIGUSR1 %d veces\n", num);
		exit(0);
	}
	else if (s == 1)
	{
		ready = 1;
	}
}

int main()
{
	struct sigaction new_action;
	new_action.sa_flags = 0;
	sigemptyset(&new_action.sa_mask);
	new_action.sa_handler = handler;
	
	int r = fork();
	if (r == -1) exit(0);  // Error
	else if (r == 0)  // Aqui entra el hijo
	{
		sigaction(SIGUSR1, &new_action, NULL);
		sigaction(SIGUSR2, &new_action, NULL);
		while(1) 
		{
			pause();
		}
	}
	else  // Aqui entra el padre
	{
		sigaction(SIGHUP, &new_action, NULL);
		sleep(1);
		for (int i=0; i<1000; i++)
		{
			ready = 0;
			kill(r, SIGUSR1);
			while( ready == 0) sched_yield();
		}
		kill(r, SIGUSR2);
		waitpid(r,NULL,0);
	}
}
