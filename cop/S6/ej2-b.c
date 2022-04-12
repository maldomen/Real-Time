#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sched.h>

int main()
{
	int fd, size;
	long a;
	char buff[256];
	
	mkfifo("pipe_P6_2", 0666);
	fd = open("pipe_P6_2", O_RDONLY);
	
	while(1)
	{
		read(fd, &size, sizeof(int));
		read(fd, buff, size);
		printf("%s", buff);
		
		read(fd, &a, sizeof(long));
		printf("%ld\n", a);
		
		sched_yield();
	}
}
