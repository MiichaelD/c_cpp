#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
	pid_t  pid;
	pid= fork();
	printf("Proceso: %d\n",pid);
	if (pid< 0) { 
		fprintf(stderr, "Fallo en fork()");
		exit(-1);
	}
	else if (pid == 0) { /* proceso hijo */
		printf("Iniciando el proceso hijo" );
		execlp("./fork.exe", "./fork.exe", NULL);
		
	}
	else { /* proceso padre espera a que el hijo concluya */
		printf("Iniciando el proceso PADRE" );
		execlp("./fork.exe", "./fork.exe", NULL);
		wait(NULL);
		printf ("Proceso hijo concluido");
		exit(0);
	}
}