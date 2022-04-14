#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>
int main(void){
    int c=5,*pc=(int*)((char*)&c+1);
    //int *pc=((char*)c)+1;
    //void *pc=((char*)&c)+1;
    printf("decimal c:%d decimal pc:%d\npunter c:%p punter pc:%p\n",c,*pc,&c,pc);
    printf("tamany int:%ld tamany char:%ld tamany voidp:%ld\n",sizeof(int),sizeof(char),sizeof(void*));


}

