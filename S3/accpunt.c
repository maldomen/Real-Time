#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>

int main() {
    int num=5;           
    char *ptr = ((char*)&num);
    int i; int j;
    /*for (i = 1, j = 0; i < 8, j < 7; i += 2, j += 2) {
        printf("0x%hx%hx at address %p \n", ptr[i], ptr[j], (void *) ptr+i);
    }*/
    printf("adress char:%p adress int:%p\n",ptr,&num);
    printf("value char:%p value int:%p\n",*ptr,num);
    
    *ptr='c';
     
    printf("Cambiem valor de char\nadress char:%p adress int:%p\n",ptr,&num);
    printf("value char:%p value int:%p\n",*ptr,num);
    
    
    printf("la adressa de ptr es: %p\n",&ptr,&num);
    


    return 0;
}