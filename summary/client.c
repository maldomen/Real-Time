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

#define MAX_BUFF 2048

char buff[MAX_BUFF],*usrnm,*ip,*pin,*pout;
int sdfwr,sdfrd;
void USR1_handler(){
    printf("\nSIGUSR1 tancant client\n");
    exit(0);
}

void * cl_wr(){
    struct addrinfo addr,*result,*rp;
    int s;
    char buffin[MAX_BUFF];
    memset(&addr,0,sizeof(addr));
    addr.ai_family=AF_INET;addr.ai_socktype=SOCK_STREAM;addr.ai_protocol=0;addr.ai_flags=0;
    

    s=getaddrinfo(ip,pin,&addr,&result);
    if(s!=0){printf("error getaddrinfo client pin\n");exit(0);}
    //provem de conectarnos als resultats de getaddrinfo
    for(rp=result;rp!=NULL;rp=rp->ai_next){
        sdfwr=socket(rp->ai_family,rp->ai_socktype,rp->ai_protocol);
        if(sdfwr==-1) continue;
        if(connect(sdfwr,rp->ai_addr,rp->ai_addrlen)!=-1) break; //sucess
        close(sdfwr);
    }
    freeaddrinfo(result);
    if(rp==NULL){printf("no s'ha pogut conectar client a pin\n");exit(0);} //fail

    sprintf(buffin,"%s",usrnm);
    //write(sdfwr,buff,sizeof(buff));
    //sleep(1);
    //printf("buffin:%s",buffin);
    printf("conectat al servei de chat\n");
    write(sdfwr,buffin,strlen(buffin));

    //send(sdfwr,buffin,strlen(buffin),MSG_MORE); //enviem usrnm
    while(1){
    memset(buffin,'\0',sizeof(buffin));//borrem tot el buffer
    //buffin[0]='\0';
    //printf("dins while\n");
    fgets(buffin,sizeof(buffin),stdin);
    write(sdfwr,buffin,strlen(buffin));
    //printf("despres send while return\n");
    }
}

void * cl_rd(){
    struct addrinfo addr,*result,*rp;
    int s;
    char buffout[MAX_BUFF];
    memset(&addr,0,sizeof(addr));
    addr.ai_family=AF_INET;addr.ai_socktype=SOCK_STREAM;addr.ai_protocol=0;addr.ai_flags=0;
    
    s=getaddrinfo(ip,pout,&addr,&result);
    if(s!=0){printf("error getaddrinfo client pout\n");exit(0);}
    //provem de conectarnos als resultats de getaddrinfo
    for(rp=result;rp!=NULL;rp=rp->ai_next){
        sdfrd=socket(rp->ai_family,rp->ai_socktype,rp->ai_protocol);
        if(sdfrd==-1) continue;
        if(connect(sdfrd,rp->ai_addr,rp->ai_addrlen)!=-1) break; //sucess
        close(sdfrd);
    }
    freeaddrinfo(result);
    if(rp==NULL){printf("no s'ha pogut conectar client pout\n");exit(0);} //fail
    while(1){
        memset(buffout,'\0',sizeof(buffout));//borrem tot el buffer
        read(sdfrd,buffout,sizeof(buffout));
        write(1,buffout,strlen(buffout));
    }

    /* read a fer
    while(1){
    sprintf(buff, "hola tio la puestada que llevo\n");
	write(sdfrd,buff, strlen(buff));
    sleep(2);
    */
}


int main(int argc,char **argv)
{   
    
    if (argc!=5){
		sprintf(buff, "La sintaxis es: client username serverip port-in port-out\n");
		write(1,buff, strlen(buff));
		return -1;
		
        }
    //VARIABLES SOCKT
    usrnm=argv[1];
    ip=argv[2];
    pin=argv[3];
    pout=argv[4];
    //pin!=pout
    if(strcmp(pin,pout)==0){
        printf("Port-in Port-out han de ser diferents\n");
        return -1;
    }
    //printf("usr;%s ip:%s pin%s pout%s\n",usrnm,ip,pin,pout);
    //pid del proces
    FILE *fproc=fopen("clientprocessid.txt","w+");
    fprintf(fproc,"%d",getpid());
    fflush(stdout);//ens asegurem que el fitxer sigui escrit 
    fclose(fproc);
    //SIGUSR1 acaba el programa
    struct sigaction mata={0};
    mata.sa_handler=USR1_handler;
    sigaction(SIGUSR1,&mata,NULL);
    //threads
    pthread_t write,read;
    pthread_create(&write,NULL,cl_wr,NULL);
    pthread_create(&read,NULL,cl_rd,NULL);
    //pthread_join(write,NULL);
    //pthread_join(read,NULL);
    while(1);
}