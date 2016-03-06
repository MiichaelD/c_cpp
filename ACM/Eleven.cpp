/*
	given a 10 power to 100 number, print all the possible permutations
	that are divisible by 11. As the possible answers can be very large,
	you are requiered to output the remainder of dividing it by 10 power
	to 9, + 7 (1000000007)

*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>



int main () {
    char arr[128];
    memset(arr,0,sizeof(arr));
    scanf("%s",arr);
    
    //here should be the permutation part AND hash them to prevent of being
    //repeated and processed more than once
    
    
    //check divisibility by 11 of every permutation
    int i=0,sum1=0,sum2=0,len = strlen(arr);
    for(;i<len;i++){
      if(i%2)sum2+=arr[i]='0';
      else sum1+=arr[i]='0';
    }
    
    if(sum1 - sum2 % 11)
      printf("true\n");
    return 0;
}
