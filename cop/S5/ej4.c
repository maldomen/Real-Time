#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

int power(int x, int y)
	{
	int res = 1;
	int i = y;
	if (y < 0) res = -1;
	else if (y = 0) res = 1;
	else 
	{
		while (i > 0)
		{
			res = res * x;
			i--;
		}
	}
	return res;
}

int AsciiToInteger(char *sr1)
{
   	int l = strlen(sr1);
   	int res = 0;
	for (int i=0; i<l; i++)
	{
		if ((*sr1 >= '0' && *sr1 <= '9') && (res != -1))
		{
			res = res + ((*sr1-'0')*power(10, l-i-1));
		}
		else
		{
			res = -1;
		}
		sr1++;
	}
	return res;
} 

void handler(int s)
{
	if (s == SIGCHLD)
	{
		char buff[256];
		int pid, res;
		
		pid = waitpid(-1, &res, 0);
		sprintf(buff, "El hijo con PID %d ha sido el primero en terminar con un retorno %d\n", pid, res);
		write(1, &buff, strlen(buff));
		exit(0);
	}
}

void child_action()
{
	int j;
	char buff[256];
	sleep(1);
	for (int j=1; j<=1000; j++)
	{
		sprintf(buff, "El hijo con pid %d ha trabajado %d veces\n", getpid(), j);
		write(1, &buff, strlen(buff));
	}
	exit(0);
}

int main(int argc, char**argv)
{
	char buff[256];
	int i,r, num_child;
	struct sigaction new;
	
	if (argc == 1)
	{
		sprintf(buff, "Error, sintaxis: ej4.c (int)numero_de_hijos\n");
		write(1, &buff, strlen(buff));
		exit(0);
	}
	
	new.sa_flags = 0;
	sigemptyset(&new.sa_mask);
	new.sa_handler = handler;
	sigaction(SIGCHLD, &new, NULL);
	
	num_child = AsciiToInteger(argv[1]);
	for (i=0; i<num_child; i++)
	{
		r = fork();
		if (r <= -1)
		{
			sprintf(buff, "Error generando hijos\n");
			write(1, &buff, strlen(buff));
		}
		if (r == 0) child_action();
	}
	sigsuspend(&new.sa_mask);
}
