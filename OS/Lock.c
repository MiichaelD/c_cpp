/*
Programa:		CodeLock.c
Fuente:			ACM ICPC 2009 – Latin American Regionals - 4474

Objetivo: 			El candado usa un sistema de codigo, el candado contiene una secuencia de ruedas.
				cada rueda tiene las 26 letras del alfabeto, trata de acomodarlas para qe queden como
				es especificada en la linea de entrada (los candados empiezan con todos las ruedas
				apuntando a 'a').
				
nota:			Descomenta la definicion de D, para ir imprimiendo informacion relevante a la ejecucion

Input:
abcxyz
abcdefghijklmnopqrstuvwxyz
aaaaaaaaa
zzzzzzzzz
zzzzbzzzz
adfjklnp
azywvm
pnlkjfda
abcxyzbc
*

Output:
5
25
0
1
3
15
14
23
7

				
				
				
Autor:			Michael Duarte
Fecha:			Septiembre 2012
*/
#define M 1000
//#define D //DEBUGING DEFINE

#include <stdio.h>
#include <math.h>

//variables
char pass[M];

//functions
double lockDecoder(char[]);
int decoder(char pass[], char cad[], int directions[], int letters);
char getNext(char, int);
void getDirections(int[], char[], char[],int);
int maxMoves(int[],int,int,char);


int main(){
	scanf("%s",pass);
	while(pass[0]!='*'){
		printf("%.0f\n",lockDecoder(pass));
		scanf("%s",pass);
	}
	return 0;
}

double lockDecoder(char in[]){
	double moves;
	int letters,i;
	//check how many letters there are on the array
	for(i=0;i<M;i++)
		if(in[i]==0){
			letters=i;
			break;
		}
	#ifdef D
		printf("Letters; %d\n",letters);
	#endif
	
	//create a new char array to be compare with password
	char cad[letters];
	int directions[letters];
	
	//fill the array with characters 'a' 
	for(i=0;i<letters;i++)
		cad[i]='a';
	cad[letters]=0; // I don't know why, if this isn't done, a last unknown char will be pushed back in cad
	//decoder
	#ifdef D
		printf("cadena: \t%s \npasswd: \t%s \nIguales?\t%d\n",cad,pass,strcmp(cad,pass));
	#endif
	moves=decoder(pass,cad,directions,letters);
	#ifdef D
		printf("Finished in %.0f moves\n",moves);
	#endif
	return moves;
}


int decoder(char pass[], char cad[], int directions[], int letters){
	char comp;
	int moves=0,i,findex,lindex,max;
	while(strcmp(cad,pass) != 0){				//mientras que sean diferentes ( diferentes a 0 )
		getDirections(directions,cad, pass, letters);
		
		for(i=0;i<letters;i++){						//get Consecutive order letters;
			if(directions[i]	!=0){				//if different letters than password found.
				findex=i;
				
				if(directions[i]>0){					//if found is positive
					comp='+';
					while(directions[i]>0 && i!=letters)
						i++;
				}
				else{										//if found is negative
					comp='-';
					while(directions[i]<0 && i!=letters)
						i++;
				}
				lindex=i;
				
				break;
			}
		}
		
		#ifdef D
			printf("this group indexes:\tstarting: %d\t ending: %d\n",findex,lindex);		
		#endif
																				
																	
														///increment/decrement consecutive order letters
		max=maxMoves(directions,findex,lindex,comp);
		moves+=abs(max);
		for(i=findex;i<lindex;i++){
			#ifdef D
				printf("before %c,  moving upto: %d, after: %c\n",cad[i],max,pass[i]);
			#endif
			cad[i]=pass[i];
		}
		
		#ifdef D
			printf("cadena:\t\t%s\npasswd:\t\t%s\nMoves:\t\t%d\n",cad,pass,moves);
		#endif
	}
	return moves;
}

int maxMoves(int dir[],int findex, int lindex,char dire){
	int moves=0,	i;
	if(dire=='+'){
		for(i=findex;i<lindex;i++)
			if(dir[i]>moves)
				moves=dir[i];
	}
	else{
		for(i=findex;i<lindex;i++)
			if(dir[i]<moves)
				moves=dir[i];
	}
	return moves;
}


void getDirections(int dir[],char cad[], char pass[], int len){
	char curC,	lastC;
	int i,	difC,	difL,	steps, steps2;// index, steps from curC to Pass
	#ifdef D
		printf("Getting #-Directions: \t");
	#endif
	for(i=0;i<len;i++){
		if(pass[i]==cad[i]){				//if equal, direction =0, so no movement required, steps  store abs value 
			dir[i]=0;
			#ifdef D
				printf("%d, ",dir[i]);
			#endif
			continue;
		}
		curC=cad[i];
		
		difC=pass[i]-curC;				//calculate the steps between the letters
		
		if (difC == 13){
			int x=i;
			while(x<len){				//move until letter != 'n' or end the password length
				x++;
				if(pass[x]!='n'){		
					if((pass[x]-cad[x])>13){ //if next leter is more than 13 steps away, go negative direction
						dir[i]=-13;
						steps=13;
					}	
					else{						//else get positive direction
						steps=13;
						dir[i]=13;
					}
					
					x=0;
					break;
				}
			}
			if(x !=0 ){ 			//if last letter is 'n' then it doesn't matter the direction, Taking positive direciton
				steps=difC;
				dir[i]=difC;
			}
				
		}
		else if(difC>13){
			dir[i]=difC-26;
			steps=-dir[i];
		}
		else{
			steps=difC;
			dir[i]=difC;
		}
			
		if(i>0){							//check if its closer from the last letter to the password letter
			lastC=cad[i-1];
			difL=pass[i]-lastC;
			if(difL>0){ 						//clockwise direction
				if(difL>13){
					if(steps>26-difL)	{		//if they are less steps, update dir array;
						dir[i]=difL-26;
						cad[i]=cad[i-1];
					}
				}
				else
					if(steps>difL){				//if they are less steps, update dir array;
						dir[i]=difL;
						cad[i]=cad[i-1];
					}
			}
			else{								//anticlockwise direction
				steps2=-difL;
				if(steps2>13){				//if there are less steps,update dir array;
					if(steps>difL+26){
						dir[i]=difL+26;
						cad[i]=cad[i-1];
					}
				}
				else
					if(steps>steps2)	{	//if there are less steps,update dir array;
						dir[i]=difL;
						cad[i]=cad[i-1];
					}
			}
		}

		#ifdef D
			printf("%d, ",dir[i]);
		#endif
	}
	#ifdef D
		printf("\n");
	#endif
}