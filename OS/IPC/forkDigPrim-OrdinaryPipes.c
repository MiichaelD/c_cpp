	/*
	 Programa:	ForkDigPrim-OrdinaryPipes.c
	 
	 Funcion:		1.- Solicitar dos número entero A y B
						2.- Crear una tubería ordinaria (pipe)
						3.- Crear un prceso hijo
						4.- El proceso hijo calculará cuántos números primos hay entre A y B, y aplicará el algoritmo digits a los números A y B
						5.- El proceso hijo enviará los resultados al proceso padre utilizando la tubería 
						6.- El proceso padre imprimirá todos los resultados
	 
	 Autor:		Michael Duarte
	 
	 */


	#include <unistd.h>
	#include <stdlib.h>
	#include <stdio.h>
	#include <string.h>


	short esPrimo(int); 	

	int main()
	{
	  int bytes,   fd[2],	A,	B;
	  char mensaje[80];
	  char buffer[BUFSIZ + 1];
	  pid_t fork_result;
	  memset(buffer, '\0', sizeof(buffer));
	  
	  //1.pedir 2 numeros:
	  printf("Intoduce 2 numeros :");
	  scanf("%d",&A);
	  scanf("%d",&B);
	  
	  
	  
	  
	  if (pipe(fd) == 0) {//2.- Crear una tubería ordinaria (pipe)
		//recibimos referencia de entero
		if ((fork_result = fork()) == -1) {//3.- Crear un proceso hijo
		fprintf(stderr, "Error en fork()");
		exit(EXIT_FAILURE);
		}
		if (fork_result == 0) {	//4.- Proceso hijo calculará # primos y aplicará digits entre A y B
		
		
		  int primos=0,i,j;//calculamos primos desde A a B
		  char string[10];
		  for (i=A;i<=B;i++){
			primos+=esPrimo(i);
		  }
		  
		  int cont[]={0,0,0,0,0,0,0,0,0,0};
		  for(i=A;i<=B;i++){////Aplicamos digits.
			  sprintf(string, "%d",i);
			  for(j=0;j<strlen(string);j++){
			cont[(string[j]-'0')]++;}
		  }
		
		
		  //5.- enviará los resultados al proceso padre utilizando la tubería 
		  //mandamos referencia del entero, dado que write solo funciona con punteros
		  bytes = write(fd[1], &primos, sizeof(primos));
		  printf("Proceso hijo: Mande resultado de primos en %d bytes\n", bytes); 
			
		  //mandamos puntero/arreglo de enteros
		  bytes= write(fd[1], cont, sizeof(cont));
		  printf("Proceso hijo: Mande resultado de Digits en %d bytes \n", bytes);
		  exit(EXIT_SUCCESS);
		 }
		else {//6.- El proceso padre imprimirá todos los resultados
		int resPrimos, resDigits[10],i;
		wait(NULL);//esperamos a que termine el proceso hijo
		
		bytes = read(fd[0], &resPrimos, sizeof(int));//recibimos referencia de entero
		printf("Numeros Primos: %d\n", resPrimos);
		
		printf("Digits: \t");
		//recibimos puntero/arreglo de enteros
		bytes = read(fd[0], resDigits, sizeof(resDigits));
		
		for(i=0; i<sizeof(resDigits)/sizeof(int);i++)
		  printf("%d ", resDigits[i]);
		printf("\n");
		}
	  }exit(EXIT_SUCCESS);
	}


	short esPrimo(int num){
	  if( num <= 1 )
		return 0;// numeros primos deben ser mayores  a 1
		int j;
	  for(j=num-1; j>1;j--)
		if(num%j == 0)
		  return 0;
		//printf("Numero primo: %d\n",num);
	  return 1;
	}