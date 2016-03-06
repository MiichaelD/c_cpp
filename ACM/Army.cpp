/*For example the second case in the problem:
S=10 B=4   ===> * 1 2 3 4 5 6 7 8 9 10 *
2 5        ===> * 1(2 3 4 5)6 7 8 9 10 *
                * 1<       >6 7 8 9 10 *
6 9        ===> * 1        (6 7 8 9)10 *
                * 1<               >10 *
1 1        ===> *(1)                10 *
                *<                 >10 *
10 10      ===> *                  (10)*
                *<                    >*

This is my implementation and you can see in live archive's statistic (Run Time:0.104).

 * 
 * @author: vudduu - Edwin Guzman
 * @problem: Problem A - Army Buddies
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

int vleft[100001], vright[100001];

int main(){
   int n, x, y, m;
   scanf("%d %d", &n, &m);
   while(n){
      FOR(i, 1, n+1){
         vleft[i] = i-1;
         vright[i] = i+1;
      }
      F(i, m){
         scanf("%d %d", &x, &y);
         if(vleft[x] == 0) printf("* ");
         else printf("%d ", vleft[x]);
         if(vright[y] == n+1) printf("*\n");
         else printf("%d\n", vright[y]);
         vleft[ vright[y]] = vleft[x];
         vright[ vleft[x]] = vright[y];
      }
      printf("-\n");
      scanf("%d %d", &n, &m);
   }
}
