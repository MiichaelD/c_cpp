/*

   Programa:     holamundo_thread.c
   Objetivo:     Mostrar el uso de POSIX Threads (Pthreads)

   Nota:         Para compilar:  gcc -o hola_thread hola_thread.c -lpthread

*/


#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void *thread_code(void * arg)
{
  printf("Hola Mundo desde un hilo!\n");
  pthread_exit(NULL);
}

main ()
{
  pthread_t thid;

  printf("Hilo main padre a punto de crear un hilo\n");

  pthread_create(&thid, NULL, &thread_code, NULL);

  pthread_exit(NULL);
}
