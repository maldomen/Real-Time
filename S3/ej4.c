#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>

long int vec[10]={1,2,3,4,5,6,7,8,9,10};


void *func(void *arg){
    for(int i=0;i<1000;i++){
        (*(long int*)arg)++;
    }
    pthread_exit(NULL);
}
void main(void){
    pthread_t id[10];
    printf("Definim variable global long int vec[10]={1,2,3,4,5,6,7,8,9,10}\n");
    for(int i=0;i<=9;i++){
        pthread_create(&id[i], NULL, func,(void*)&vec[i]);
    }
    for(int i=0;i<=9;i++){
        pthread_join(id[i],NULL); 
    }
    for(int i=0;i<=9;i++){
        printf("vec[%d]=%ld\n",i,vec[i]); 
    }
}