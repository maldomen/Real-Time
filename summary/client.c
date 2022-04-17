#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <signal.h>
#include <sched.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>

char buff[256],*usrnm,*ip,*pin,*pout;

void USR1_handler(){
    printf("\nSIGUSR1 tancant client\n");
    exit(0);
}

void * cl_wr(){
    int fdwr=socket(AF_INET,SOCK_STREAM,0);

    sprintf(buff, "hola\n");
	write(1,buff, strlen(buff));
    while(1);
}

void * cl_rd(){
    sprintf(buff,"hola\n");
	write(1,buff, strlen(buff));
    
}


int main(int argc,char **argv)
{   
    //VARIABLES SOCKT
    usrnm=argv[1];
    ip=argv[2];
    pin=argv[3];
    pout=argv[4];
    printf("usr;%s ip:%s pin%s pout%s\n",usrnm,ip,pin,pout);
    if (argc!=5){
		sprintf(buff, "La sintaxis es: client username serverip port-in port-out\n");
		write(1,buff, strlen(buff));
		return -1;
		
        }
    
    //pid del proces
    FILE *fproc=fopen("processid.txt","w+");
    fprintf(fproc,"%d",getpid());
    fflush(stdout);//ens asegurem que el fitxer sigui escrit encara que no acabi en \n
    fclose(fproc);
    //SIGUSR1 acaba el programa
    struct sigaction mata={0};
    mata.sa_handler=USR1_handler;
    sigaction(SIGUSR1,&mata,NULL);
    //threads
    pthread_t write,read;
    pthread_create(&write,NULL,cl_wr,NULL);
    pthread_create(&read,NULL,cl_rd,NULL);
    while(1);
}