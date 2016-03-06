/*
 *    Programa:   fifoProductor.c
 * 
 *    Funcion:    Utilizando POSIX FIFOs implementar con dos procesos el modelo Productor-Consumidor,
 *		de la siguiente manera:    
 *		
 *		  El cliente solicitará dos números A y B al usuario, y enviará el valor de los números
 *		al servidor, utilizando una FIFO.
 *		  El servidor determinará cuantos números primos existen entre A y B, y aplicará el
 *		algortimo digits a los números A y B. Posteriormente, enviará los resultados al cliente
 *		utilizando la FIFO.
 *		  El cliente imprimirá los resultados en pantalla.
 * 
 *    Autor:    	Michael Duarte
 *    
 *    Fecha:	Octubre 2012
 * 
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

#define TEN_MEG (1024 * 1024 * 10)//10 megabytes

short esPrimo(int);

int main()
{
  int pipe_fd,A,B,nPrimos,i,j,cont[10];
  int res;
  int bytes_sent = 0;
  char buffer[PIPE_BUF + 1];
  
  if (access(FIFO_NAME, F_OK) == -1) {//si no podemos accesar a la fifo
      printf("No pudimos accesar a fifo, asi que creamos una.\n");
      res = mkfifo(FIFO_NAME, 0777);   // creamos una nueva
      if (res != 0) {
	fprintf(stderr, "No fue posible crear la FIFO %s\n", FIFO_NAME);
	exit(EXIT_FAILURE);
      }
  }
  
  // LEEEEEEEEEEMOS /////////////////////////////////////////////////////////////////
  printf("\nProceso productor con pid %d abriendo la FIFO en modo O_RDONLY\n", getpid());
  pipe_fd = open(FIFO_NAME, O_RDONLY);
  printf("El proceso productor con pid %d obtuvo como resultado %d\n", getpid(), pipe_fd);
  if (pipe_fd != -1) {
    
    //leemos par de numeros
    res = read(pipe_fd, buffer, PIPE_BUF);
    buffer[res]='\0';
    sscanf(buffer,"%d %d",&A,&B);
    (void)close(pipe_fd);
  }
  else {
    exit(EXIT_FAILURE);
  }
  
  /////////////////////DIGITS y PRIMOS////////////////////////////////////////////////
  for(i=A;i<=B;i++){//DIGITS
        sprintf(buffer, "%d",i);//se convierte a String
	for(j=0;j<strlen(buffer);j++){//se recorren caracteres
            cont[(buffer[j]-'0')]++;}//se incrementa dependiendo de caracter que es
  }
  
  
  for (i=A;i<=B;i++){//PRIMOS
	nPrimos+=esPrimo(i);
  }
  
  sprintf(buffer,"Digits:\t\t\t");////pasamos resultados a string
  for (i=0;i<10;i++){//Concatenamos el arreglo de enteros en un string
		sprintf(buffer,"%s%d ",buffer,cont[i]);
  }
  sprintf(buffer,"%s\nNumeros Primos: \t%d",buffer,nPrimos);
  
  ////ESCRIBIMOS////////////////////////////////////////////////////////////////////////
  printf("\nProceso productor con pid %d abriendo la FIFO en modo O_WRONLY\n", getpid());
  pipe_fd = open(FIFO_NAME, O_WRONLY);
  printf("El proceso productor con pid %d obtuvo como resultado %d\n", getpid(), pipe_fd);
  if (pipe_fd != -1) {
      if ((res = write(pipe_fd, buffer, PIPE_BUF)) == -1) {
	fprintf(stderr, "Error al escribir en FIFO\n");
	exit(EXIT_FAILURE);
      }
      bytes_sent += res;
    (void)close(pipe_fd);
  }
  else {
    exit(EXIT_FAILURE);
  }
  printf("Proceso productor con pid %d concluido\n", getpid());
  exit(EXIT_SUCCESS);
}



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
