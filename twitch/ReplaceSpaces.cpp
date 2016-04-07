#include <iostream>

/* 
  Create a function {void ReplaceSpaces(char *buffer);}  that replaces spaces of a string with "%20"
  without using any other helper function or allocating new memory.
  Keep in mind that the buffer is big enough to hold the resulting string.

  i. e. "Hello World Twitch"   ===> "Hello%20World%20Twitch"
*/

void ReplaceSpaces(char* buffer){  
  char *aux = buffer;
  char *end;
  int spaces = 0;
  // find the end of the string;
  while (aux && *aux != '\0'){
    if (*aux == ' ') ++spaces;
    ++aux;
  }
  //if the string is big enoug we are going to stop iterating when
  //we find the null character terminator.
  end = (aux+(spaces*2));
  
  // aux = buffer; // aux will start from the front;
  while (aux != buffer || spaces){
    if (*aux == ' '){
      *end = '0';
      *(--end) = '2';
      *(--end) = '%';
      --spaces;
    } else {
      *end = *aux;
    }
    
    --end;
    --aux;
  }
}

int main(){
  char str[100] = "Hello World Twitch";
  printf ("%s\n",str);
  ReplaceSpaces(str);
  printf ("%s\n",str);
  
}