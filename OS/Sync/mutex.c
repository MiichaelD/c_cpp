/*
   Programa:    mutex.c
   
   Objetivo:    Elaborar un programa que cree un hilo. Los dos hilos, esto es, el hilo "main" y el hilo creado,
		actualizarán la variable global "cont" que tendrá un valor inicial igual a cinco.
   
		El hilo "main" ejecutará el siguiente código, después de crear al otro hilo:
		      (3 veces){
			for (i=1; i<1000; i++)
			  for (j=1; j<1000; j++);
			cont++;
		      }
		
		El otro hilo ejecutará el mismo código, con la diferencia de que decrementará en uno el valor
		del contador (cont--) en lugar de incrementarlo (cont++). Esto es, el hilo "main" incrementará
		tres veces en uno el valor de cont, mientras que el otro hilo lo decrementará tres veces.
		
		Como puedes observar, el uso de la variable cont es una sección crítica. Para evitar
		inconsistencia en el resultado final, deberás utilizar el API para Mutex de POSIX (por ejemplo,
		pthread_mutex_lock()) para el acceso a la sección crítica.
   
		Finalmente, el hilo "main" esperará a que el otro hilo concluya su ejecución (esto es, haga un
		pthread_join()) e imprimirá el valor final de la variable cont.
		
    Nota:	Como la operación de la sección crítica es muy sensilla por lo general no se nota la diferencia
		al utilizar mutex, pero con esto aseguramos que nunca haya incongruencias al momento de acceder
		al mismo recurso por 2 hilos distinto.
   
   Compilar:	gcc mutex.c -lpthread
   
   
    Autor:    	Michael Duarte
    
    Fecha: 	Noviembre 2012
*/ 

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

void *funcionHilo(void *arg);
void incrementar();
void decrementar();
pthread_mutex_t mutex;   //Solo ocuparemos un mutex dado que solo se accesa a un recurso compartido (sección critica)
int cont;

int main() {
   pthread_t hilo;
   cont =5;
   printf("Valor inicial de contador: %d.", cont);
   pthread_create(&hilo, NULL, funcionHilo, NULL);
   pthread_mutex_init(&mutex, NULL); // opcional - innecesarios
   int h,i,j;
   for(h = 0; h < 3; ++h ){
     for (i=1; i<1000; i++)
       for (j=1; j<1000; j++);
     incrementar();
   }
   
   pthread_join(hilo, NULL);//esperamos que termine el hilo
   pthread_mutex_destroy(&mutex);//destruimos el mutex
   printf("\tValor Final: %d\n",cont);
   exit(EXIT_SUCCESS);//terminamos
}
void *funcionHilo(void *arg) {
  int i,j;
  for(h = 0; h < 3; ++h ){
     for (i=1; i<1000; i++)
       for (j=1; j<1000; j++);
     decrementar();
   }
   pthread_exit(0);
}

void incrementar(){
  pthread_mutex_lock(&mutex); 
  cont++;//sección crítica
  pthread_mutex_unlock(&mutex);
}

void decrementar(){
  pthread_mutex_lock(&mutex);
  cont--;//sección crítica
  pthread_mutex_unlock(&mutex);
}
