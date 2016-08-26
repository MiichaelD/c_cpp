#include <stdio.h>
#include <math.h>

/**

example of escape codes, 

\x1b[30m    -> color 30 - 37.

\x1b[30;1m  -> color 30 - 37, using the bold color

\x1b[0m     -> restart to previous color ( cancel last color used )

\b          -> move cursor 1 space back.

*/


int intLength(int n){
	if( n == 0 )
		return 1;
		
	return floor(log10(abs(n)))+1;
}

main(){
	int i = 0, j, len, top;
	printf("Insert max numer:");
	scanf("%d",&top);
	printf("START\ncurrent number: ");
	for(;i<=top;i++){
		printf("\x1b[3%d;1m",i%8);
		printf("%d",i);
		
		//for(len=0;len<2000;len++)printf("");
		
		len = intLength(i);
		
		for(j=0;j<len;j++){
			printf("\b");
		}
		printf("\x1b[0m");
	}
	printf("\x1b[0m");
	printf("\nDONE\n");
}

