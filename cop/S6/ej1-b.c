#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sched.h>

int main()
{
	int fd;
	long a;
	
	mkfifo("pipe_P6_1", 0666);
	fd = open("pipe_P6_1", O_RDONLY);
	
	while(1)
	{
		read(fd, &a, sizeof(long));
		printf("%ld\n",a);
		sched_yield();
	}
}
