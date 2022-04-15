	#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>

int main(){
	pthread_mutex_t critical; //esta
	pthread_mutex_init(&critical,NULL); //esta
	int r = shm_open("/ej4_region", O_RDWR, 0777);
	
	int *region = (int *)mmap(NULL, 4096, PROT_READ|PROT_WRITE, MAP_SHARED, r, 0);
	close(r);
	
	while(1){
		
		printf("programb");
		//while(region[2] != 1);
		pthread_mutex_lock((pthread_mutex_t*)&region[3]);//esta
		region[1] = 0;
		printf("Programa B recibe: %ld\n", (long)region[0]);
		region[1] = 1;
		region[2] = 0;
		pthread_mutex_unlock((pthread_mutex_t*)&region[3]);//esta
	}
	
	munmap(region, 4096);	
	
	return 0;
}
