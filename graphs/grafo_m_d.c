/*
 * Programa:   grafo_m.c
 * 
 * Objetivo:   Implementar la colonia de hormigas del problema "Ants Colony" utilizando un grafo. El grafo es representado con
 *             una matriz de adyacencias (dinamica).
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


/*
 *   Prototipos de las funciones
*/

int crear_matriz(int *** matrix, int row, int col);
void imprime_matriz(int ** matrix, int row, int col);

int main(int argc, char *argv[] )
{
   
   int **grafo;
   int **paths;
   int i,j,n,x,y;
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
  *   Se crea matriz de adyacencias
 */
    if ( !crear_matriz(&grafo, n, n) ) {
      fprintf(stderr,"Error: No fue posible crear la matriz de adyacencias\n");
      return 0;
   }

 /*
  *   Se crea matriz para almacenar las rutas
 */
    if ( !crear_matriz(&paths, n, 2) ) {
       fprintf(stderr,"Error: No fue posible crear la matriz de rutas\n");
       return 0;
   }

 /*
  *   Se leen las rutas que unen a las colonias
 */

 printf("input:\n");
 printf("%d\n", n);
 for (i=1; i<n; i++) {
      if (fgets(line, sizeof(line),  input) == NULL){ 
	  printf("Error al leer archivo\n");
	  return;
      }
      sscanf(line, "%d%d", &x,&y);
      paths[i][0] = x;
      paths[i][1] = y;
      printf("%d\t%d\n", paths[i][0], paths[i][1]);
   }
   
/*
 *  Se almacenan las rutas en la matriz de adyacencias
*/
   for (i=1; i<n; i++) {
      x = paths[i][0];
      grafo[i][x] = paths[i][1];
      grafo[x][i] = paths[i][1];
   }
   
 /*
  *   Se imprime la matriz de adyacencias
 */
 
   printf("\nMatriz de adyacencias:\n");
   imprime_matriz(grafo, n, n);
   
}

/*
 *   Codigo de las funciones
*/

int crear_matriz(int ***matrix, int r, int c)
{
   int k,l;
   
   (*matrix) = (int **) malloc (r * sizeof(int *));
   if ( !(*matrix) ) {
      return 0;
   }
   for (k=0; k<r; k++) {
      (*matrix)[k] = (int *) malloc(c * sizeof(int));
      if (! (*matrix)[k] ) {
	 return 0;
      }
   }
   
   for (k=0; k<r; k++)
      for (l=0; l<c; l++)
	 (*matrix)[k][l] = 0;   
   
   return 1;
}

void imprime_matriz(int ** matrix, int r, int c)
{
   int i, j;
   
   for (i=0; i<r; i++) {
      for (j=0; j<c; j++) {
	 printf("%d\t", matrix[i][j]);
      }
      printf("\n");
   }
}