/* 
 * @author: vudduu - Edwin Guzman
 * @problem: Problem K - King's Poker
 * @contest: ACM ICPC Latin America Regional 2011
 */
#include <iostream>
#include <sstream>
#include <utility>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <cmath>
#include <functional>
#include <algorithm>
#include <numeric>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <list>
#include <map>
#include <set>
#include <stdio.h>
#include <string.h>
using namespace std;

#define FOR(i,a,b)  for(int i=(a),_##i=(b);i<_##i;++i)
#define F(i,a)      FOR(i,0,a)
#define ALL(x)      x.begin(),x.end()
#define PB          push_back
#define MP          make_pair
#define S           size()
typedef long long   LL;

int it;
char ch[30];

int main(){
  int v[3];
  scanf("%d %d %d", &v[0], &v[1], &v[2]);
  while(v[0]){
    sort(v, v+3);
    if(v[0] == v[1] && v[0] == v[2]){
      if(v[0] == 13) printf("*\n");
      else printf("%d %d %d\n", v[0]+1, v[0]+1, v[0]+1);
    }
    else if(v[0] == v[1]){
      if(v[2] == 13) printf("1 %d %d\n", v[0]+1, v[0]+1);
      else printf("%d %d %d\n", v[0], v[0], v[2]+1);
    }
    else if(v[1] == v[2]){
      if(v[0] == v[1]-1){
        if(v[1] == 13) printf("1 1 1\n");
        else printf("%d %d %d\n", v[2], v[2], v[0]+2);
      }
      else printf("%d %d %d\n", v[0]+1, v[2], v[2]);
    }
    else printf("1 1 2\n");
    scanf("%d %d %d", &v[0], &v[1], &v[2]);
  }
}
