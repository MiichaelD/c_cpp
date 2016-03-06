/*
 Programa: 	TCP-cliente.c
 
 Descripción: 	Implementar el modelo cliente-servidor utilizando sockets, en Lenguaje C.
		1. El cliente solicitará dos números A y B al usuario, y 
		   enviará el valor de los números al servidor.
    
		2. El servidor determinará cuantos números primos existen
		   entre A y B, y aplicará el algortimo digits a los números A y B.
		   Posteriormente, enviará los resultados al cliente.
    
		3. El cliente imprimirá los resultados en pantalla.

Programador:	Michael Duarte

compilar:   gcc TCP-cliente.c -o client -lpthread -w

Fecha:		Octubre 2012

*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>

#define PORT htons(4444)         // numero de puerto al que el cliente se conectara
#define MAXDATASIZE 256 		  // tamano maximo del mensaje de  datos (bytes)

int main(int argc, char *argv[])
{
  int sockfd, numbytes, A,B;
  char buf[MAXDATASIZE];
  struct hostent *he;
  struct sockaddr_in their_addr;

  if (argc != 2) {
    fprintf(stderr,"debe utilizarse asi: HolaMundoClientTP hostname\n");
    exit(1);
  }
  
  ////////////////////////////////////////////////////////////////////////
  printf("Introduce 2 numeros: ");
  scanf("%d",&A);
  scanf("%d",&B);
  ////////////////////////////////////////////////////////////////////////
  
  if ((he=gethostbyname(argv[1])) == NULL) {  // se obtiene la info del servidor
    herror("gethostbyname");
    exit(1);
  }
  if ((sockfd = socket(PF_INET, SOCK_STREAM, 0)) == -1) {
    perror("socket");
    exit(1);
  }

  their_addr.sin_family = AF_INET;    // familia de direcciones de sockets (TCP/IP v4)
  their_addr.sin_port = PORT; // se convierte a  network byte order
  their_addr.sin_addr = *((struct in_addr *)he->h_addr);
  memset(&(their_addr.sin_zero), '\0', 8); // se ponen 0's en el resto de la estructura

  // se colicita conexion con el servidor
  if (connect(sockfd, (struct sockaddr *)&their_addr,sizeof(struct sockaddr)) == -1) {
    perror("connect");
    exit(1);
  }

  /////////////////////////////////////////////////////////////////////////////
  //enviamos numeros
  char str[256];  
  numbytes=sprintf(str,"%d %d",A,B);
  
  if (send(sockfd, str, numbytes, 0) == -1)
            perror("send");
  printf("Cliente: Se enviaron los datos correctamente: %s\n",str );
 // se recibe mensaje del servidor
  if ((numbytes=recv(sockfd, buf, MAXDATASIZE-1, 0)) == -1) {
    perror("recv1 - cliente");
    exit(1);
  }
  buf[numbytes] = '\0';
  printf("Cliente: Respuesta del servidor:\n%s\n",buf);
  
  
  ////////////////////////////////////////////////////////////////////////////////
  
  close(sockfd);
  return 0;
}
