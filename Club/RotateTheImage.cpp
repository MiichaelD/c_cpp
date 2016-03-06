#include <stdio.h>
#include <memory.h>
#include <string.h>

/**
 * This program rotate an image (represented by an NxN matrix, each pixel is 4
 * bytes long) 90 degrees. 
 * 
 * programmer:          Michael Duarte
 * 
 * date:                October 3rd, 2013 * 
 */
 
 


void printMat(int **matrix, int N){
	int i,j;
	printf("\n");
    for(i=0;i<N;i++){
        for(j=0;j<N;j++){
            printf("%d\t",matrix[i][j]);
        }
        printf("\n");
    }
}

 
 /**
  * This function takes a 2D array and rotates it 90 degrees anti-clockwise
  * the array's dimension is specified in the second parameter  */
void rotate90deg(int **mat, int dimension){
	if(dimension <2)
		return;

	int aux1,i,j, dimeX = dimension, maxN = dimension-1;

    if(dimension > 2)
		dimeX = (int)dimension/2;
	//printf("iteraciones = %d\n",dimeX);
	
    for(i=0;i<dimeX;i++)
	{
	  for(j=i;j<maxN-i;j++){
            aux1 = mat[i][j];
			mat[i][j] = mat[j][maxN-i];
			mat[j][maxN-i] = mat[maxN-i][maxN-j];
			mat[maxN-i][maxN-j] = mat[maxN-j][i];
			mat[maxN-j][i] = aux1;
			//printMat(mat,dimension);
        }
    }
}
 
 
int main(){

    int **matrix;
    int i,j,N;
    printf("Input the dimension of the picture; N = \t");
    scanf("%d",&N);
    
    
    //Init and Print the image
    matrix =  new int*[N];
    for(i=0;i<N;i++)
	{
        matrix[i] = new int[N];
        for(j=0;j<N;j++){
            matrix[i][j]=(i*N)+(j+1);
            printf("%d\t",matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    
    //rotate and print 
    rotate90deg(matrix,N);
    
    printf("\nFinished Rotation:\n");
	printMat(matrix,N);
}