#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
	int pd[2];
	int a,r;
	
	pipe(pd);
	
	r=fork();
	if (r== -1) exit(0);
	
	if (r==0)	// Hijo (escritor)
	{
		close(pd[0]);
		a=0;
		while(1)
		{
			write(pd[1], &a, sizeof(int));
			a++;
		}
	}
	else		// Padre (lector)
	{
		close(pd[1]);
		while(1)
		{
			read(pd[0], &a, sizeof(int));
			printf("%d\n", a);
		}
	}
}
