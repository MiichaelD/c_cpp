/*

   Programa:     suma2o_thread.c
   Objetivo:     Mostrar el uso de POSIX Threads (Pthreads)
                 El programa recibe dos numeros enteros y crea un hijo para que calcule la suma de los numeros
	         e imprima el resultado

   Autor:        Arnoldo Diaz Ramirez

   Nota:         Para compilar:  gcc -o suma2_thread suma2_thread.c -lpthread
                 Para ejecutar:  ./suma2_thread num1 num2
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

/*
   Prototipo de la funcion que ejecutar el hilo
   El codigo de la funcion se define despues del main()
*/

void * thread_code(void *);

/*
   Se define la variable global num[], a la que pueden acceder los hilos
*/
int num[2];


int main (int argn, char **argv)
{
  pthread_t thid;
  int suma;

/*
  Se verifica que el programa haya sido invocado correctamente
*/

  if (argn != 3) {
    printf("Error, debe utilizarse asi: %s num1 num2 \n", argv[0]);
    exit(0);
  }

  num[0] = atoi(argv[1]);
  num[1] = atoi(argv[2]);

/*
   Se crea el hilo
*/

  pthread_create(&thid, NULL, &thread_code, NULL);

  pthread_exit(NULL);
}

/*
   Codigo que ejecutara el hilo
*/

void *thread_code(void * x)
{

  printf("La suma de los numeros es %d\n", num[0] + num[1]);
  pthread_exit(NULL);

}
