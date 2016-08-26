/*
Programa:			hashing.c

Descripcion:			Almacenar en un arreglo 600 numeros aleatorios [0 - 2000] utilizando hashing para
					acceder a los valores de manera directa, en caso de colision se usan listas para no perder
					ningun valor. Despues se puede buscar algun numero aplicandole la misma funcion hash, para
					accederlo, si se encuentra, se imprimira en donde se encuentra localizado.
					Introducir 0 para terminar busquedas.
					
Programador:		Michael Duarte

Fecha 				Octubre 2012
*/


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <memory.h>


#define arrayLength 700

typedef struct slot_S{	//estructura Slot
	int key;
	struct slot_S *next;
} slot;

slot *vec[arrayLength]; // linkedlist of slots

int hashCode(int key,int arrLength){	//funcion para generar indice
	return key%(arrLength-1);			// primo cercano a 2000/3 y lejano a potencia de 2
}


main()
{
	int i, index, ran,colisiones=0;
	//memset(vec, NULL, sizeof(slot*));											// llenamos el arreglo en 0;
	srand ( time(NULL) );
	
	
	for(i=0; i<arrayLength; i++){ 												//generamos 600 numeros
		ran = rand() % 2001; 													// del 0 al 2000
		index =hashCode(ran,arrayLength);
		if (vec[index] != NULL){
			colisiones++;
			slot *aux = vec[index];
			while(aux->next != NULL){											//recorremos lista hasta la ultima
				aux=aux->next;
			}
			aux->next=(slot *) malloc (sizeof(slot));							//agregamos nuevo elemento a la lista
			aux->next->key = ran;												//inicializamos su valor llave
			
		}
		else{
			vec[index] = (slot * ) malloc (sizeof(slot));
			vec[index]->key = ran;			
		}
		
	}

	printf("Imprimimos Arreglo Hash:\n");
	int nums=0, colisiones2=colisiones;
	for(i=0; i<arrayLength; i++){ 												//mostramos 600 numeros
		if(vec[i] != NULL){
			++nums;
			slot *aux=vec[i];
			printf("%d\t",aux->key);
			
			if((1+nums)%20 ==0)
				printf("\n");
			while(aux->next != NULL){
				colisiones2--;
				aux = aux->next;
				printf("%d\t",aux->key);
				nums++;
				if((1+nums)%20 ==0)
				printf("\n");
			}
			
		}
	}
	printf("\nColisiones: %d, \tPorcentaje: %.2f, \tColisiones Perdidas: %d\n\n",colisiones,((double)colisiones/arrayLength)*100,colisiones2);



	do{
		printf ("\nIngrese numero a buscar: ");
		scanf("%d",&i);
		index=hashCode(i,arrayLength);
		if(vec[index] != NULL){													// Slot no vacio
			if(vec[index] -> key == i){											// Key estaba en el primer slot del indice
				printf("Se encontro el numero %d en la posicion (Index): %d\n",i,hashCode(i,arrayLength));
			}
			else{																//buscamos key en la lista de slots
				int colision=1;												
				slot *aux=vec[index];
				while (aux->next != NULL){										//recorremos lista
					aux = aux->next;
					if(aux->key == i){											//comparamos si es la misma llave
						printf("Se encontro el numero %d en la posicion (Index): %d, colision #: %d\n",i,hashCode(i,arrayLength),colision);
						colision=0;
					}
					++colision;
				}
				if(colision)
					printf("Numero no capturado\n");
			}
		}
		else{
			printf("Numero no capturado - Slot vacio\n");
		}
	}while(i != 0);

}


