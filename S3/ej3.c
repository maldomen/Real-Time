#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>
long int vec[10]={0,0,0,0,0,0,0,0,0,0};
void * thd(){
    for(int i=0;i<1000;i++){
        for(int j=0;j<=9;j++){
            vec[j]++;
        }
    }

    pthread_exit(NULL);
}

void main(void){
    pthread_t id;
    pthread_create(&id, NULL, thd, NULL);
    printf("Definim variable global long int vec[10]={0,0,0,0,0,0,0,0,0,0}\n");    
    for(int i=0;i<1000;i++){
        for(int j=0;j<=9;j++){
            vec[j]++;
        }
        
    }
    pthread_join(id,NULL);
    for(int i=0;i<=9;i++){
        printf("vec[%d]=%ld\n",i,vec[i]);
    }
}
