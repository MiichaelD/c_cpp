/*
	Programa:   ForkSharedMem-Mensajes

	Funcion:    	Comunicacion entre procesos usando  memoria compartida, consumidor imprime mensajes recibidos
		    por parte del productor.


	Autores:    Michael Duarte

*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/shm.h>

#define TEXT_SZ 2048			//2 kB maximo por lectura

struct communicate {
   int  recibido;
   char mensaje[TEXT_SZ];
};


int main()
{
	int ejecutando = 1;
	int fork_res;
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
		
	    
	    while(ejecutando) {
		  //Esperando a qe marque mensaje como RECIBIDO =0
		  if(!sharedComm->recibido){
		    printf("Escribe algun texto: ");
		    fgets(sharedComm->mensaje, TEXT_SZ, stdin);
		    sharedComm->recibido = 1;
		    if	 (strncmp(sharedComm->mensaje, "fin", 3) == 0) {
			      ejecutando = 0;
		    }
		  }
	      }
	      if (shmdt(shared_memory) == -1) {
		  fprintf(stderr, "Error en shmdt\n");
		  exit(EXIT_FAILURE);
	      }
	      
	      printf("Proceso Hijo terminó satisfactoriamente \n");
	}
	else{////////////////////////PROCESO PADRE - CONSUMIDOR
	      sharedComm->recibido = 0;
	    // ciclo hasta que el proceso lea del area de memoria compartida el texto "fin"
	      while (ejecutando) {
		      if (sharedComm->recibido) {
			      printf("\t\t\tEscribiste: %s", sharedComm->mensaje);
			      //sleep( 1 );  
			      sharedComm->recibido = 0;
			      if ( strncmp(sharedComm->mensaje, "fin", 3 ) == 0) {
				      ejecutando = 0;
			      }
		      }
	      }

	    // el proceso se des-asocia del area de memoria compartida
	      if (shmdt(shared_memory) == -1) {
		      fprintf(stderr, "Error en shmdt\n");
		    exit(EXIT_FAILURE);
	      }
      
	      if (shmctl(shmid, IPC_RMID, 0) == -1) {
		      fprintf(stderr, "Error en shmctl (IPC_RMID)\n");
		      exit(EXIT_FAILURE);
	      }
	      printf("Proceso Padre terminó satisfactoriamente\n");
	}
	exit(EXIT_SUCCESS);
}
