#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>

/* Los valores de tiempo esperados son ahora mucho mas exactos que en el anterior ejercicio */

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

int main(int argc, char**argv)
{
	struct timeval ini, fin;
	struct timezone t;
	char buff[256];
	int utime;
	
	if (argc == 1)
	{
		sprintf(buff, "Error, sintaxis: ej4.c (int)us\n");
		write(1, &buff, strlen(buff));
		exit(0);
	}
	
	utime = AsciiToInteger(argv[1]);
	sprintf(buff, "Inicio\n");
	write(1, &buff, strlen(buff));
	
	gettimeofday(&ini, &t);
	espera_activa(utime);
	gettimeofday(&fin, &t);
	
	sprintf(buff, "Fin\nSe ha esperado realmente %ld us\n", (fin.tv_usec - ini.tv_usec));
	write(1, &buff, strlen(buff));
}
