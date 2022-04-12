#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int a=500;
int main(void){
    
    int i=0;
    pid_t idfork=fork();
    printf("%d\n",a);
    if (idfork==-1) printf("error al crear child \n");
    else if (idfork==0){
        for(i; i<5;i++){
            a=a+1;
            printf("child a: %d\n",a);
        }
        printf("El process child fa una copia de les variables ja siguin locals o globals per tant com esperavem cada process te les seves propies variables\n");
    }
    else {
        for(i; i<5;i++){
            a=a-1;
            printf("parent a: %d\n",a);
        }
    }
}