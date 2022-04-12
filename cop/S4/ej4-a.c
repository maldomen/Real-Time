#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>

/* El programa podria fallar en caso de que A no llegase a poner valid a 1 antes de que el OS cambiara de thread que ejecutar, lo que supondría que B no leería el numero que se le envía ni pondría tampoco ready a 1 con lo que ambos programas se quedarían esperando el uno al otro. Lo mismo ocurriría si B no llegara a poner ready a 1 por falta de tiempo. Este problema se solucionaría definiendo como zona crítica el código que se encuentra dentro del segundo while para ambos códigos (las lineas de código que solucionan el problema se encuentran comentadas)*/

int main(){
	pthread_mutex_t critical; //esta
	pthread_mutex_init(&critical,NULL); //esta
	int ready = 1;
	int valid = 0;
	long i = 0;
	
	int r = shm_open("/ej4_region", O_CREAT|O_RDWR, 0777);
	ftruncate(r, 4096);
	
	int *region = (int *)mmap(NULL, 4096, PROT_READ|PROT_WRITE, MAP_SHARED, r, 0);
	close(r);
	
	region[1] = ready;
	region[2] = valid;
	while(1){
		while(region[1] != 1);
		pthread_mutex_lock(&critical); //esta
		region[2] = 0;
		region[0] = i;
		printf("Programa A escribe: %ld\n", i);
		i++;
		region[2] = 1;
		region[1] = 0;
		pthread_mutex_unlock(&critical); //esta
	}
	
	munmap(region, 4096);
	shm_unlink("/ej4_region");
	
	return 0;
}
