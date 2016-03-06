/*
 * 
 *   Programa:    	pThread-dig-prim.c (tarea 13)
 *   Objetivo:     	Elaborar un programa en lenguaje C que lea dos numeros enteros A y B.
			El hilo main deberá crear 2 hilos.
 * 		  	Uno aplicara el Digits y el otro Contara numeros primos.
 * 			Main debe imprimir resultados.
 * 
 *   Autor:    		Michael Duarte
 * 
 *   Fecha:		Noviembre 2012
 * 
 *   Nota:         	Para compilar:  gcc -o ptDigPrim pThread-dig-prim.c -lpthread
 *                 	Para ejecutar:  ./ptDigPrim
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int num[2];
int cont[]={0,0,0,0,0,0,0,0,0,0};
int nPrimos;

short esPrimo(int num){
  int j;
  if( num <= 1 )
    return 0;// numeros primos deben ser mayores  a 1
    for(j=num-1; j>1;j--)
      if(num%j == 0)
	return 0;
      //printf("Numero primo: %d\n",num);
    return 1;
}

void *digits(void * x)
{  
  int i,j;
  char string[25];
  for(i=num[0];i<=num[1];i++){
    sprintf(string, "%d",i);//se convierte a String
    for(j=0;j<strlen(string);j++){//se recorren caracteres
       cont[(string[j]-'0')]++;}//se incrementa dependiendo de caracter que es
  }
  pthread_exit(NULL);
  
}

void *primos(void * x)
{
  int i;
  nPrimos=0;
  for(i=num[0];i<=num[1];i++){
    nPrimos+=esPrimo(i);
  }
  pthread_exit(NULL);
}


int main (int argn, char **argv)
{
  pthread_t dig;
  pthread_t prim;
  int i;
  
  printf("Introduce 2 numeros separados por un espacio: ");
  scanf("%d",&num[0]);
  scanf("%d",&num[1]);
  
  pthread_create(&dig, NULL, &digits, NULL);
  pthread_create(&prim, NULL, &primos, NULL);
  
  pthread_join(dig, NULL);
  printf("Digits: \t");
  for(i=0;i<10;i++)
    printf("%d ",cont[i]);
  printf("\n\n");  
  
  pthread_join(prim, NULL);
  printf("Numeros primos: %d\n", nPrimos);
  exit(EXIT_SUCCESS);
}