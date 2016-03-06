/*
    Programa:   pipes.c

    Funcion:    Muestra el uso de de tuberias (pipes) para comunicar procesos padre e hijo

    Autores:    Dave Mathew y Richard Stone (Beginning Linux Programming, 4th Edition)

*/


#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main()
{
   int data_processed;
   int fd[2];
   const char some_data[] = "123";
   char buffer[BUFSIZ + 1];
   pid_t fork_result;

   memset(buffer, '\0', sizeof(buffer));
   if (pipe(fd) == 0) {
      fork_result = fork();
      if (fork_result == -1) {
	 fprintf(stderr, "Error en fork()");
	 exit(EXIT_FAILURE);
      }
      if (fork_result == 0) {
	 data_processed = read(fd[0], buffer, BUFSIZ);
	 printf("Proceso hijo:  lei %d bytes: %s\n", data_processed, buffer);
	 exit(EXIT_SUCCESS);
      }
      else {
	 data_processed = write(fd[1], some_data, strlen(some_data));
	 printf("Proceso padre: Escibi %d bytes\n", data_processed);
      }
   }
   exit(EXIT_SUCCESS);
}