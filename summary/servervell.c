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

int
       main(int argc, char *argv[])
       {
           struct addrinfo addrin,addrout;
           struct addrinfo *result, *rp,*rp2;
           int sfd,sfd2, s;
           struct sockaddr_storage peer_addr;
           socklen_t peer_addr_len;
           ssize_t nread;
           char buf[256];

           if (argc != 3) {
               fprintf(stderr, "Usage: %s portin portout\n", argv[0]);
               exit(EXIT_FAILURE);
           }
            //inicialitzem portin i portout
           memset(&addrin, 0, sizeof(addrin));
           addrin.ai_family = AF_INET;    /* Allow IPv4 */
           addrin.ai_socktype = SOCK_DGRAM; /* Stream socket */
           //addrin.ai_flags = AI_PASSIVE;    /* For wildcard IP address */
           addrin.ai_flags =0;
           addrin.ai_protocol = 0;          /* IPV4 */
           addrin.ai_canonname = NULL;
           addrin.ai_addr = NULL;
           addrin.ai_next = NULL;
            addrout=addrin;//inicialitzem portot
           s = getaddrinfo(NULL, argv[1], &addrin, &result);
           if (s != 0) {
               fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
               exit(EXIT_FAILURE);
           }

           /* getaddrinfo() returns a list of address structures.
              Try each address until we successfully bind(2).
              If socket(2) (or bind(2)) fails, we (close the socket
              and) try the next address. */

           for (rp = result; rp != NULL; rp = rp->ai_next) {
               sfd = socket(rp->ai_family, rp->ai_socktype,
                       rp->ai_protocol);
               if (sfd == -1)
                   continue;

               if (bind(sfd, rp->ai_addr, rp->ai_addrlen) == 0)
                   break;                  /* Success */

               close(sfd);
           }

           freeaddrinfo(result);           /* No longer needed */

           if (rp == NULL) {               /* No address succeeded */
               fprintf(stderr, "Could not bind\n");
               exit(EXIT_FAILURE);
           }
           // ACABAT PORTIN
           //PORTOUT:
           s = getaddrinfo(NULL, argv[2], &addrout, &result);
           if (s != 0) {
               fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
               exit(EXIT_FAILURE);
           }

           /* getaddrinfo() returns a list of address structures.
              Try each address until we successfully bind(2).
              If socket(2) (or bind(2)) fails, we (close the socket
              and) try the next address. */

           for (rp2 = result; rp2 != NULL; rp2 = rp2->ai_next) {
               sfd2 = socket(rp2->ai_family, rp2->ai_socktype,
                       rp2->ai_protocol);
               if (sfd2 == -1)
                   continue;

               if (bind(sfd2, rp2->ai_addr, rp2->ai_addrlen) == 0)
                   break;                  /* Success */

               close(sfd2);
           }

           freeaddrinfo(result);           /* No longer needed */

           if (rp2 == NULL) {               /* No address succeeded */
               fprintf(stderr, "Could not bind\n");
               exit(EXIT_FAILURE);
           }
        printf("Server sucess\n");
        while(1);
       }