#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sched.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>

#define BUFF_SIZE 8192
#define MESAGE_SIZE 256
#define MAX_MSG 100

int main()
{
	char buff[BUFF_SIZE];	
	mqd_t mem;

	mem = mq_open("/cola", O_RDONLY);
	
	while(1)
	{
		mq_receive(mem, buff, BUFF_SIZE, NULL);
		printf("%s\n", buff);
		sched_yield();
	}
	mq_close(mem);
}
