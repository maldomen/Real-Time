#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <semaphore.h>

#define N 10
sem_t sem[N]; 
pthread_t tr[N];
int buff[N];
int l = 1;

void orden(){
	// [0,1,2,3,4,5,6,7,8,9] -> [2,4,6,8,10,9,7,5,3,1] Valores
	// [0,1,2,3,4,5,6,7,8,9]    [0,1,2,3,4, 5,6,7,8,9] Pos. vect.
	int k;
	int i = 1;
	for (k=0; k<N; k++){
		if(k%2 == 0){
			buff[N-1-(k/2)] = k;
		}
		else{
			buff[k-i] = k;
			i++;
		}
	}
	for (k=0; k<N; k++){
		buff[k]++;
	}
}

void * id (void *arg){
	long i = (long)arg;
	sem_wait(&sem[i-1]);
	printf("Soy el thread %ld\n", i);
	int next = buff[(l)%N];
	l++;
	sem_post(&sem[next-1]);
	pthread_exit(0);
}

int main(){
	long i;
	orden();
	
	// Inicializacion de los semaforos
	for(i=0; i<N; i++){
		sem_init(&sem[i], 0, 0); // Semaforos cerrados
	}
	sem_post(&sem[1]); // El primer semaforo abierto
	
	// Inicializacion de los threads
	for(i=0; i<N; i++){
		pthread_create(&tr[i], NULL, id, (void *)(i+1));
	}
	
	// Sincronización con los threads
	for(i=0; i<N; i++){
		pthread_join(tr[i], 0);
	}
	return 0;
}
