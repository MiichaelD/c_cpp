#include <stdio.h>
#include <conio.h>
#include <ctype.h>

main(){
  char c1,c2,c3,c4;
  
  // declara una cadena de longitud 20 como máximo. 
  char a[20];
  // declara una cadena de longitud 10 como máximo.
  // el contenido es la cadena “hola”, x[4] = ‘\0’.
  char x[10] = "hola";
  // declara una cadena de 4 caracteres mas \0
  char *m = "que tal";
  // declara una cadena con longitud variable
  char s[] = {'B','i','e','n','v','e','n','i','d','o','\0'};
  // declara una cadena con longitud variable
  char nom[] = "juan perez";
  puts(x);
  puts(m);
  puts(s);
  puts(nom);
  printf("x es \"%s\", ",x);
  printf("m es \"%s\", ",m);
  printf("s es \"%s\", ",s);
  printf("nom es \"%s\" ",nom);
  
  
  
  
  
  printf("teclee un caracter: ");
  c1 = getch();
  fflush(stdin);
  if(isdigit(c1))
    printf("%c es un digito\n",c1);
  else
    printf("%c NO es un digito\n",c1);
  printf("tecle un caracter: ");
  c2 = getch();
  fflush(stdin);
  if(isalpha(c2))
    printf("%c es una letra\n",c2);
  else
    printf("%c NO es una letra\n",c2);
  
 printf("tecle un caracter: ");
  c3 = getch();
  fflush(stdin);
  if(isupper(c3)){
    printf("%c es una letra mayuscula\n",c3);
    printf("La minuscula de %c es %c\n\n",c3,tolower(c3));
  }
  if(islower(c3)){
    printf("%c es una letra minuscula\n",c2);
    printf("La mayuscula de %c es %c\n\n",c3,toupper(c3));
  }
  
  
  
  
  getch();
}
