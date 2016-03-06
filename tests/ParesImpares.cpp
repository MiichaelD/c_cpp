#include <stdio.h>
void capturar();
int contarPares(int[]);
int vec[10];

main(){

       capturar();
       int n=contarPares(vec);
       printf("Numeros pares: %d\nNumeros Impares: %d\n",n,(10-n)); 
       }


void capturar(){
          for (int i=0;i<10;i++){
          printf("Inserta un numero para el valor %d: ",(i+1));
                     scanf("%d",&vec[i]);
          }
     }

int contarPares(int vec2[]){
     int n1=0;
     for (int i=0;i<10;i++){
          if(vec2[i]%2==0)
                ++n1;
     }
     return n1;     
     }
