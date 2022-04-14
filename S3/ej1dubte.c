#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>

void * func(){ //preguntar perque no func(NULL) o func(void)
    printf("thread \n");
    pthread_exit((void *)4); //pregunta pq si a join fiquem un void** no funciona i retorna una adreça 0x4
}
int main(){
    pthread_t id;
    void *ret;
    pthread_create(&id, NULL, func, NULL);
    pthread_join(id,ret); 
    printf("valor exit:%d\n",*(int*)ret);
}
