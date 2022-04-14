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
#include <arpa/inet.h>

// CLIENT PROGRAM
// TCP --> STREAM	<--
// UDP --> DGRAM

#define MESAGE_SIZE 256
#define PORT 8080

int main()
{
	int fd = socket(AF_INET, SOCK_STREAM, 0);
	if (fd == -1)
	{
		printf("Error creating socket\n");
		exit(0);
	}
	
	struct addrinfo addr, *serv;
	char hostip[10] = "0.0.0.0";
	char port[10] = "8080";
	memset(&addr, 0, sizeof(addr));
	addr.ai_family = AF_UNSPEC;
	addr.ai_socktype = SOCK_STREAM;
	addr.ai_flags = AI_PASSIVE;
	int rv = getaddrinfo(hostip, port, &addr, &serv);
	if (rv == -1)
	{
		printf("Error getting socket IP\n");
		exit(0);
	}
	
	struct addrinfo *p;
	char s[INET6_ADDRSTRLEN];
	for(p=serv; p!=NULL; p=p->ai_next)
	{
		inet_ntop(p->ai_family, p->ai_addr, s, sizeof(s));
		if(connect(fd, p->ai_addr, p->ai_addrlen) == -1)
		{
			printf("Error connecting to server");
		}
		break;
	}
	freeaddrinfo(serv);
	
	char buff[MESAGE_SIZE];
	while(1)
	{
		read(fd, buff, MESAGE_SIZE);
		printf("%s\n", buff);
	}
}




















