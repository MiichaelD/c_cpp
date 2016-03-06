/*
 * Programa:   grafo_l_d.c
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

/*
   Numero maximo de colonias 
*/

#define N 1000

struct vertice
{
   int nodo;
   int dist;
   struct vertice *next;
};

/*
 *   Prototipos de las funciones
*/

struct vertice * crear_lista(int);
int agregar_ele(struct vertice *, int, int, int);
void imprimir_lista(struct vertice *, int);

int main(int argc, char *argv[] )
{
   struct vertice *grafo;
   int i,n,x,y;
   char line[20];
   FILE *input;
/*
 *  Se verifica que se haya ingresado el nombre del archivo
*/   
    if (argc != 2) {
      printf("Error: debes indicar el nombre del archivo con los datos de entrada\n");
      return 0;
    }
/*
 *  Se abre el archivo con los datos de entrada
*/    
    input = fopen(argv[1], "r");
    if (input == NULL) {
       printf("Error: no fue posible abrir el archivo %s\n", argv[1]);
       return 0;
    }
 /*
  *  Se lee el numero de colonias
 */  
   if (fgets(line, sizeof(line),  input) == NULL) {
      printf("Error al leer archivo\n");
      return 0;
   }
   sscanf(line, "%d", &n);
   if (n > N) {
      printf("Error: numero de colonias demasiado grande\n");
      return 0;
   }
 /*
  *   Se crea arreglo de punteros a las listas de adyacencias
 */
   grafo = crear_lista(n);
 /*
  *   Se leen las rutas que unen a las colonias y se almacenan las rutas en las listas de adyacencias
 */

   printf("input:\n");
   printf("%d\n", n);
   for (i=1; i<n; i++) {
      if (fgets(line, sizeof(line),  input) == NULL){ 
         printf("Error al leer archivo\n");
         return;
      }
      sscanf(line, "%d%d", &x,&y);
      if ( !agregar_ele(grafo, i, x, y) ) {
         printf("Error al agregra ruta en lista\n");
         return 0;
      }
      printf("%d\t%d\n", x, y);
   } 
   
  
 /*
  *   Se imprime la matriz de adyacencias
 */
 
   printf("Lista de adyacencias:\n");
   imprimir_lista(grafo, n);
   
}

/*
 *   Codigo de las funciones
*/

/*
 *  Crea una lista de adyacencias para "s" vertices
*/

struct vertice * crear_lista(int s)
{
   struct vertice * aux;
   int j;
   
   aux = (struct vertice*) malloc(s * sizeof(struct vertice));
   if (!aux) {
      printf("Error al crear lista de adyacencias\n");
      return NULL;
   }
   
   for (j=0; j<s; j++) {
      aux[j].nodo = -1;
      aux[j].dist = 0;
      aux[j].next = NULL;
   }
   return aux;
}

/*
 *  Agrega a la lista "lista" la ruta con distancia "d" entre los vertices "v1" y "v2"
*/

int agregar_ele(struct vertice *lista, int v1, int v2, int d){
   struct vertice *aux, *new;
   aux = &lista[v1];
   if (aux -> nodo >= 0) {   // si no es el primer nodo de la lista se crea uno nuevo
      new = (struct vertice*) malloc (sizeof (struct vertice));
      if (!new) {
	 return 0;
      }
      new -> nodo = v2;
      new ->  dist = d;
      new -> next = NULL;
      while (aux -> next) {
	 aux = aux -> next;
      }
      aux -> next = new;
   } else {               // si el primer nodo de la lista no ha sido utilizado, se utiliza
      aux -> nodo = v2;
      aux -> dist = d;
   }
   // se agrega ruta de v2 a v1
   aux = &lista[v2];
   if (aux -> nodo >= 0) {  // si no es el primer nodo de la lista se crea uno nuevo
      new = (struct vertice*) malloc (sizeof (struct vertice));
      if (!new) {
	 return 0;
      }
      new -> nodo = v1;
      new ->  dist = d;
      new -> next = NULL;
      while (aux -> next) {
	 aux = aux -> next;
      }
      aux -> next = new;      
   } else {                // si el primer nodo de la lista no ha sido utilizado, se utiliza
      aux -> nodo = v1;
      aux -> dist = d;
   }
   return 1;
}

/*
 * Imprime la lista de adyacencias "lista" de "s" vertices
*/ 

void imprimir_lista(struct vertice * lista, int s)
{
   struct vertice *aux;
   int j;
   
   for (j=0; j<s; j++) {
      printf("Nodo %d: ", j);
      aux = &lista[j];
      while (aux) {
	 printf("%d,%d\t", aux -> nodo, aux -> dist);
	 aux = aux -> next;
      }
      printf("\n");
   }
}
