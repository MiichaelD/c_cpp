/*
Programa:		CodeLock.c
Fuente:			ACM ICPC 2009 – Latin American Regionals - 4474

Objetivo: 			El candado usa un sistema de codigo, el candado contiene una secuencia de ruedas.
				cada rueda tiene las 26 letras del alfabeto, trata de acomodarlas para qe queden como
				es especificada en la linea de entrada (los candados empiezan con todos las ruedas
				apuntando a 'a').

Input:
abcxyz
abcdefghijklmnopqrstuvwxyz
aaaaaaaaa
zzzzzzzzz
zzzzbzzzz
*

Output:
5
25
0
1
3
				
				
				
Autor:			Michael Duarte
Fecha:			Septiembre 2012
*/
#define M 1000
#define D 1//debug

#include <stdio.h>


//variables
char pass[M];


//functions
double lockDecoder(char[]);
char getNext(char, char);
void getDirections(char[], char[], char[],int);

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
	int letters,i,findex,lindex;
	//check how many letters there are on the array
	if(D)printf("Letters: ");
	for(i=0;i<M;i++)
		if(in[i]==0){
			letters=i;
			break;
		}
	if(D)printf("%d\n",letters);
	
	//create a new char array to be compare with password
	char cad[letters];
	char	directions[letters];
	char comp;
	
	//fill the array with characters 'a' 
	for(i=0;i<letters;i++)
		cad[i]='a';
	cad[letters]=0; // I don't know why, if this isn't done, a last unknown char will be pushed back in cad
	//decoder
	if(D){
		printf("cadena: \t%s \npasswd: \t%s \nIguales?\t%d\n",cad,pass,strcmp(cad,pass));
	}
	moves=0;
	while(strcmp(cad,pass) != 0)//mientras que sean diferentes ( diferentes a 0 )
	{
		getDirections(directions,cad, pass, letters);
		comp='=';
		moves++;
		//get Consecutive order letters;
		for(i=0;i<letters;i++){
			if(directions[i]	!=	comp){
				findex=i;
				comp=directions[i];
				if(D)printf("diff sign: %c @ %d\t ",directions[i],i);
				if(i==letters-1){
					lindex=i+1;
				}
				else{
					while(directions[i] == comp || directions[i] == '.'){
						i++;
					}
					lindex=i;
				}
				if(D)printf("until: %d \n",lindex);
				
				break;
			}
		}
		if(D)printf("\t\tcomp = %c\tfindex: %d\t lindex: %d\n",comp,findex,lindex);
		/////////////////////////////////////////////
		//increment/decrement consecutive order letters
		if(comp!='=')
		for(i=findex;i<lindex;i++){
			if(D)printf("before %c, ",cad[i]);
			cad[i]=getNext(cad[i],comp);
			if(D)printf("after %c\n",cad[i]);
		}
		
		if(D){
			printf("cadena:\t\t%s\npasswd:\t\t%s\nIguales?\t\t%d\n",cad,pass,strcmp(cad,pass));
		}
	}
	if(D)printf("Finished in %.0f moves\n",moves);
	return moves;
}

char getNext(char c,char direction){
	switch(direction){
	case '+':if(c=='z')
					return 'a';
				else
					return c+1;
	case '-':	if(c=='a')
					return 'z';
				else
					return c-1;
	default:	
				if(D)printf("char: %c; \tdirection unknown: %c\n",c,direction);
				break;
	}
	return c;
}

void getDirections(char dir[],char cad[], char pass[], int len){
	char cU,cD;
	int i;
	if(D)printf("getting Directions: \t");
	for(i=0;i<len;i++){
		if(pass[i]==cad[i]){
			dir[i]='=';
			if(D)printf("%c",dir[i]);
			continue;
		}
		cU=cad[i];
		cD=cad[i];
		while(cU!=pass[i] && cD!=pass[i]){
			cU=getNext(cU,'+');
			cD=getNext(cD,'-');
			if(pass[i]==cU){
				if(cU==cD)
					dir[i]='.';
				else
					dir[i]='+';
			}else if(pass[i]==cD){
				if(cU==cD)
					dir[i]='.';
				else 
					dir[i]='-';
			}
		}
		if(D)printf("%c",dir[i]);
	}
	if(D)printf("\n");
}