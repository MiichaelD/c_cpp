#include <stdio.h>

main(){
       int x;
       int *ptr;

       x=10;
       printf("x = %d\n",x);

       ptr=&x;
       printf("ptr = %d\n",*ptr);

       *ptr=13;
       printf("x = %d",x);

       scanf("%d");       
}
