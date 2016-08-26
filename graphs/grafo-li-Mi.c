/*
 * Programa:   grafo_l.c
 * 
 * Objetivo:   Implementar la colonia de hormigas del problema "Ants Colony" utilizando un grafo. El grafo es representado con
 *             una lista de adyacencias (dinamica).
 *             Los datos del programa se leen de un archivo. Para ejecutar el programa, escribir:
 * 
 *             ./grafo_m input
 * 
 *             en donde "input" es el nombre del archivo que contiene los datos de entrada.
 * 
 * Autor:      Arnoldo Diaz Ramirez
 * 
 * Fecha:      Marzo de 2012
*/


#include <stdio.h>
#include <stdlib.h>

 void addLast(int i);

 struct vertice
 {
   int nodo;
   int dist;
   struct vertice *next;
 };

 struct vertice *grafo, *new, *aux;
 int i,n,x,y;
 char line[20];
 FILE *input;
 
 int main(int argc, char *argv[] )
 {
/*
 *  Se verifica que se haya ingresado el nombre del archivo
*/   
 if (argc != 2) {
  printf("Error: debes indicar el nombre del archivo con los datos de entrada\n");
  return 0;}
/*
 *  Se abre el archivo con los datos de entrada
*/    
 input = fopen(argv[1], "r");
 if (input == NULL) {
   printf("Error: no fue posible abrir el archivo %s\n", argv[1]);
   return 0;}
  /*
  *  Se lee el numero de colonias
 */  
  
  if (fgets(line, sizeof(line),  input) == NULL) {
    printf("Error al leer archivo\n");
    return 0;
  }
  
  sscanf(line, "%d", &n);   
 /*
  *   Se crea punteros a las listas de adyacencias
 */

  grafo = (struct vertice*) malloc(n * sizeof(struct vertice));
  
  for (i=0; i<n; i++) {
    grafo[i].next = NULL;
    grafo[i].nodo = 0;
    grafo[i].dist = 0;
  }

  printf("input:\n");
  printf("%d\n", n);
  for (i=1; i<n; i++) {
   fgets(line, sizeof(line),  input) ;
   sscanf(line, "%d%d", &x,&y);
   printf("%d.-\t%d\t%d\n", i, x, y);
   
   new = (struct vertice*) malloc (sizeof (struct vertice));
   new -> nodo = x;
   new ->  dist = y;
   new -> next = NULL;
   addLast(i);
   new = (struct vertice*) malloc (sizeof (struct vertice));
   new -> nodo = i;
   new -> dist = y;
   new -> next = NULL;
 }

 printf("Lista de adyacencias:\n");
 for (i=0; i<n; i++) {
  printf("Nodo %d: ", i);
  aux=grafo[i].next;
  while (aux->next!=NULL) {
    printf("%d,%d\t->", aux->nodo, aux->dist);
    aux=aux->next;
  }
  printf("\n");
}
}


void addLast(int i){
	int ciclos=0;
	aux=&grafo[i];	
	while(1){
   if(aux -> next != NULL){
     ciclos++;
     aux=aux->next;	
   }
   else {
     aux->next=new;	
     printf("en %d, se agrego %d,%d CORRECTAMENTE, ahora hay %d nodos\n",i,new->nodo,new->dist,(ciclos+1));
     return;}
   }
 }
