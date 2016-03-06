/*
   Programa:  HolaMundoClientTPC.c

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
#define PORT 4444         // numero de puerto al que el cliente se conectara
#define MAXDATASIZE 200   // tamano maximo del mensaje de  datos (bytes)

int main(int argc, char *argv[])
{
  int sockfd, numbytes;
  char buf[MAXDATASIZE];
  struct hostent *he;
  struct sockaddr_in their_addr;

  if (argc != 2) {
    fprintf(stderr,"debe utilizarse asi: HolaMundoClientTP hostname\n");
    exit(1);
  }
  if ((he=gethostbyname(argv[1])) == NULL) {  // se obtiene la info del servidor
    herror("gethostbyname");
    exit(1);
  }
  if ((sockfd = socket(PF_INET, SOCK_STREAM, 0)) == -1) {
    perror("socket");
    exit(1);
  }

  their_addr.sin_family = AF_INET;    // familia de direcciones de sockets (TCP/IP v4)
  their_addr.sin_port = htons(PORT); // se convierte a  network byte order
  their_addr.sin_addr = *((struct in_addr *)he->h_addr);
  memset(&(their_addr.sin_zero), '\0', 8); // se ponen 0's en el resto de la estructura

  // se colicita conexion con el servidor
  if (connect(sockfd, (struct sockaddr *)&their_addr,
	      sizeof(struct sockaddr)) == -1) {
    perror("connect");
    exit(1);
  }

 // se recibe mensaje del servidor
  if ((numbytes=recv(sockfd, buf, MAXDATASIZE-1, 0)) == -1) {
    perror("recv");
    exit(1);
  }
  buf[numbytes] = '\0';
  printf("Recibido: %s\n",buf);  // se imprime mensaje recibido
  close(sockfd);
  return 0;
}
