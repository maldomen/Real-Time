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
// TCP --> STREAM
// UDP --> DGRAM 	<--

#define MESAGE_SIZE 256
#define PORT 8080

int main()
{
	int s, b;
	char buff[MESAGE_SIZE];
	char cli[MESAGE_SIZE];
	struct sockaddr_in addr;
	
	s = socket(AF_INET, SOCK_DGRAM, 0);
	if (s < 0)
	{
		printf("Error creating socket\n");
		exit(0);
	}
	
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(PORT);
	
	int sndsize;
	int n;
	
	sprintf(cli, "Client connected");
	sendto(s, &cli, strlen(cli), 0, (struct sockaddr *)&addr, sizeof(addr));
	
	while(1)
	{
		n = recvfrom(s, buff, MESAGE_SIZE, 0, (struct sockaddr *)&addr, &sndsize);
		buff[n] = '\0';
		printf("%s\n", buff);
	}
}
