/*
 * Programa:  digits.c
 * Objetivo:  Lee dos numeros a y b (0 <= a <= b) e imprime diez digitos. Cada digito representa un numero del 0 al 9 (en ese orden).
 *            Cada digito impreso representa la cantidad de veces que ese digito es utilizado para escribir todos los numeros entre a y
 *            b inclusive
 * Autor:     Arnoldo Diaz Ramirez
 * 
 */


#include <stdio.h>

main() {
   
   int a,b;
   int digitos[10];
   int i, res, coc, temp;
   
   // se inicializa arreglo en ceros
   for (i=0; i<10; i++)
      digitos[i] = 0;
   
   // se solicitan a y b, validando que (0 <= a <= b)
   do {
      printf("Escribe un numero: ");
      scanf("%d", &a);
      printf("Escribe otro numero: ");
      scanf("%d", &b);
   } while ( (a > b) || (a < 0) );
   
   
   // se calcula la cantidad de veces que cada digito es utilizado para escribir los numeros entre a y b, inclusive
   for (i=a; i<=b; i++) {
      temp = i;
      do {
	 res = temp % 10;
	 coc = temp / 10;
	 digitos[res]++;
	 temp = coc;
      } while (coc != 0);
   }
   
   // se imprimen los resultados
   for (i=0; i<10; i++)
      printf("%d ", digitos[i]);
   printf("\n");
   
}