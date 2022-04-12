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
