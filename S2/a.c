#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
    printf("nose prova\n");
    fork();
    printf("dis\n");
    return 0;
}