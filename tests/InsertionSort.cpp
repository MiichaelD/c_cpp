#include <stdio.h>
#include <cstdlib>
#include <iostream>

int vec[10];
void insertionSort(int[],int);
void insertionSort2(int[],int);
main (){
     int i,size;
     size=10;
     printf("Vector Desordenado:\n");
     for(i=0;i<size;i++){
           vec[i]= rand()%1000;
           printf("%d\n",vec[i]);
     }
     insertionSort2(vec,size);
     printf("\n\nVector Ordenado \tInsertion Sort :\n");
     for(i=0;i<size;i++){
           printf("%d\n",vec[i]);
     }
     printf("Presione <Enter> para salir");
     getchar();
}

void insertionSort(int array[], int size){
   int i, a, key;
 
   for (i=1; i < size; i++){
      key = array[i];
      a=i-1;
      while (a>=0 && array[a]>key){
         array[a + 1] = array[a];
         a--;
      }
      array[a+1] = key;
   }
}



void insertionSort2(int array[], int size){
   int i, a, key;
 
   for (i=1; i < size; i++){
      key = array[i];
      for (a=i-1;    a>=0 && array[a]>key   ; a--){
         array[a + 1] = array[a];
      }
      array[a+1] = key;
   }
}

