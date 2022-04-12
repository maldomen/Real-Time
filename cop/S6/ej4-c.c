#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sched.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <netdb.h>

// SERVER PROGRAM
// TCP --> STREAM	<--
// UDP --> DGRAM

#define MESAGE_SIZE 256
#define PORT 8080

int main(int argc, char** argv)
{
	int fd, fd2, b;
	int i = 1;
	long a = 0;
	char buff[MESAGE_SIZE];
	char aux[(MESAGE_SIZE/2)];
	struct sockaddr_in addr, cliaddr;
	
	fd = socket(AF_INET, SOCK_STREAM, 0);
	if (fd == -1)
	{
		printf("Error creating socket\n");
		exit(0);
	}
	
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(PORT);
	
	b = bind(fd, (struct sockaddr*) &addr, sizeof(addr));
	if (b == -1)
	{
		printf("Error binding socket\n");
		exit(0);
	}
	
	if(listen(fd, 2) == -1)
	{
		printf("Error configurating connectios");
		exit(0);
	}
	
	int addrsize = sizeof(cliaddr);
	fd2 = accept(fd, (struct sockaddr*)&cliaddr, &addrsize);
	if(fd2 < 0)
	{
		printf("Error accepting connection");
		exit(0);
	}
	
	while(i<argc)
	{
		strcat(aux , argv[i]);
		strcat(aux , " ");
		i++;
	}
	
	while(1)
	{
		sprintf(buff, "%s%ld", aux, a);
		a++;
		write(fd2, buff, sizeof(buff));
	}
}

