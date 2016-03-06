/*This problem is a case of RMQ or Interval Trees.
For join two ranges:




With that formula we can pre-calculate some intervals and the intervals can join for solve queries, this my implementation.

 
 * @author: vudduu - Edwin Guzman
 * @problem: Problem J - Jupiter Attacks!
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

LL T[400000], MOD, B[100005];

void insert(int i, int v, int it, int ini, int end){
   if(ini == end){
      T[it] = v % MOD;
      return;
   }
   int le = it<<1, ri = le+1, mid = (ini+end)>>1;
   if(i <= mid) insert(i, v, le, ini, mid);
   else insert(i, v, ri, mid+1, end);
   T[it] = ((( T[le]*B[end-mid] ) % MOD) + T[ri]) % MOD;
}

LL functionH(int x, int y, int it, int ini, int end){
   if(x == ini && y == end) return T[it];
   int le = it<<1, ri = le+1, mid = (ini+end)>>1;
   if(y <= mid) return functionH(x, y, le, ini, mid);
   else if(x > mid) return functionH(x, y, ri, mid+1, end);
   return ((( functionH(x, mid, le, ini, mid)*B[y-mid] ) % MOD) + functionH(mid+1, y, ri, mid+1, end)) % MOD;
}

int main(){
   int b, p, l, n, x, y;
   char op;
   scanf("%d %d %d %d", &b, &p, &l, &n);
   while(b){
      memset(T, 0, sizeof(T));
      memset(B, 0, sizeof(B));
      B[0] = 1;
      MOD = p;
      FOR(i, 1, 100000) B[i] = (B[i-1]*LL(b)) % MOD;
      F(i, n){
         cin>>op>>x>>y;
         if(op == 'E') insert(x, y, 1, 1, l);
         else printf("%lld\n", functionH(x, y, 1, 1, l));
      }
      printf("-\n");
      scanf("%d %d %d %d", &b, &p, &l, &n);
   }
}

