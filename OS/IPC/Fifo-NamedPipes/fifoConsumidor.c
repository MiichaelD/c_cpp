/*
 *    Programa:   fifoConsumidor.c
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


int main()
{
  int pipe_fd,A,B;
  int res;
  char buffer[PIPE_BUF + 1];
  int bytes_read = 0;
  memset(buffer, '\0', sizeof(buffer));		//limpiamos buffer
  
  
  printf("Proceso consumidor con pid %d abriendo la FIFO en modo O_WRONLY\n", getpid());
  pipe_fd = open(FIFO_NAME, O_WRONLY);			//abrimos fifo solo lectura
  printf("El proceso consumidor con pid %d, resultado al abrir pipa: %d\n", getpid(), pipe_fd);
  
  if (pipe_fd != -1) {				//enviamos numeros
    
    printf("\nIntroduce 2 numeros: ");//capturamos numeros
    scanf("%d",&A);
    scanf("%d",&B);
    res=sprintf(buffer,"%d %d",A,B);
    buffer[res]='\0';

    if(write(pipe_fd,buffer,PIPE_BUF) == -1){
      printf("Error enviando numeros a productor\n");
      exit(EXIT_FAILURE);
      (void)close(pipe_fd);			//cerramos pipa
    }
  }else{
    exit(EXIT_FAILURE);
  }
  
  sleep(1);
  printf("\nProceso productor con pid %d abriendo la FIFO en modo O_RDONLY\n", getpid());
  pipe_fd = open(FIFO_NAME, O_RDONLY);
  printf("El proceso consumidor con pid %d, resultado al abrir pipa: %d\n", getpid(), pipe_fd);
  if (pipe_fd != -1) {
    printf("\n");
    //leemos y almacenamos en buffer (tamaño definido en limits.h)
    res = read(pipe_fd, buffer, PIPE_BUF);
    bytes_read += res;
    printf("%s\ns",buffer);
     
    
    (void)close(pipe_fd);//cerramos pipa
    printf("\nTermina consumidor con pid: %d\n",getpid());
  }
  else {
    exit(EXIT_FAILURE);
  }
  
  exit(EXIT_SUCCESS);
}
