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
// TCP --> STREAM
// UDP --> DGRAM 	<--

#define MESAGE_SIZE 256
#define PORT 8080

int main(int argc, char** argv)
{
	int s, b;
	int i = 1;
	long a = 0;
	char buff[MESAGE_SIZE];
	char aux[(MESAGE_SIZE/2)];
	char cli[MESAGE_SIZE];
	struct sockaddr_in servaddr, cliaddr;
	
	s = socket(AF_INET, SOCK_DGRAM, 0);
	if (s < 0)
	{
		printf("Error creating socket\n");
		exit(0);
	}
	
	memset(&servaddr, 0, sizeof(servaddr));
	memset(&cliaddr, 0, sizeof(cliaddr));
	
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = INADDR_ANY;
	servaddr.sin_port = htons(PORT);
	
	b = bind(s, (const struct sockaddr *)&servaddr, sizeof(servaddr));
	if (b < 0)
	{
		printf("Error binding socket\n");
		exit(0);
	}
	
	sprintf(aux, "Server: ");
	while(i<argc)
	{
		strcat(aux , argv[i]);
		strcat(aux , " ");
		i++;
	}
	printf("%s\n", aux);
	
	printf("Waiting for client\n");
	int clisize = sizeof(cliaddr);
	int n = recvfrom(s, &cli, MESAGE_SIZE, 0, (struct sockaddr *)&cliaddr, &clisize);
	cli[n] = '\0';
	printf("%s\n", cli);
	
	while(1)
	{
		sprintf(buff, "%s%ld", aux, a);
		a++;
		sendto(s, buff, strlen(buff), 0, (struct sockaddr *)&cliaddr, clisize);
	}	
}
