/*
Programa:               ForkDigits.c

Objetivo:                   Crear un proceso hijo que realizara el programa digits.c	
						lee dos números enteros a y b (0 <= a <= b <= 100000). Posteriormente,
						el programa creará un proceso hijo quien ejecutará el código del
						programa digits.c (ver archivo con definición del problema "Digits")
						y que imprima los resultados.
						 
Nota:						La funcion fork, retorna un 0 al proceso hijo y	el PID del proceso
						hijo al proceso padre. 
                              
Autor:                  Michael Duarte
Fecha:                  Septiembre 2012
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//#include <unistd.h> // No es necesario

char string[50];
int num1,num2,i;
int j,es_hijo;

void main(){
     
	 printf("Dame 2 numeros: ");
     scanf("%d",&num1);
     scanf("%d",&num2);
	
	 es_hijo=fork();
	 
	 if(!es_hijo){//solo el hijo hara esto
              int cont[]={0,0,0,0,0,0,0,0,0,0};
              for(i=num1;i<=num2;i++){
                   sprintf(string, "%d",i);//se convierte a String
                   for(j=0;j<strlen(string);j++){//se recorren caracteres
                        cont[(string[j]-'0')]++;}//se incrementa dependiendo de caracter que es
              }
              for(i=0;i<10;i++)//se imprime vector con resultados
                   printf("%d ",cont[i]);
			  printf("\n");
     }
/*	 else
			printf("Soy Padre, no hago nada!\n");
*/	 
}