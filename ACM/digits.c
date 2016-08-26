#include <stdlib.h>
#include <stdio.h>
#include <string.h>


char string[50];
int i,j,num1,num2;

void main(){
     while(1){
        int cont[]={0,0,0,0,0,0,0,0,0,0};
        scanf("%d",&num1);
        scanf("%d",&num2);
        if(num1==0 && num2==0)
            break;
        for(i=num1;i<=num2;i++){ 
           sprintf(string, "%d",i);
           for(j=0;j<strlen(string);j++){
                cont[(string[j]-'0')]++;} 
        }
        for(i=0;i<10;i++)
             printf("%d ",cont[i]);
     }
}
