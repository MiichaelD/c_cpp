/*
 * Programa:   grafo_m.c
 * 
 * Objetivo:   Implementar la colonia de hormigas del problema "Ants Colony" utilizando un grafo. El grafo es representado con
 *             una matriz de adyacencias (est√°tica).
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

int main(int argc, char *argv[] )
{
   
   int grafo[N][N];
   int paths[N][2];
   int i,j,n,x,y;
   char line[20];
   FILE *input;
   
/*
 *  Se verifica que se haya ingresado el nombre del archivo
*/   
    if (argc != 2) {
      printf("Error: debes indicar el nombre del archivo con los datos de entrada\n");
      return;
    }

/*
 *  Se abre el archivo con los datos de entrada
*/    
    input = fopen(argv[1], "r");
    if (input == NULL) {
       printf("Error: no fue posible abrir el archivo %s\n", argv[1]);
       return;
    }

 /*
 *  Se inicializa en cero cada elemento
 *  de la matriz de adyacencias
*/

   for (i=0; i<N; i++)
      for (j=0; j<N; j++)
	 grafo[i][j] = 0; 

 /*
  *  Se lee el numero de colonias
 */  

   if (fgets(line, sizeof(line),  input) == NULL) {//lee de linea, el tamaÒo de linea si es NULL, no existe el archivo
      printf("Error al leer archivo\n");
      exit(0);
   }
   
   sscanf(line, "%d", &n);//lee de linea, lo transforma a numero y lo guarda en direccion &n ( ATOI similar)
   if (n > N) {
      printf("Error: numero de colonias demasiado grande\n");
      return;
   }
   printf("input:\n");
   printf("%d\n", n);
   
 /*
  *   Se leen las rutas que unen a las colonias
 */
 
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
   Se almacenan las rutas en la matriz de adyacencias
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
   for (i=0; i<n; i++) {
      for (j=0; j<n; j++) {
	 printf("%d\t", grafo[i][j]);
      }
      printf("\n");
   }
}
