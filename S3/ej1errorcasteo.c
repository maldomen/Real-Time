#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>

void * func(){
    printf("thread \n");
    pthread_exit((void *)1);
}
int main(){
    pthread_t id;
    int ret,a=55;
    pthread_create(&id, NULL, func, NULL);
    printf("valor a:%d adressa a:%p valor ret:%d adressa ret %p\n",a,&a,ret,&ret);
    pthread_join(id, (void*)&ret);
    printf("valor a despres de join:%d",a);
    //el tamany de un void pointer son 8 bytes,el compilador esta asignant per "a" els 4 bytes despres de ret
    //per tant al castejar el punter de ret a void* fica el 1 ens els 8 bytes que se li han asignat borrant el valor de a. 
}