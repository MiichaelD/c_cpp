/*
 Programa: 	TCP-servidor-fork.c
 
 Descripción: 	Implementar el modelo cliente-servidor utilizando sockets, en Lenguaje C.
		1. El cliente solicitará dos números A y B al usuario, y 
		   enviará el valor de los números al servidor.
 
		2. El servidor creará un proceso hijo que determinará cuantos números primos
		   existen  entre A y B, y aplicará el algortimo digits a los números A y B.
		   Posteriormente, enviará los resultados al cliente.
 
		3. El cliente imprimirá los resultados en pantalla.

 Nota:		El crear un proceso hijo utilizando fork(), nos permite seguir atendiendo
		  peticiones, en la linea 119 se duerme al proceso hijo para hacer notar que
		  el proceso padre sigue aceptando conexiones y creando nuevos procesos hijo.
 
 Programador:	Michael Duarte
 
 Fecha:		Octubre 2012
 
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>

#define MYPORT htons(4444)		// numero de puerto para recibir conexiones
#define BACKLOG 100				// numero de conexiones pendientes

short esPrimo(int);

int main(void)
{
    int sockfd, new_fd,numbytes;
    struct sockaddr_in myAddr;  // direccion del servidor
    struct sockaddr_in clientAddr; // direccion remota
    socklen_t sin_size;
    int yes=1;

    // se crea el socket
    if ((sockfd = socket(PF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }

    // se define el comportamiento del socket
    if (setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(int)) == -1) {
        perror("setsockopt");
        exit(1);
    }

    myAddr.sin_family = AF_INET;          // familia de direcciones de sockets (TCP/IP v4)
    myAddr.sin_port = MYPORT;      // se convierte a  network byte order
    myAddr.sin_addr.s_addr = INADDR_ANY;  // se obtiene direccion local
    memset(&(myAddr.sin_zero), '\0',8);   //  se ponen 0's en el resto de la estructura
    if (bind(sockfd, (struct sockaddr *)&myAddr, sizeof(struct sockaddr)) == -1) {
        perror("bind");
        exit(1);
    }

    // se habilita el puerto para recibir conexiones
    if (listen(sockfd, BACKLOG) == -1) {
        perror("listen");
        exit(1);
    }

    while(1) { // ciclo infinito del servidor, en el que se reciben conexiones de clientes
        sin_size = sizeof(struct sockaddr_in);

	// se espera una nueva conexi�n
        if ((new_fd = accept(sockfd, (struct sockaddr *)&clientAddr,&sin_size)) == -1) {
            perror("accept");
            continue;
        }
		
		if(fork() == 0){//se crea un proceso hijo para que atienda la conexión
		  // ha llegado una conexion!
		  ///////////////////////////////////////////////////////////////////////////////////
		  int num1,num2,nPrimos=0,i,j;
		  char str[256];
		  int cont[]={0,0,0,0,0,0,0,0,0,0};
		  if ((numbytes=recv(new_fd, str, 35, 0)) == -1) {
			  perror("recv - servidor");
			  exit(1);
		  }
		  str[numbytes] = '\0';
		  printf("\tRECIBIMOS:%s\t\t de cliente: %s\t\n",str,inet_ntoa(clientAddr.sin_addr));
		  
		  sscanf(str,"%d %d",&num1,&num2);//obtenemos numeros
		  
		  memset(str,'\0',256);//limpiamos string
		  
		  for(i=num1;i<=num2;i++){//DIGITS
		    sprintf(str, "%d",i);//se convierte a String
		    for(j=0;j<strlen(str);j++){//se recorren caracteres
		      cont[(str[j]-'0')]++;}//se incrementa dependiendo de caracter que es
		  }
		  
		  for (i=num1;i<=num2;i++){//PRIMOS
			  nPrimos+=esPrimo(i);
		  }
		  
		  memset(str,'\0',256);
		  sprintf(str,"Digits:\t\t\t");
			  
		  for (i=0;i<10;i++){//Concatenamos el arreglo de enteros en un string
			  sprintf(str,"%s%d ",str,cont[i]);
		  }
		  sprintf(str,"%s\nNumeros Primos: \t%d",str,nPrimos);
		
	 	  
		  printf("Servidor %d: conectado a:%s\t TERMINÓ\n",getpid(), inet_ntoa(clientAddr.sin_addr));
		  if (send(new_fd, str,(sizeof(str)/sizeof(char)), 0) == -1)
		    perror("send");
				  
		  
		  /////////////////////////////////////////////////////////////////////////////////////
		  close(new_fd); // se cierra la conexion
		  exit(EXIT_SUCCESS);//se termina el proceso hijo
		}
    }

  return 0;
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

