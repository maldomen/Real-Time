#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void handler(int s)
{
	printf("Numero de signal: %d\n", s);
}


int main()
{
	struct sigaction new_action={0};
	int signum;
	
	new_action.sa_handler = handler;
	sigaddset(&new_action.sa_mask,2);
	//sigemptyset(&new_action.sa_mask);
	
	for(signum = 1; signum<=64; signum++)
		sigaction(signum, &new_action, NULL);
		
	while(1)
		pause();
}




/*
Versio vella del programa, en el cas que oldaction=NULL && treure el newactions.sa.flags
el programa el segon cop que fas la mateixa signal fa laccio predeterminada. un cop has fet 2 signals diferents funciona normal


int main()
{
	struct sigaction new_action, old_action;
	int signum;
	
	new_action.sa_handler = handler;
	new_action.sa_flags = 0;
	sigemptyset(&new_action.sa_mask);
	
	for(signum = 1; signum<=64; signum++)
		sigaction(signum, &new_action, &old_action);
		
	while(1)
		pause();
}
*/