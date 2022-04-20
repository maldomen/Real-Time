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
#include <semaphore.h>
#include <errno.h>

#define MAX_CLIENTS 100
#define MAX_BUFF 2048

struct clients{
    int fd_in,fd_out,estat;
    char usrnm[100];
    
};

struct clients client[MAX_CLIENTS]; //vector global clients
sem_t sem;
int server_fd_in,server_fd_out, new_socket_in,new_socket_out;
long int numclient;//numero total clients

void *thdatclient(void*arg){
    long int clnum=*(int*)arg;
    
    //printf("argument pasat a thd%ld, usr de thd:%s\n",clnum,client[clnum].usrnm);
    sem_post(&sem);
    int connected=1;
    client[clnum].estat=1;
    char msg[MAX_BUFF],msgusr[MAX_BUFF];
    while(connected!=0){
        //printf("dise\n");
        memset(msg,'\0',sizeof(msg));//borrem tot el buffer
        memset(msgusr,'\0',sizeof(msgusr));//borrem tot el buffer
        connected=read(client[clnum].fd_in,msg,sizeof(msg));
        if(connected>0){
            sprintf(msgusr,"%s",client[clnum].usrnm);
            strcat(msgusr,msg);//juntar username amb missatge
            //printf("valor al byuff:%s",msgusr);
            for(int i=0;i<numclient;i++){
            
                if(clnum!=i && client[i].estat!=0)write(client[i].fd_out,msgusr,strlen(msgusr));
            }
        }

    }
    printf("client %s desconecat\n",client[clnum].usrnm);
    client[clnum].estat=0;//client mort, amb aquest disseny de thread de server es complicat borrarlo de la llista i que els demes el seu numero de client --
    close(client[clnum].fd_in);
    close(client[clnum].fd_in);
    
}

void USR2_handler(){
    printf("\nSIGUSR2 tancant client\n");
    for(int j=0;j<numclient;j++){
        close(client[j].fd_in);
        close(client[j].fd_out);
        
    }
    close(new_socket_in);
    close(new_socket_out);
    close(server_fd_in);
    close(server_fd_out);
    
    exit(0);
}

int main(int argc,char** argv)
{  
    if (argc != 3) {
               fprintf(stderr, "Usage: %s portin portout\n", argv[0]);
               exit(EXIT_FAILURE);
           }
    //VARIABLES SOCKT
    
    char *pin=argv[1],*pout=argv[2];
    //printf("pin %s pout %s\n",pin,pout);
    //pin!=pout
    if(strcmp(pin,pout)==0){
        printf("Port-in Port-out han de ser diferents\n");
        return -1;
    }
    //pid del proces
    FILE *fproc=fopen("serverprocessid.txt","w+");
    fprintf(fproc,"%d",getpid());
    fflush(stdout);//ens asegurem que el fitxer sigui escrit encara que no acabi en \n
    fclose(fproc);
    //SIGUSR2 acaba el programa
    struct sigaction mata={0};
    mata.sa_handler=USR2_handler;
    sigaction(SIGUSR2,&mata,NULL);
    //sockets
    int valread;
    struct sockaddr_in adress_in,adress_out;
    int addrlenin = sizeof(adress_in),addrlenout = sizeof(adress_out);
    char buffer[MAX_BUFF];
    pthread_t id[MAX_CLIENTS];

    // Creating socket file descriptor
    
    if ((server_fd_in = socket(AF_INET, SOCK_STREAM, 0))
        == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port pin
    /*if (setsockopt(server_fd_in, IPPROTO_TCP,
                   SO_REUSEADDR, &opt, reuseaddr per poder reutilitzar adreses locals reuse port ens deixaria bindejar mes de un socket a un mateix port
                   sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }*/
    adress_in.sin_family = AF_INET;
    adress_in.sin_addr.s_addr = INADDR_ANY;
    adress_in.sin_port = htons(atoi(pin));
    // Forcefully attaching socket to the port pin
    if (bind(server_fd_in, (struct sockaddr*)&adress_in,
             sizeof(adress_in))
        < 0) {
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd_in, 5) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    //mateix procediment socket2
    //*************************
    if ((server_fd_out = socket(AF_INET, SOCK_STREAM, 0))
        == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port pin
    /*if (setsockopt(server_fd_out, SOL_SOCKET,
                   SO_REUSEADDR | SO_REUSEPORT, &opt, //reuseaddr per poder reutilitzar adreses locals reuse port ens deixaria bindejar mes de un socket a un mateix port
                   sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }*/
    adress_out.sin_family = AF_INET;
    adress_out.sin_addr.s_addr = INADDR_ANY;
    adress_out.sin_port = htons(atoi(pout));
    // Forcefully attaching socket to the port pin
    if (bind(server_fd_out, (struct sockaddr*)&adress_out,
             sizeof(adress_out))
        < 0) {
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd_out, 5) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }


    //************************
    sem_init(&sem,0,0);
    int msglen;
    numclient=0;
    printf("server iniciat esperant clients\n");
    while(numclient<MAX_CLIENTS){
        //buffer[0]='\0';
        memset(buffer,'\0',sizeof(buffer));//borrem tot el buffer
        if ((new_socket_in= accept(server_fd_in, (struct sockaddr*)&adress_in,(socklen_t*)&addrlenin))< 0  
        || (new_socket_out= accept(server_fd_out, (struct sockaddr*)&adress_out,(socklen_t*)&addrlenout))< 0) {
            printf("accept\n");
            exit(EXIT_FAILURE);
        }
        msglen=read(new_socket_in,buffer,MAX_BUFF);
        //msglen=recv(new_socket_in,buffer,MAX_BUFF,0);
        /*if(msglen<0){
            char joder[MAX_BUFF];
            strerror_r(errno,joder,MAX_BUFF);
            printf("ERROR:%s",buffer);
        }*/
        printf("client %s conectat\n", buffer);
        client[numclient].fd_in=new_socket_in;
        client[numclient].fd_out=new_socket_out;
        strcat(buffer,":");
        strcpy(client[numclient].usrnm,buffer);
        pthread_create(&id[numclient],NULL,thdatclient,(void*)&numclient);
        
        sem_wait(&sem);//ens asegurem que numclient sigui correcte en el thread
        numclient++;
        
    }
    printf("arribat maxim numero de clients\n"); 
    while(1);
}
   

