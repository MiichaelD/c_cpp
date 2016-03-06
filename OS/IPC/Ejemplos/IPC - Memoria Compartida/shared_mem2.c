/*
	Programa:   shared_mem2.c

	Funcion:    Muestra el uso de memoria compartida (shared memory) como mecanismo de Comunicacion Entre Procesos (IPC)
				El programa shared_,mem2 es un "productor", que escribe (produce) en el area de memoria compartida la
				informacion (texto) que ingresa el usurio, para que sea leiada (consumida) por el proceso "consumidor"

	Autores:    Dave Mathew y Richard Stone (Beginning Linux Programming, 4th Edition)

*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/shm.h>
#include "shm_com.h"

int main()
{
	int running = 1;
	void *shared_memory = (void *)0;
	struct shared_use_st *shared_stuff;
	char buffer[BUFSIZ];
	int shmid;
	printf("Obteniendo memoria compartida ...");
	shmid = shmget((key_t)1234, sizeof(struct shared_use_st), 0666 | IPC_CREAT);
	if (shmid == -1) {
		fprintf(stderr, "Error en shmget\n");
		exit(EXIT_FAILURE);
	}
	
	printf("Asociando memoria compartida ...");
	shared_memory = shmat(shmid, (void *)0, 0);
	if (shared_memory == (void *)-1) {
		fprintf(stderr, "Error en shmat\n");
		exit(EXIT_FAILURE);
	}

	printf("Memoria compartida asociada en %X\n", (int)shared_memory);
	shared_stuff = (struct shared_use_st *)shared_memory;
	while(running) {
		while(shared_stuff->written_by_you == 1) {
			sleep(1);
			printf("espeando algun cliente...\n");
		}
		printf("Escribe algun texto: ");
		fgets(buffer, BUFSIZ, stdin);
		strncpy(shared_stuff->some_text, buffer, TEXT_SZ);
		shared_stuff->written_by_you = 1;
		if (strncmp(buffer, "fin", 3) == 0) {
			running = 0;
		}
	}
	if (shmdt(shared_memory) == -1) {
		fprintf(stderr, "Error en shmdt\n");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}
