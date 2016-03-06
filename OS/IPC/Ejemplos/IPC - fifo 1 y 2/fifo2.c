/*
    Programa:   fifo2.c

    Funcion:    Muestra el uso de tuberias con nombre (fifos) como mecanismo de Comunicacion Entre Procesos (IPC)
                El programa fifo2 es un "consumidor", que lee (consume) la informacion que escribe el "productor"
                en la fifo y la muestra en pantalla

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


int main()
{
   int pipe_fd;
   int res;
   int open_mode = O_RDONLY;
   char buffer[BUFFER_SIZE + 1];
   int bytes_read = 0;
   memset(buffer, '\0', sizeof(buffer));
   printf("Proceso consumidor con pid %d abriendo la FIFO en modo O_RDONLY\n", getpid());
   pipe_fd = open(FIFO_NAME, open_mode);
   printf("El proceso consumidor con pid %d obtuvo como resultado %d\n", getpid(), pipe_fd);
   if (pipe_fd != -1) {
      do {
	 res = read(pipe_fd, buffer, BUFFER_SIZE);
	 bytes_read += res;
      } while (res > 0);
      (void)close(pipe_fd);
   }
   else {
      exit(EXIT_FAILURE);
   }
   printf("Proceso consumidor con pid %d concluido, leyo %d bytes\n", getpid(), bytes_read);
   exit(EXIT_SUCCESS);
}
