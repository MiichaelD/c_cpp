/*
 * Programa: 		Servidor.c
 * 
 * Descripción: 	Elaborar una aplicación Cliente-Servidor utilizando Sockets, con las siguientes características:
 * 
 *				1.- El Servidor deberá estar implementado en Lenguaje C
 *				2.- Por cada solicitud que llegue al Servidor, deberá crearse un proceso o hilo para atenderla.
 *				3.- Los servicios que pueden solicitar los clientes son:
 *					a) Alta de alumnos
 *					b) Baja de alumnos
 *					c) Modificacion de datos de alumno (excepto número de control)
 *					d) Consulta de los datos del alumno utilizando el número de control
 *				4.- Deberá utilizarse algún mecanismo de sincronización en el servidor
 *				5.- Los datos de los alumnos y las carreras deberán almacenarse en los archivos alumnos.db y carreras.db, respectivamente
 *				6.- El Cliente puede implementarse en cualquier lenguaje
 * 
 *				
 * Compilacion:		gcc Servidor.c -o servidor -lpthread -w
 * 
 * Programador:		Michael Duarte
 * 					Hector García
 * 
 * Fecha:			Diciembre 2012
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
#include <string.h>
#include <pthread.h>

#define MYPORT 	htons(4444)		// numero de puerto para recibir conexiones
#define BACKLOG 100				// numero de conexiones pendientes
#define MAXSIZE 128
#define LOCK 	pthread_mutex_lock(&mutex); 
#define UNLOCK 	pthread_mutex_unlock(&mutex);


int sockfd, new_fd, yes=1;
struct sockaddr_in myAddr; 		 	// direccion del servidor
struct sockaddr_in clientAddr; 		// direccion remota
socklen_t sin_size;
pthread_mutex_t mutex;				//solo ocuparemos un mutex, cualqier operacion bloqueara a las demas

void prepareSocket(){
  if ((sockfd = socket(PF_INET, SOCK_STREAM, 0)) == -1) {// se crea el socket
		perror("socket");     exit(1);
  }
  
  if (setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(int)) == -1) {// Opciones de Socket
		perror("setsockopt");    exit(1);
	}

	myAddr.sin_family = AF_INET;          // familia de direcciones de sockets (TCP/IP v4)
	myAddr.sin_port = MYPORT;    		  // se convierte a  network byte order
	myAddr.sin_addr.s_addr = INADDR_ANY;  // se obtiene direccion local
	memset(&(myAddr.sin_zero), '\0',8);   //  se ponen 0's en el resto de la estructura

	if (bind(sockfd, (struct sockaddr *)&myAddr, sizeof(struct sockaddr)) == -1) {
	  perror("bind");       exit(1);
	}

	if (listen(sockfd, BACKLOG) == -1) {// se habilita el puerto para recibir conexiones
			perror("listen");      exit(1);
	}

}

int encontrarCarrera(char * carrera){
  char read[MAXSIZE],mod[MAXSIZE],car[MAXSIZE];
  int num;
  char *temp;
  memset(car,'\0',MAXSIZE);
  LOCK
  FILE *file = fopen("carreras.db","r+");
  if(file != NULL)
    while (fgets(read,sizeof(read),file) != NULL){//fgets no guarda en punteros de caracteres.
			strcpy(mod,read);
			temp=strtok(mod,"\t\r\n "); 
			num=atoi(temp);
			temp=strtok(NULL," \t\n\r");
			while(temp!=NULL){
			  strcat(car,temp);
			  if( (temp=strtok(NULL," \n\r\t")) != NULL) 
			    strcat(car," ");
			}
			//printf("%s == '%s' ? %d\n",carrera,car,strcmp(carrera,car));
			if(strcmp(carrera,car) == 0 ){
			  fclose(file);
			  UNLOCK
			  return num;
			}
			memset(car,'\0',MAXSIZE);
    }
    
    fclose(file);
    UNLOCK
    return 0;
}

char * Carrera(int carrera){
  char read[MAXSIZE],mod[MAXSIZE],car[MAXSIZE];
  int num;
  char *temp;
  memset(car,'\0',MAXSIZE);
  LOCK
  FILE *file = fopen("carreras.db","r+");
  if(file != NULL)
    while (fgets(read,sizeof(read),file) != NULL){//fgets no guarda en punteros de caracteres.
			strcpy(mod,read);
			temp=strtok(mod,"\t\r\n "); 
			num=atoi(temp);
			if(num == carrera ){
			  temp=strtok(NULL," \t\n\r");
			  while(temp!=NULL){
			    strcat(car,temp);
			    if( (temp=strtok(NULL," \n\r\t")) != NULL) 
			      strcat(car," ");
			  }
			  fclose(file);
			  UNLOCK
			  return car;
			}			
    }
    
    fclose(file);
    UNLOCK
    strcat(car,"NULL");
    return car;
}

short alta(char * cad,int size){
	char *nCon,*nombre,*carrera;
	char read[MAXSIZE],rNcon[MAXSIZE];
	cad[size]='\0';
	nCon = strtok(cad,"&");
	nombre = strtok(NULL,"&");
	carrera = strtok(NULL,"&");
	int car=encontrarCarrera(carrera);
	if(car==0)
	  return 1;
	  
	LOCK
	FILE *file = fopen("alumnos.db","r+");
	if(file != NULL)
		while (fgets(read,MAXSIZE,file) != NULL){//fgets no guarda en punteros de caracteres.
			strcpy(rNcon,read);
			strtok(rNcon,"\t");//nos quedamos con el primer token
			//printf("%s == %s ?\n",rNcon,nCon);
			if(strcmp(rNcon,nCon) == 0 ){
			  fclose(file);
			  UNLOCK
			  return 2;
			}
		}
	else perror("Error al abrir archivo alumnos - altas\n");

	fclose(file);
	UNLOCK

	char newAlumno[size];
	sprintf(newAlumno,"%s\t%s\t%d\n",nCon,nombre,car);
	LOCK
	file = fopen("alumnos.db","a+");
	fputs(newAlumno,file);
	fclose(file);
	UNLOCK
	return 0;
}

short baja(char * nCon,int size){
  nCon[size]='\0';
short found=0;

LOCK
FILE *file = fopen("alumnos.db","r+");
FILE *temp = fopen("temp.txt","w+");
char read[MAXSIZE],rNcon[MAXSIZE];

if(file != NULL)
  while (fgets(read,MAXSIZE,file) != NULL){//fgets no guarda en punteros de caracteres.
			strcpy(rNcon,read);
			strtok(rNcon,"\t");//nos quedamos con el primer token
			//printf("%s == %s ? %d\n",rNcon,nCon,strcmp(rNcon,nCon));
			if(strcmp(rNcon,nCon)){
			  fputs(read,temp);
			}
			else found=1;
  }
  
  fclose(file);
  fclose(temp);
  remove("alumnos.bd");
  rename("temp.txt","alumnos.db");
UNLOCK

if(found)
  return 0; 
return 1;
}

char * consu(char * nCon,int size){
  nCon[size]='\0';
    short found=0;
    
    LOCK
    FILE *file = fopen("alumnos.db","r+");
    char read[MAXSIZE],rNcon[MAXSIZE];
    char * temp;
    
    if(file != NULL)
      while (fgets(read,MAXSIZE,file) != NULL){//fgets no guarda en punteros de caracteres.
			strcpy(rNcon,read);
			strtok(rNcon,"\t\n\r ");//nos quedamos con el primer token
			//printf("%s == %s ? %d\n",rNcon,nCon,strcmp(rNcon,nCon));
			if(!strcmp(rNcon,nCon)){
			  fclose(file);
			  UNLOCK
			  memset(nCon,'\0',strlen(nCon));
			  memset(rNcon,'\0',strlen(rNcon));
			  strcat(nCon,read);
			  if(nCon[strlen(nCon)-3] != '\t'){
			    rNcon[0]=nCon[strlen(nCon)-3];
			    rNcon[1]=nCon[strlen(nCon)-2];
			    nCon[strlen(nCon)-3]='\0';
			  }
			  else{
			    rNcon[0]=nCon[strlen(nCon)-2];
			    nCon[strlen(nCon)-2]='\0';
			  }
			  strcat(nCon,Carrera(atoi(rNcon)));
			  return nCon; 
			}
}

fclose(file);
UNLOCK
memset(nCon,'\0',sizeof(nCon));
strcat(nCon,"ER - Numero de Control No Registrado");
return nCon;
}

short modif(char * cad,int size){
  char *nCon,*nombre,*carrera;
  char str[MAXSIZE];
  cad[size]='\0';
  nCon = strtok(cad,"&");
  nombre = strtok(NULL,"&");
  carrera = strtok(NULL,"&");
  int car=encontrarCarrera(carrera);
  if(!car)
    return 2;
  sprintf(str,"%s\t%s\t%d\n",nCon,nombre,car);
  int found=0;
  
  LOCK
  FILE *file = fopen("alumnos.db","r+");
  FILE *temp = fopen("temp.txt","w+");
  char read[MAXSIZE],rNcon[MAXSIZE];
  
  if(file != NULL)
    while (fgets(read,MAXSIZE,file) != NULL){//fgets no guarda en punteros de caracteres.
			strcpy(rNcon,read);
			strtok(rNcon,"\t");//nos quedamos con el primer token
			//printf("%s == %s ? %d\n",rNcon,nCon,strcmp(rNcon,nCon));
			if(strcmp(rNcon,nCon)){
			  fputs(read,temp);
			}
			else{
			  found=1;
			  fputs(str,temp);
			}
}

fclose(file);
fclose(temp);
remove("alumnos.bd");
rename("temp.txt","alumnos.db");
UNLOCK

if(found)
  return 0; 
return 1;
}

void * attendClient(void * x){
  char str[MAXSIZE];
  int new_connection=(int) x;
  int numbytes;
  printf("valor de nueva conexion: %d\n",new_connection);
  memset(str,'\0',MAXSIZE);
  
  if ((numbytes=recv(new_connection, str, MAXSIZE, 0)) == -1) {
    perror("recv - servidor");		exit(1);
  }
  
  //printf("\tRECIBIMOS:%s\t de cliente: %s\t\n",str,inet_ntoa(clientAddr.sin_addr));
  
  switch(str[--numbytes]){
    case 'a': 
      printf("Altas: \n");
      switch(alta(str,numbytes)){
	case 0:
	  if (send(new_connection, "OK",2, 0) == -1)
	    perror("send");
	  break;
	  
	case 1:
	  if (send(new_connection, "ER - Carrera No Existe",22, 0) == -1)
	    perror("send");
	  break;
	  
	case 2:
	  if (send(new_connection, "ER - Numero de control Ya Registrado",36, 0) == -1)
	    perror("send");
	  break;
      }
      break;
      
	case 'b': 
	  if(!baja(str,numbytes)){
	    if (send(new_connection, "OK",2, 0) == -1)
	      perror("send");
	  }
	  else
	    if (send(new_connection, "ER - Numero de Control No Registrado",36, 0) == -1)
	      perror("send");
	    break;
	  
	  
	case 'c': 
	  
	  if (send(new_connection, consu(str,numbytes),sizeof(str), 0) == -1)
	    perror("send");
	  
	  break;
	  
	case 'm': 
	  switch(modif(str,numbytes)){
	  case 0:
	      if (send(new_connection, "OK",2, 0) == -1)
		perror("send");
	      break;
	      
	  case 1:
	      if (send(new_connection, "ER - Numero de Control No Registrado",36, 0) == -1)
		perror("send");
	      break;
	  
	  case 2:
	    if (send(new_connection, "ER - Carrera No Existe",22, 0) == -1)
	      perror("send");
	    break;
	  }
	  break;
	  
	default:
	  if (send(new_connection, "ER - Comando No Encontrado",26, 0) == -1)
	    perror("send");
	  break; 
  }  
  
  /////////////////////////////////////////////////////////////////////////////////////
  close(new_connection); // se cierra la conexion
  printf("***Se termina el hilo que atendio la conexion: #%d***\n",new_connection);
  pthread_exit(NULL);//se termina el hilo
}



int main (int argn, char **argv){  
  int envio;
  prepareSocket(); 
  
  pthread_t hilo;
  pthread_mutex_init(&mutex, NULL);
  
  //Creamos los archivos - si no han sido creados//
  FILE *file = fopen("alumnos.db","a+");
  fclose(file);
  file = fopen("carreras.db","a+");
  fclose(file);
  
  while(1) { // ciclo infinito del servidor, en el que se reciben conexiones de clientes
		sin_size = sizeof(struct sockaddr_in);
		
		// se espera una nueva conexion
		if ((new_fd = accept(sockfd, (struct sockaddr *)&clientAddr,&sin_size)) == -1) {
		  perror("accept");
		  continue;
		}
		
		envio= (int) malloc(sizeof(int));
		envio=new_fd;
		
		///////////// ha llegado una conexion!/////////////////////////////////////
		hilo = (pthread_t) malloc (sizeof(pthread_t));//creamos nuevo hilo
		pthread_create(&hilo, NULL, &attendClient, (void *)envio);//inicializamos el nuevo hilo
  }
  pthread_mutex_destroy(&mutex);
  
  return 0;
}


