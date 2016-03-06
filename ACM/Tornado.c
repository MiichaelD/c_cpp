#include <stdio.h>
#include <stdlib.h>

int main(){
	int n,i,posts;
	char c;
	char line[2000];
	while(1){
		 if (fgets(line, sizeof(line),  stdin) == NULL)
			break;
		sscanf(line,"%d",&n);
		posts=0;
		for (i=0;i<n;i++){
			scanf("%c%c",&c);
			if(c == '0'){
				if(i<n-1){
					i++;
					scanf("%c%c",&c);
					
					if(c=='0')
						posts++;
				}
				else
					break;
			}
		}
		//fgets(line, sizeof(line),  stdin);
		printf("%d-%s\n",posts,line);
	}
}

/*
 * cuenta ceros seguidos (cada 2 se incrementa el contador)
10
1 0 1 0 1 0 1 0 0 0
10
1 0 0 1 0 0 0 1 0 1


*/