#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>

void * func(){
    printf("thread \n");
    pthread_exit((void *)1);
}
int main(){
    pthread_t id;
    printf("hola1 \n");
    //int *ret=(int*)0x000000310f9ff840,*a=(int*)0x000000310f9ff844; no puc accedir a aquesta memoria virutal a saber com funciona gcc i Minwin amb el sistema operatiu
    int *ret, *a= ret+0x1; //se li suma 1 no se benve per :((
    printf("hola2 \n");
    *a=55;
    printf("hola3 \n");

    pthread_create(&id, NULL, func, NULL);   
    printf("hola4 \n");
    printf("valor a:%d adressa on apunta a:%p valor ret:%d adressa on apunta ret %p\n",*a,a,*ret,ret);
    printf("valor de retorn thread: %d\n", pthread_join(id, (void*)ret)) ;
    printf("valor a despres de join:%d\n",*a);

    printf("sizeof void*: %d    sizeof int*: %d\n", sizeof(void*),sizeof(int));
    //el tamany de un void pointer son 8 bytes,el compilador esta asignant per "a" els 4 bytes despres de ret
    //per tant al castejar el punter de ret a void* fica el 1 ens els 8 bytes que se li han asignat borrant el valor de a. 
    //tambe important saber que en maquines de 64 bits normalment tot i que la variable int siguide 4 bits el int* es de 8 bytes per poder adressar correctament la memoria
}