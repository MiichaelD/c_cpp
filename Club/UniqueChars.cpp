#include <stdio.h>
#include <memory.h>
#include <string.h>

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
            
            if(character == ' ')
                continue;
            
            if ( chars[character]){
                printf("This string has duplicate characters (%c) at pos: %d & %d\n",character, chars[character], i+1);
                i = -1;
                break;
            }
            chars[character] = i+1;       
        }
        if ( i != -1 ){
            printf("all characters in the input string are unique\n");
        }
    }
}