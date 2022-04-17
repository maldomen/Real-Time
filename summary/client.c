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

char buff[1024],*usrnm,*ip,*pin,*pout;

void USR1_handler(){
    printf("\nSIGUSR1 tancant client\n");
    exit(0);
}

void * cl_wr(){
    struct addrinfo addr,*result,*rp;
    int s,sdf;
    memset(&addr,0,sizeof(addr));
    addr.ai_family=AF_INET;addr.ai_socktype=SOCK_STREAM;addr.ai_protocol=0;addr.ai_flags=0;
    
    s=getaddrinfo(ip,pin,&addr,&result);
    if(s!=0){printf("error getaddrinfo client pin\n");exit(0);}
    //provem de conectarnos als resultats de getaddrinfo
    for(rp=result;rp!=NULL;rp=rp->ai_next){
        sdf=socket(rp->ai_family,rp->ai_socktype,rp->ai_protocol);
        if(sdf==-1) continue;
        if(connect(sdf,rp->ai_addr,rp->ai_addrlen)!=-1) break; //sucess
        close(sdf);
    }
    freeaddrinfo(result);
    if(rp==NULL){printf("no s'ha pogut conectar client a pin\n");exit(0);} //fail

    sprintf(buff, "%s\n",usrnm);
    write(sdf,buff,strlen(buff));
    while(1){
    sprintf(buff, "hola tio la puestada que llevo\n");
	write(sdf,buff, strlen(buff));
    sleep(2);
    }
}

void * cl_rd(){
    struct addrinfo addr,*result,*rp;
    int s,sdf;
    memset(&addr,0,sizeof(addr));
    addr.ai_family=AF_INET;addr.ai_socktype=SOCK_STREAM;addr.ai_protocol=0;addr.ai_flags=0;
    
    s=getaddrinfo(ip,pout,&addr,&result);
    if(s!=0){printf("error getaddrinfo client pout\n");exit(0);}
    //provem de conectarnos als resultats de getaddrinfo
    for(rp=result;rp!=NULL;rp=rp->ai_next){
        sdf=socket(rp->ai_family,rp->ai_socktype,rp->ai_protocol);
        if(sdf==-1) continue;
        if(connect(sdf,rp->ai_addr,rp->ai_addrlen)!=-1) break; //sucess
        close(sdf);
    }
    freeaddrinfo(result);
    if(rp==NULL){printf("no s'ha pogut conectar client pout\n");exit(0);} //fail
    while(1) printf("clienrd bee\n");
    /* read a fer
    while(1){
    sprintf(buff, "hola tio la puestada que llevo\n");
	write(sdf,buff, strlen(buff));
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
    printf("usr;%s ip:%s pin%s pout%s\n",usrnm,ip,pin,pout);
    //pid del proces
    FILE *fproc=fopen("clientprocessid.txt","w+");
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
    //pthread_create(&read,NULL,cl_rd,NULL);
    pthread_join(write,NULL);
    //pthread_join(read,NULL);
}