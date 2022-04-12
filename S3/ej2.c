#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>
long int a=10;

void * thd(){
    for(int i=0;i<100;i++){
    a=a+1;
    printf("thread valor a:%ld\n",a);
    }
    
    pthread_exit(NULL);
}
void main(void){
    pthread_t id;
    pthread_create(&id,NULL,thd,NULL);
    for(int i=0;i<100;i++){
        a=a-1;
        printf("parent valor a:%ld\n",a);
        }
    
    pthread_join(id,NULL);
}   
//tal i com esperavem tant el thread com el parent modifiquen a
