#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sched.h>

int main(int argc, char**argv)
{
	int fd, i;
	long a=0;
	char buff[256];
	char aux[128];
	
	mkfifo("pipe_P6_2", 0666);
	fd = open("pipe_P6_2", O_WRONLY);
	
	for(i=1; i<argc; i++)
	{
		strcat(buff , argv[i]);
		strcat(buff , " ");
	}

	while(1)
	{	
		int size = strlen(buff);
		write(fd, &size, sizeof(int));
		write(fd, buff, size);
		
		write(fd, &a, sizeof(long));
		a++;
		
		sched_yield();
	}
}
