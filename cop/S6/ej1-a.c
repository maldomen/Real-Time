#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sched.h>

int main()
{
	int fd;
	long a=0;
	
	mkfifo("pipe_P6_1", 0666);
	fd = open("pipe_P6_1", O_WRONLY);
	
	while(1)
	{
		write(fd, &a, sizeof(long));
		a++;
		sched_yield();
	}
}
