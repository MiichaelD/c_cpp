/*
	Programa:   ForkSharedMemMensajes

	Funcion:    	Elaborar un programa en Lenguaje C llamado productor que solicite dos número enteros
		    A y B que posteriormente calcule cuántos números primos existen entre A y B inclusive.
		    El proceso productor pondrá el resultado en una área de MEMORIA COMPARTIDA POSIX, en donde
		    serán leídos por un proceso consumidor , quién imprimirá el resultado.
		    Esta tarea puede hacerse en equipo de dos personas.


	Autores:    Michael Duarte & Hector García

*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/shm.h>

struct communicate {
   int  recibido;
   int	A,B;
   int	numPrimos;
};

short esPrimo(int);

int main()
{
	int ejecutando = 1;
	void *shared_memory = (void *)0;
	struct communicate *sharedComm;
	int shmid;
	printf("Obteniendo memoria compartida ...\n");
	//pedimos al SO Memoria compartida del tamaño de la estructura especificada con clave 1234.
	shmid = shmget((key_t)1234, sizeof(struct communicate), 0666 | IPC_CREAT);
	if (shmid == -1) {
		fprintf(stderr, "Error en shmget\n");
		exit(EXIT_FAILURE);
	}
	
	//Nos asociamos a la memoria que le pedimos a SO con el shmid qe nos devolvio al crearla
	printf("Asociando memoria compartida ...\n");
	shared_memory = shmat(shmid, (void *)0, 0);
	if (shared_memory == (void *)-1) {
		fprintf(stderr, "Error en shmat\n");
		exit(EXIT_FAILURE);
	}
	
	printf("Memoria compartida asociada en: %X, con shmid: %d\n", (int)shared_memory,shmid);
	
	// hacemos que el aera de memoria compartida tenga la estructura de "sharedComm"
	sharedComm = (struct communicate *)shared_memory;
	
	
	//creamos proceso hijo!
	if(!fork()){/////PROCESO HIJO - PRODUCTOR
	    printf("Dame 2 numeros: \n");
	    scanf("%d",&sharedComm->A);
	    scanf("%d",&sharedComm->B);
	    int i;
	    sharedComm->numPrimos=0;
	    for (i=sharedComm->A;i<=sharedComm->B;i++){
		 sharedComm->numPrimos+=esPrimo(i);
	    }
	    
	    sharedComm->recibido = 1;//indica al consumidor que está listo
	    
	      
	      if (shmdt(shared_memory) == -1) {
		  fprintf(stderr, "Error en shmdt\n");
		  exit(EXIT_FAILURE);
	      }
	      
	      printf("Proceso Hijo (Productor) terminó satisfactoriamente \n");
	}
	else{////////////////////////PROCESO PADRE - CONSUMIDOR
	      sharedComm->recibido = 0;
	      while (!sharedComm->recibido);
	      printf("Numeros primos desde %d hasta %d: %d\n\n",sharedComm->A,sharedComm->B,sharedComm->numPrimos);


	    // el proceso se des-asocia del area de memoria compartida
	      if (shmdt(shared_memory) == -1) {
		      fprintf(stderr, "Error en shmdt\n");
		    exit(EXIT_FAILURE);
	      }
      
	      if (shmctl(shmid, IPC_RMID, 0) == -1) {
		      fprintf(stderr, "Error en shmctl (IPC_RMID)\n");
		      exit(EXIT_FAILURE);
	      }
	}
	exit(EXIT_SUCCESS);
}


short esPrimo(int num){
	int j;
	if( num <= 1 )
		return 0;// numeros primos deben ser mayores  a 1
	for(j=num-1; j>1;j--)
		if(num%j == 0)
			return 0;
	//printf("Numero primo: %d\n",num);
	return 1;
}
