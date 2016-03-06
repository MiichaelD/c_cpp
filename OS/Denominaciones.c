/*
Programa:		Denominaciones.c

Objetivo: 			El programa debe imprimir cuántos billetes y monedas en efectivo debe entregar
				un cajero para al dueño del cheque. El cajero tan solo dispone de billetes de 50 y
				20 pesos, así como monedas de 10, 5, 2 y 1 peso.

Autor:			Michael Duarte
Fecha:			Septiembre 2012
*/

#include <stdio.h>

int denom[]={50,20,10,5,2,1};
void diffDenom(int,int[], int[],int);
void imprimirDenom(int[],int[],int);


int main(){
	int cantidad,  		size=sizeof(denom)/sizeof(int);
	int exit[size],		i;
	
	//inicializamos arreglo de salida con 0s
	for(i=0;i<size;i++)
		exit[i]=0;
	
	
	printf("Introduce cantidad del cheque: ");
	scanf("%d",&cantidad);
	
	//buscaremos variedad de denominaciones necesitaremos
	printf("Denominaciones para: %d\n",cantidad);
	diffDenom(cantidad,denom,exit,size);
	
	//imprimiremos la variedad de denominaciones
	imprimirDenom(denom,exit,size);
	
	return 0;
}

void diffDenom(int cantidad, int in[],int exit[], int size){
	int temp;
	int i = 0;
	for(i=0;i<size&&cantidad>0;i++){
		if((temp=cantidad/in[i])>0){
			//printf("%d x $%d\n",temp,in[i]);
			exit[i]=temp;
			cantidad-=temp*in[i];
		}
	}
}

void imprimirDenom(int denom[], int unidades[], int size){
	int i;
	for(i=0;i<size;i++){
		if(unidades[i]>0){
			printf("\t%d x $%d\n",unidades[i],denom[i]);
		}
	}
	
}
	