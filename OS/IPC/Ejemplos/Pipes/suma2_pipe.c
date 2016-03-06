/*

   Programa:   suma2_pipe.c
   Objetivo:   El programa lee dos numeros y crea un proceso hijo para que calcule la
               suma de los numeros. El proceso hijo enviara el resultado al padre utilizando
               una tuberia (pipe). El proceso padre imprimira el resultado
               
   Autor:      Arnoldo Diaz Ramirez
   
*/


#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
int main()
{
  int data_processed;
  int x, y, suma;
  int fd[2];
  char some_data[80];
  char buffer[BUFSIZ + 1];
  pid_t fork_result;
  memset(buffer, '\0', sizeof(buffer));
  
  printf("Escribe un numero: ");
  scanf("%d", &x);
  
  printf("Escribe otro numero: ");
  scanf("%d", &y);
  
  if ( pipe(fd) == 0 ) {     // se crea la tuberia
    fork_result = fork();       // se crea el proceso hijo
    if (fork_result == -1) {
      fprintf(stderr, "Error en fork()");
      exit(EXIT_FAILURE);
    }
    if (fork_result == 0) {     // proceso hijo
      suma = x + y;
      sprintf(some_data, "El resultado de la suma es %d\n", suma);     
      data_processed = write(fd[1], some_data, strlen(some_data));
      printf("Proceso hijo: Escribi %d bytes en la tuberia\n", data_processed);
      exit(EXIT_SUCCESS);
    }
    else {                      // proceso padre
     
      data_processed = read(fd[0], buffer, BUFSIZ);
      printf("Proceso padre: lei %d bytes: %s\n", data_processed, buffer);
    }
  }
  exit(EXIT_SUCCESS);
}
