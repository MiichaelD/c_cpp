#include <stdio.h>
  
   char line[80];  /* Input line */
   int x, y;       /* variables */
   float res;

   main(){
      
     while (fgets(line, sizeof(line),  stdin) != EOF) { /* read a line from keyboard */
        sscanf(line, "%d%d", &x, &y);
		res=((float)x)/y;
		printf("%.2f\n",res);
      }
   }