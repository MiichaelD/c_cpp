/*
Programa:				Utilizar la funcion fork para crear nuevos procesos.
*/

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

main(){
	int return_value;
	//La funcion fork, retorna un 0 al proceso hijo y  el PID del proceso hijo al proceso padre.
	printf("Creando procesos con fork\n");
	return_value=fork();
	if(return_value == 0 ) {
		printf("El PID del proceso HIJO es %d, mi hijo es: %d \n",getpid(),return_value);
	}
	else{
		printf("El PID del proceso Padre es %d, mi hijo es: %d \n",getpid(),return_value);
	}
}