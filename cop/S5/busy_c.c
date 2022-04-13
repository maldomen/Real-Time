#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <pthread.h>

float media_difs_us=0;
int num_tr;

int power(int x, int y)
	{
	int res = 1;
	int i = y;
	if (y < 0) res = -1;
	else if (y = 0) res = 1;
	else 
	{
		while (i > 0)
		{
			res = res * x;
			i--;
		}
	}
	return res;
}

int AsciiToInteger(char *sr1)
{
   	int l = strlen(sr1);
   	int res = 0;
	for (int i=0; i<l; i++)
	{
		if ((*sr1 >= '0' && *sr1 <= '9') && (res != -1))
		{
			res = res + ((*sr1-'0')*power(10, l-i-1));
		}
		else
		{
			res = -1;
		}
		sr1++;
	}
	return res;
}

void espera_activa(int us)
{
	struct timeval strt, end;
	struct timezone t;
	long dif = 0;
	
	gettimeofday(&strt, &t);
	
	while (dif < us)
	{
		gettimeofday(&end, &t);
		dif = end.tv_usec - strt.tv_usec;
	}
}

void * f(void *arg)
{
	struct timeval ini, fin;
	struct timezone t;
	char buff[256];
	long us = (long)arg;
	
	gettimeofday(&ini, &t);
	espera_activa(us);
	//usleep(us);
	gettimeofday(&fin, &t);
	
	sprintf(buff, "Fin\nSe ha esperado realmente %lds y %ldus\n\n",(fin.tv_sec - ini.tv_sec), (fin.tv_usec - ini.tv_usec));
	write(1, &buff, strlen(buff));
	
	int dif_s = (fin.tv_sec - ini.tv_sec);
	int dif_us = (fin.tv_usec - ini.tv_usec);

	media_difs_us += (dif_us + (dif_s*power(10,6)) - us)/num_tr;
	
	pthread_exit(0);
}

int main(int argc, char**argv)
{
	struct timeval ini, fin;
	struct timezone t;
	char buff[256];
	long utime;
	int i;
	
	if (argc < 3)
	{
		sprintf(buff, "Error, sintaxis: ej4.c (int)us (int)num_threads\n");
		write(1, &buff, strlen(buff));
		exit(0);
	}
	
	utime = AsciiToInteger(argv[1]);
	num_tr = AsciiToInteger(argv[2]);
	
	sprintf(buff, "Inicio: %d threads esperarán %ld us\n\n", num_tr, utime);
	write(1, &buff, strlen(buff));
	
	pthread_t tr[num_tr];
	for (i=0; i<num_tr; i++)
	{
		pthread_create(&tr[i], NULL, f, (void*)utime);
	}
	for (i=0; i<num_tr; i++)
	{
		pthread_join(tr[i], 0);
	}
	
	sprintf(buff, "La diferencia media para una espera de %ld con %d es de:\n%f us\n", utime, num_tr, media_difs_us);
	write(1, &buff, strlen(buff));
}
