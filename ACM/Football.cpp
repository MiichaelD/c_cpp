/*
	example of SORT
	
	Given a Number of Matches N, an amount of buyable goals G,
	we will get N lines with 2 Integers, the first 'S'represents
	our Scored Goals and  and the second 'R'indicates the other 
	Team's goals.
	
	for every won match we get 3 points, ties give us 1 point, 
	we have to get the max amount of points.

*/

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>
using namespace std;

bool ascending (int i,int j) { return (i<j); }
bool descending (int i,int j) { return (i>j); }

struct myclass {
  bool operator() (int i,int j) { return (i<j);}
} myobject;

void printVector(vector<int> &myvector){
  unsigned int i= 0;
  printf("\t[");
  for (; i<myvector.size() ; i++)
    printf("%d ", myvector[i]);
  printf("]\n");  
}


int main () {
    int N, G, S, R, res = 0, buyWin, buyTie;
    vector<int> vec;
    scanf("%d %d", &N,&G);
    while(N--){
      scanf("%d %d", &S,&R);
      if (S>R)
	res+=3;
      else if(S==R){
	if(G > 0){
	  G--;
	  res+=3;
	}
	else
	  res++;
      }
      else {
	vec.push_back(R-S);
      }
    }
   
    if(G){
      sort (vec.begin(), vec.end(), descending);
      //printVector(vec);
      
      while(!vec.empty() && G){
	buyTie = vec.back();
	vec.pop_back();
	buyWin = buyTie+1;
	if(G>=buyWin){
	  //printf("\tBought a Win that costs %d with my G: %d\n",buyWin,G); 
	  G-=buyWin;
	  res+=3;
	}
	else if(G == buyTie){
	  //printf("\tBought a Tie that costs %d with my G: %d\n",buyTie,G); 
	  G-=buyTie;
	  res++;
	}
	else
	  break;	
      }
    }
    printf("%d\n",res);
    //system("pause");
    return 0;
}
