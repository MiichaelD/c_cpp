/*
   Programa:    pthread_mutex.c
   
   Objetivo:    El programa utiliza dos hilos. El hilo "main" solicita al usuario que escriba  un texto, que almacena en la variable
                "work_area". El hilo "a_thread" revisa constantemente si el hilo "main" ha escrito algo en "work_area", para reportar
                el numero de caracteres escritos y "limpiar" la variable "work_area". Todo esto se lleva a cabo hasta que el usuario
                escriba la palabra "fin". En ese caso, el valor de la variable "time_to_exit" se hace igual a 1 y los hilos concluyen
                su ejecucion. Las variables compartidas "work_area" y "time_to_exit" estan protegidas por mutexes.
                
    Autores:    Dave Mathew y Richard Stone (Beginning Linux Programming, 4th Edition). Modificado por Arnoldo Diaz Ramirez.
*/ 

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

void *thread_function(void *arg);

pthread_mutex_t work_mutex;    /* protege a la variable work_area */ 
pthread_mutex_t time_mutex;    /* protege a la variable time_to_exit */
#define WORK_SIZE 1024
char work_area[WORK_SIZE];
int time_to_exit = 0;

int main() {
   int res;
   pthread_t a_thread;
   void *thread_result;
   res = pthread_mutex_init(&work_mutex, NULL);
   if (res != 0) {
      perror("Fallo al iniciar el Mutex initialization");
      exit(EXIT_FAILURE);
   }
   res = pthread_create(&a_thread, NULL, thread_function, NULL);
   if (res != 0) {
      perror("Fallo en la creacion del Thread");
      exit(EXIT_FAILURE);
   }
   pthread_mutex_lock(&time_mutex);
   pthread_mutex_lock(&work_mutex);
   printf("Escribe algun texto. Ingresa 'fin' para terminar\n");
   while(!time_to_exit) {
      fgets(work_area, WORK_SIZE, stdin);
      pthread_mutex_unlock(&work_mutex);
      pthread_mutex_unlock(&time_mutex);
      while(1) {
	 pthread_mutex_lock(&work_mutex);
	 if (work_area[0] != '\0') {
	    pthread_mutex_unlock(&work_mutex);
	    sleep(1);
	 }
	 else {
	    break;
	 }
      }
   }
   pthread_mutex_unlock(&work_mutex);
   pthread_mutex_unlock(&time_mutex);
   printf("\nEsperando la terminacion del thread...\n");
   res = pthread_join(a_thread, &thread_result);
   if (res != 0) {
      perror("Fallo en el join del Thread");
      exit(EXIT_FAILURE);
   }
   printf("Se hizo join al Thread de manera correcta\n");
   pthread_mutex_destroy(&work_mutex);
   exit(EXIT_SUCCESS);
}
void *thread_function(void *arg) {
   sleep(1);
   pthread_mutex_lock(&work_mutex);
   while(strncmp("fin", work_area, 3) != 0) {
      printf("Escribiste %d caracteres\n", strlen(work_area) -1);
      work_area[0] = '\0';
      pthread_mutex_unlock(&work_mutex);
      sleep(1);
      pthread_mutex_lock(&work_mutex);
      while (work_area[0] == '\0' ) {
	 pthread_mutex_unlock(&work_mutex);
	 sleep(1);
	 pthread_mutex_lock(&work_mutex);
      }
   }
   pthread_mutex_lock(&time_mutex);
   time_to_exit = 1;
   pthread_mutex_unlock(&time_mutex);   
   work_area[0] = '\0';
   pthread_mutex_unlock(&work_mutex);
   pthread_exit(0);
}
