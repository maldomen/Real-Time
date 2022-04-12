#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sched.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>

#define MESAGE_SIZE 256
#define MAX_MSG 100

int main(int argc, char** argv)
{
	char buff[MESAGE_SIZE];
	char aux[(MESAGE_SIZE/2)];
	long a;
	int i = 1;
	mqd_t mem;
	
	mem = mq_open("/cola", O_RDWR|O_CREAT, 0777, NULL);
	
	while(i<argc)
	{
		strcat(aux , argv[i]);
		strcat(aux , " ");
		i++;
	}
	
	while(1)
	{
		sprintf(buff, "%s %ld", aux, a);
		//printf("%s", buff);
		mq_send(mem, buff, sizeof(buff), 0);
		a++;
		sched_yield();
	}

	mq_close(mem);
}

