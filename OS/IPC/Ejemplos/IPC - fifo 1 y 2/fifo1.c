/*
    Programa:   fifo.c

    Funcion:    Muestra el uso de tuberias con nombres (fifos) como mecanismo de Comunicacion Entre Procesos (IPC)
                El programa fifo1 es un "productor", que produce (escribe) informacion que es "consumida" (leida)
                por el proceso consumidor

    Autores:    Dave Mathew y Richard Stone (Beginning Linux Programming, 4th Edition)

*/


#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>

#define FIFO_NAME "/tmp/my_fifo"
#define BUFFER_SIZE PIPE_BUF

#define TEN_MEG (1024 * 1024 * 10)

int main()
{
   int pipe_fd;
   int res;
   int open_mode = O_WRONLY;
   int bytes_sent = 0;
   char buffer[BUFFER_SIZE + 1];
   if (access(FIFO_NAME, F_OK) == -1) {
      res = mkfifo(FIFO_NAME, 0777);
      if (res != 0) {
	 fprintf(stderr, "No fue posible crear la FIFO %s\n", FIFO_NAME);
	 exit(EXIT_FAILURE);
      }
   }
   printf("Proceso productor con pid %d abriendo la FIFO en modo O_WRONLY\n", getpid());
   pipe_fd = open(FIFO_NAME, open_mode);
   printf("El proceso productor con pid %d obtuvo como resultado %d\n", getpid(), pipe_fd);
   if (pipe_fd != -1) {
      while(bytes_sent < TEN_MEG) {
	 res = write(pipe_fd, buffer, BUFFER_SIZE);
	 if (res == -1) {
	    fprintf(stderr, "Error al escribir en FIFO\n");
	    exit(EXIT_FAILURE);
	 }
	 bytes_sent += res;
      }
      (void)close(pipe_fd);
   }
   else {
      exit(EXIT_FAILURE);
   }
   printf("Proceso productor con pid %d concluido\n", getpid());
   exit(EXIT_SUCCESS);
}
