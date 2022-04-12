#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>
//en aquesta versio del exercici 1 fem servir la posibilitat de que join utilitzi un punter a un void*
//en aquest exercici no te cap utilitat pero pot ser util si el thread retorna un punter a un objecte
long long int nexit;//si no la fem global al acabar el thread s'allibera la memoria i perdem el valor
//al ser long long int ens asegurem que tingui 8 bytes tant en maquines de 32 i 64 bits i al ser castejada a void* no entrem als bytes d'algun altre int
void * func(){
    printf("thread \n");
    nexit=5;
    pthread_exit((void*)&nexit);
}
int main(){
    pthread_t id;
    void **ret;
    pthread_create(&id, NULL, func, NULL);
    pthread_join(id,ret); 
    //printf("valor exit:%d\n",*((int*)*ret));
}