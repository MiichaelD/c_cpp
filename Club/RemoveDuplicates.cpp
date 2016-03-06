#include <stdio.h>
#include <memory.h>
#include <string.h>

/**
 * This program removes the duplicated characters within a string and prints the
 * resultant string.
 * 
 * programmer:          Michael Duarte
 * 
 * date:                October 3rd, 2013 * 
 */
int main(){

    char linea[512], character;
    int chars[256], i, len;
    memset(linea, 0 , sizeof(linea));
    memset(chars, 0 , sizeof(chars));
    
    if (gets(linea) != NULL){
        i=-1;
        len = strlen(linea);
        while(++i<len){
            character = (int)linea[i];
            
            if(character == ' '){
                printf(" ");
                continue;
            }
            
            if ( !chars[character] ){
                chars[character] = i+1;  
                printf("%c",character);
            }
        }
        printf("\n");
        
    }
}