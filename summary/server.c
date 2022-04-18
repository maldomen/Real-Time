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

#define MAX_CLIENTS 100;

struct clients{
    struct sockaddr_in adress;
    char * usrnm[100];
};

void USR2_handler(){
    printf("\nSIGUSR2 tancant client\n");
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
    printf("pin %s pout %s\n",pin,pout);
    
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
    int server_fd_in, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = { 0 };
    char* hello = "Hello from server";
    // Creating socket file descriptor
    
    if ((server_fd_in = socket(AF_INET, SOCK_STREAM, 0))
        == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port pin
    if (setsockopt(server_fd_in, SOL_SOCKET,
                   SO_REUSEADDR | SO_REUSEPORT, &opt, //reuseaddr per poder reutilitzar adreses locals reuse port ens deixaria bindejar mes de un socket a un mateix port
                   sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(atoi(pin));
    // Forcefully attaching socket to the port 8080
    if (bind(server_fd_in, (struct sockaddr*)&address,
             sizeof(address))
        < 0) {
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd_in, 5) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    //mateix procediment socket2
    //*************************




    //************************
    //provatemp:
    printf("sembla que tot be\n");
    if ((new_socket
         = accept(server_fd_in, (struct sockaddr*)&address,
                  (socklen_t*)&addrlen))
        < 0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    
    printf("sembla que tot be\n");
    valread = read(new_socket, buffer, 1024);
    printf("%s\n", buffer);
    send(new_socket, hello, strlen(hello), 0);
    printf("Hello message sent\n");
    return 0;


}