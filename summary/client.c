#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sched.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
void USR1_handler(){
    printf("\nSIGUSR1 tancant client\n");
    exit(0);
}
int main()

{   //usr 1 acaba el programa
    struct sigaction mata={0};
    mata.sa_handler=USR1_handler;
    sigaction(SIGUSR1,&mata,NULL);
    pid_t pid=getpid();
    printf("holaa%d",pid);
    fprintf(fopen("processid.txt","w+"),"%d",pid);
    while(1);
}