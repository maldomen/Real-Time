#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int main(){
    FILE *proc=fopen("serverprocessid.txt","r");
    int id;
    fscanf(proc,"%d",&id);
    return(kill(id,SIGKILL));
}
