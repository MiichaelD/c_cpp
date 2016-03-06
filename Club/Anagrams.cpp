#include <stdio.h>
#include <memory.h>
#include <string.h>

/**
 * This program check if 2 phrases (may contain spaces BUT NOT PUNCTUATION MARKS)
 * are Anagrams, which means that both phrases use the same letters in the same
 * ammount.
 * 
 * programmer:          Michael Duarte
 * 
 * date:                October 3rd, 2013 * 
 * 
 */

int main(){

    char linea[512], character;
    int chars[256], i, len;
    memset(linea, 0 , sizeof(linea));
    memset(chars, 0 , sizeof(chars));
    
    
    printf("Please introduce the 1st phrase: \n");
    if (gets(linea) != NULL){
        i=-1;
        len = strlen(linea);
        while(++i<len){
            character = (int)linea[i];
            
            if(character == ' ')
                continue;
                
            chars[character]++;       
        }
    }
    
    printf("Introduce the 2nd phrase: \n");
    memset(linea, 0 , sizeof(linea));
    if (gets(linea) != NULL){
        i=-1;
        len = strlen(linea);
        while(++i<len){
            character = (int)linea[i];
            
            if(character == ' ')
                continue;
                
            chars[character]--;       
        }
    }
    
    i = -1 ;
    while(++i < 256){
        if( chars[i] ){
            printf("The phrases are not Anagrams from each other.\n");
            i = 0;
            break;
        }
            
    }
    
    if(i == 256)
        printf("The phrases ARE Anagrams from each other.\n");
}