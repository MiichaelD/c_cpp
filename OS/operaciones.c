/*
Programa:		operaciones.c
Objetivo:		Lee 2 numeros enteros a y b para calcular:
			-Suma de a y b
			-Resta de a y b
			-Sumatoria de 1 hasta a
			-El factorial de a
			
Autor:			Michael Duarte
Fecha:			Septiembre 2012
*/

#include <stdio.h>

int suma(int,int);
int resta(int,int);
double sumatoria(int);
double factorial(int);
int a,b;

void main(){
	printf("Introduce el valor de A: ");
	scanf("%d",&a);
	
	printf("Introduce el valor de B: ");
	scanf("%d",&b);
	
	printf("\n");
	printf("Suma de %d + %d = %d\n",a,b,suma(a,b));
	printf("Resta de %d - %d = %d\n",a,b,resta(a,b));
	printf("Sumatoria de 1 hasta %d = %.0f\n",a,sumatoria(a));
	printf("Factorial de %d = %.0f\n",a,factorial(a));  
}

int suma(int m,int n){
	return m+n;
}

int resta(int m,int n){
	return m-n;
}

double sumatoria(int m){
	return ((1+m)*m)/2;
}

double factorial(int m){
	double conta=1;
	int i;
	for(i=1;i<=m;i++) {
		conta*=i;
	}
	return conta;
}
