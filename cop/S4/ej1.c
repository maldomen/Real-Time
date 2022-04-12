#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

pthread_mutex_t critical;
long a[10]={0};

void * f(void *arg){
	int j,k;
	for (j=0; j<10000; j++){
		for (k=0; k<10; k++){
			pthread_mutex_lock(&critical);
			a[k]++;
			pthread_mutex_unlock(&critical);
		}
	}
	pthread_exit(0);
}

int main(){
	pthread_mutex_init(&critical,NULL);
	int i,l;
	pthread_t trd;
	pthread_create(&trd, NULL, f, NULL);
	for (i=0; i<10000; i++){
		for (l=0; l<10; l++){
			pthread_mutex_lock(&critical);
			a[l]++;
			pthread_mutex_unlock(&critical);
		}
	}
	pthread_join(trd, 0);
	l=0;
	for(l=0; l<10; l++){
		printf("Posición %d del vector = %ld\n",l,a[l]);
	}
}
