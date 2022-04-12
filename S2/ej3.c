#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
int main(void){

    for(int i=0;i<10;i++) {
        if(fork() == 0){
            for(int k=0;k<1000;k++){
            printf("child process numero %d amb pid %d\n",i+1,getpid());
            }
            exit(0);
        }
        else wait(NULL);
    }
     
    printf("programa acabat\n");

}