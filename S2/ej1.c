#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
int main(void)
{
    pid_t fork_pid = fork();
	pid_t process_id;
	pid_t p_process_id;
    char numero[150],numero2[150];
    char buffer[150],buffer2[150];
	process_id = getpid();
	p_process_id = getppid();
    
	if(fork_pid == 0){
        
        printf("Informacio extreta de child:\n\nLa id del proces creat pel fork del proces %d es: %d \n",p_process_id,process_id);
        printf("------\n");

    }
    else{
        printf("Aquest programa crea un child i mostra els PID del diferents processos involucrats i acaba despres que el process child ha acabat\n-----\n");
        wait(NULL); //si no fem servir aquest wait el process child s'executa un cop ha acabat el parent i llavors el seu parent ID cambia
        printf("Informació extreta de parent:\n\nLa id del proces de la consola es es: %d\n",p_process_id);
	    printf("la id del proces pare es: %d\n",process_id);
        printf("la id del proces child que hem creat amb fork es: %d\n",fork_pid);
        printf("------\n");
        printf("child process acabat \n");
    }
	return 0;
}