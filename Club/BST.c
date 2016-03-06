/*
 Programa:		BST.c
 
 Descripcion:		2 ) Arboles Binarios en C y Java                           
			- Generar 20 numeros aleatorios de [0-100] almacenarlos en BST
			- Imprimir numeros ordenados ascendentemento (menor a mayor).
			- Imprimir valores Maximos y Minimos
			- 3 numeros aleatorios [0-100] y buscar en el arbol. 

Nota:			Los arboles brindan una rapida forma de ordenar y buscar datos.
			Existen 3 variantes de recorrido de arboles, dependiendo de lo
			que se necesite.
			
 Programador:		Michael Duarte
 
 Fecha:			Octubre 2012
 
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <memory.h>

typedef struct arbol{
  struct arbol *padre;
  struct arbol *izq;
  struct arbol *der;
  int valor;
} tree;

void insertar(tree *,int);
void buscar(int);
tree * nuevoNodo(tree *,int);
void recorridoInOrder(tree*);
void recorridoPreOrder(tree*);
void recorridoPostOrder(tree*);
tree * busquedaRec(tree*,int);
tree * busquedaCic(tree*,int);
tree * MinVal(tree *);
tree * MaxVal(tree *);

int main(int argc,char *argv[]){
  tree *Root= NULL;				//inicializamos raiz de arbol
  srand(time(NULL));				//semilla de numeros aleatorios
  int i,ran;
  
  printf("Valores a agregar: \n");		//llenamos arbol con 20 num [0 - 100]
  for (i =0 ;i<20;i++){
    ran = rand() % 101;
    printf("%d ",ran);
    if(!Root)
      Root=nuevoNodo(NULL,ran);
    else
      insertar(Root,ran);
  }
  printf("\n\n");
  
  printf("Numeros Ordenados: \n");
  recorridoInOrder(Root);
  printf("\n\n");
  
  printf("Minimo: %d,\t Maximo: %d\n\n",MinVal(Root)->valor,MaxVal(Root)->valor);
  
  printf("Busamos los siguientes numeros: \n");
  for(i=0;i<3;i++){
    ran=rand()%101;
    if(busquedaCic(Root,ran))
      printf("Numero %d fue encontrado\n",ran);
    else
      printf("Numero %d no fue encontrado\n",ran);
  }
  return 0;
}

void insertar(tree *raiz, int nVal){
  {
    tree *aux = raiz;
    while(aux != NULL){
      if (nVal < (aux->valor)){
      	if(!aux->izq)
      	  break;
      	aux = (aux->izq);
      }else{
      	if(!aux->der)
      	  break;
      	aux = (aux->der);
      }
    }
    if (nVal < aux->valor){
      //printf("Se agrego nodo a izq de %d\n",aux->valor);
      aux->izq=nuevoNodo(aux,nVal);
    }else{
      //printf("Se agrego nodo a der de %d\n",aux->valor);
      aux->der=nuevoNodo(aux,nVal);
    }
  }
}

tree *nuevoNodo(tree *nPadre, int nVal){
  tree *aux = (tree *) malloc (sizeof(tree));
  aux->valor=nVal;
  aux->padre=nPadre;
  aux->izq= NULL;
  aux->der=NULL;
  return aux;
}

void recorridoInOrder(tree *raiz){
  if(raiz){
    recorridoInOrder(raiz->izq);
    printf("%d ",raiz->valor);
    recorridoInOrder(raiz->der);
  }
}

void recorridoPreOrder(tree *raiz){
  if(raiz){
    printf("%d ",raiz->valor);
    recorridoPreOrder(raiz->izq);
    recorridoPreOrder(raiz->der);
  }
}

void recorridoPostOrder(tree *raiz){
  if(raiz){
    recorridoPostOrder(raiz->izq);
    recorridoPostOrder(raiz->der);
    printf("%d ",raiz->valor);
  }  
}

tree *busquedaRec(tree* raiz,int nVal){
  if(!raiz || nVal==raiz->valor)
    return raiz;
  
  if(nVal<raiz->valor)
    return busquedaRec(raiz->izq,nVal);
  
  return busquedaRec(raiz->der,nVal);
}

tree *busquedaCic(tree* raiz,int nVal){
  tree *aux=raiz;
  while(aux && aux->valor!=nVal) {
    if(nVal < aux->valor)
	     aux=aux->izq;
    else
	     aux=aux->der;
  }
  return aux;
}

tree * MaxVal(tree * raiz){
  tree *aux=raiz;
  while(aux->der){
    aux=aux->der;
  }
  return aux;
}

tree * MinVal(tree * raiz){
  tree *aux=raiz;
  while(aux->izq){
    aux=aux->izq;
  }
  return aux;
}

