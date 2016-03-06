/*
Programa:               ForkDigits.c

Objetivo:                   Crear un proceso hijo que realizara el programa digits.c	
						lee dos números enteros a y b (0 <= a <= b <= 100000). Posteriormente,
						el programa creará un proceso hijo quien ejecutará el código del
						programa digits.c (ver archivo con definición del problema "Digits")
						y que imprima los resultados. el padre imprimira cuantos numeros primos hay
						de A a B inclusive y tambien imprimira el resultado de digits generado por su
						hijo, utilizar archivos temporales
						 
Nota:						La funcion fork, retorna un 0 al proceso hijo y	el PID del proceso
						hijo al proceso padre. 
                              
Autor:                  Michael Duarte
						Hector García
						
Fecha:                  Octubre 2012
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//#include <unistd.h> // No es necesario

char string[100];
int num1,num2,i;
int j,es_hijo;
FILE *result=NULL;
//declaración de funciones:
short esPrimo(int);

void main(){
     
	 printf("Dame 2 numeros: ");
     scanf("%d",&num1);
     scanf("%d",&num2);
	
	 es_hijo=fork();
	 
	if(es_hijo == 0){//solo el hijo hara esto
              int cont[]={0,0,0,0,0,0,0,0,0,0};
              for(i=num1;i<=num2;i++){
                   sprintf(string, "%d",i);//se convierte a String
                   for(j=0;j<strlen(string);j++){//se recorren caracteres
                        cont[(string[j]-'0')]++;}//se incrementa dependiendo de caracter que es
              }
			  
			  
			  memset(string,'\0',sizeof(string));//limpiamos variable string
			  sprintf(string,"%d.tmp",(int)getpid());//usaremos PID de nombre para archivo
			  result= fopen(string,"w");
			  if(result!=NULL){
					//printf("\nSoy hijo, el resultado de digits para %d & %d es:\n",num1,num2);
				for(i=0;i<10;i++)//se imprime vector con resultados
					fprintf(result,"%d ",cont[i]);
				fprintf(result,"\n");
				fclose(result);
			  }
			  else{
				printf("No se pudo crear archivo");
				return;
			  }
     }
	else{
			int primos=0;
			char archivo[15];
			memset(string,'\0',sizeof(string));//limpiamos variable string
			memset(archivo,'\0',sizeof(archivo));
			for (i=num1;i<=num2;i++){
				primos+=esPrimo(i);
			}
			printf("\nNumeros primos desde %d hasta %d:\t\t%d\n",num1,num2,primos);
			sprintf(archivo,"%d.tmp",(int)es_hijo);//usaremos PID del hijo como nombre para archivo
			//printf("************** archivo: %s ***************\n",archivo);			  
			wait(NULL);// ESPERAMOS A QUE PROESO HIJO TERMINE
			result= fopen(archivo,"r");//abrimos archivo en modo lectura
			if(result!=NULL){
				memset(string,'\0',sizeof(string));//limpiamos variable string
				fgets(string,sizeof(string),result);//leemos la linea
				fclose(result);//cerramos archivo
				printf("Resultado de Digits proceso Hijo:\t%s",string);
				//remove(archivo); // elimina  el archivo temporal
			}
			else{
				printf("No se encontro archivo de proceso Hijo :C\n");
			}
			  		
		}			
}

short esPrimo(int num){
	if( num <= 1 )
		return 0;// numeros primos deben ser mayores  a 1
	for(j=num-1; j>1;j--)
		if(num%j == 0)
			return 0;
	//printf("Numero primo: %d\n",num);
	return 1;
}

