#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <semaphore.h>

/* Tal y como está actualmente escrito el código no todos los filósofos pueden cenar, el código entra en un deadlock cuya entrada no es predecible. En ocasiones todos los filósofos pueden llegar a cenar y en ocasiones alguno no.
Si cambiamos el pthread_mutex_lock por un pthread_mutex_trylock estaremos solucionando el deadlock y todos los filósofos podrán cenar. Ésta solución se muestra en el ejercicio 5. */

#define N 5 //numero de filosofos
pthread_mutex_t tenedor[N];
pthread_t filosofos[N];

void * comer (void *arg){
	long i = (long)arg;
	long veces = 0;
	while(1){
		pthread_mutex_lock(&tenedor[i]); //tenedor derecho
		pthread_mutex_lock(&tenedor[(i+1)%N]); //tenedor izquierdo
		
		printf("Thread %ld ha comido %ld veces\n",i,veces++);
		
		pthread_mutex_unlock(&tenedor[(i+1)%N]);
		pthread_mutex_unlock(&tenedor[i]);
	}
}

int main(){
	long i;
	for(i=0; i<N; i++){
		pthread_mutex_init(&tenedor[i], NULL);
	}
	for(i=0; i<N; i++){
		pthread_create(&filosofos[i], NULL, comer, (void *)i);
	}
	for(i=0; i<N; i++){
		pthread_join(filosofos[i], 0);
	}
	return 0;
}
