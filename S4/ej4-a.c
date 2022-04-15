#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/wait.h>

/* El programa podria fallar en caso de que A no llegase a poner valid a 1 antes de que el OS cambiara de thread que ejecutar, lo que supondría que B no leería el numero que se le envía ni pondría tampoco ready a 1 con lo que ambos programas se quedarían esperando el uno al otro. Lo mismo ocurriría si B no llegara a poner ready a 1 por falta de tiempo. Este problema se solucionaría definiendo como zona crítica el código que se encuentra dentro del segundo while para ambos códigos (las lineas de código que solucionan el problema se encuentran comentadas)*/

int main(){
	int i = 1;
	int r = shm_open("/ej4_region", O_CREAT|O_RDWR, 0777);
	int *region = (int *)mmap(NULL, 4096, PROT_READ|PROT_WRITE, MAP_SHARED, r, 0);
	int *ready = &region[1];
	int *valid = &region[2];
	//(pthread_mutex_t)region[3]= phtread_mutex_t critical;
	pthread_mutex_init((pthread_mutex_t*)&region[3],NULL); 
	close(r);
	*ready=1;
	*valid=0;
	while(1){
		//while(*ready != 1);
		pthread_mutex_lock((pthread_mutex_t*)&region[3]); //esta
		region[2] = 0;
		region[0] = i;
		printf("Programa A escribe: %d\n", i);
		i++;
		region[2] = 1;
		region[1] = 0;
		pthread_mutex_unlock((pthread_mutex_t*)&region[3]); //esta
	}
	
	munmap(region, 4096);
	shm_unlink("/ej4_region");
	
	return 0;
}
//tindria mes sentit declarar el mutex dins la memoria compartida
//i fer que les variables locals ready i valid fossin punters que apunten a regio[0] i regio[1]
//sense el mutex funciona pero pot fallar