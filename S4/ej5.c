#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <semaphore.h>

/* 
Un deadlock es debido a que: 
	- tenemos más de dos recursos no compartibles,
	- necesitamos más de un recurso para funcionar y mientras 		esperamos a los recursos, los que vamos obteniendo los    		mantenemos y esperamos al siguiente,
	- nadie nos puede quitar los recursos que guardamos excepto nosotrs 		mismos 
	- hay una secuencia circular de dos o más tareas donde cada una de 		ellas necesita un recurso usado por otra 
Toas las condiciones han de darse a la vaz, por ello para salir del deadlock basta con romper una de ellas. Para ello de puede:
	- que los recursos sean compartibles
	- habilitar el robo de recursos
	- hacer que se cojan o todos o ninún recurso
	- ordenar las peticiones de recursos
En este ejercicio implementamos la tercera solución: cada thread intenta bloquear un recurso para el solo, pero en caso de no poder, libera los que tiene bloqueados.
 */

#define N 10 //numero de filosofos
pthread_mutex_t ten[N];
pthread_t filos[N];
long hambre;

void * comer (void *arg){
	long i = (long)arg;
	long a = 0;
	while(1){
		pthread_mutex_trylock(&ten[i]);
		if(pthread_mutex_trylock(&ten[(i+1)%N]) < 0){
			pthread_mutex_unlock(&ten[i]);
			printf("%ld veces no se ha podido coger el tenedor\n",hambre++);
		}
		else{
			printf("Thread %ld ha comido %ld veces\n",i,a++);
	
			pthread_mutex_unlock(&ten[(i+1)%N]);
			pthread_mutex_unlock(&ten[i]);
		}
	}
}

int main(){
	long i;
	for(i=0; i<N; i++){
		pthread_mutex_init(&ten[i], NULL);
	}
	for(i=0; i<N; i++){
		pthread_create(&filos[i], NULL, comer, (void *)i);
	}
	for(i=0; i<N; i++){
		pthread_join(filos[i], 0);
	}
	return 0;
}
