#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <pthread.h>
//es comparteix heap(dinamic) static(globals permanents) i no stack(local);
int globalVar; /*  A global variable*/
void * func(void * dir){
        
       printf("\n Child Process Initial ValueglobalVar = %d\n",globalVar);
       printf("thread valor inicial p:%ld thread direcio p:%p\n",*(long int*)dir,dir);
       globalVar++;
       *(long int*)dir=50;
       printf("thread valor final p:%ld thread direcio p:%p\n",*(long int*)dir,dir);
       //while(pthread_mutex_lock)
 }

int main(void)
{
       
       long int* p = (long int*) malloc(8);
       int a;
       pthread_t id;
       *p = 0;
       printf("pare\nvalor inicial p=%ld posicio:%p",*p,p);
       pthread_create(&id,NULL,func,(void*)p);
       // Putting value at allocated address
       pthread_join(id,NULL);
       printf("pare\nvalor final p=%ld posicio:%p",*p,p);
       
       //*p = 100; 
       return 0;
}