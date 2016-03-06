/*
This is a typical case of LCA. Example (Sample input 1):

6                Tree:   0
0 8                     / \
1 7                    1   4
1 9                   / \   \
0 3                  2   3   5
4 2
4
2 3
5 2
1 4
0 3

(2 3):

 sum = 0      sum = 0    sum = p[a] + p[b] = 7 + 9 = 16
    x           x           x       
   / \         / \         / \      
  1   x   =   1   x   = ab1   x  
 / \   \     / \   \     / \   \    
2   3   x   a2 b3   x   x   x   x

(5 2):

 sum = 0      sum = 0  sum=p[a]+p[b]= 9 + 11 = 20
                              2+7         8+3

    0           0           0           0ab       
   / \         / \         / \         / \      
  1   4   =   1   4   =   1a  4b  =   x   x   
 / \   \     / \   \     / \   \     / \   \    
2a  3  b5   2a  x  b5   x   x   x   x   x   x 

This is my implementation: 
*/


#include <iostream>
#include <vector>
#include <math>
using namespace std;

#define FOR(i,a,b)  for(int i=(a),_##i=(b);i<_##i;++i)
#define F(i,a)      FOR(i,0,a)
#define PB          push_back
#define MP          make_pair
#define S           size()
typedef long long   LL;

int TreeDad[100000], TreeDadH[100000];
int TreeLevel[100000];
LL TreeLen[100000];
vector<vector<int> > TreeSons(100000);

int N, sqrtL;

void build_tree(int node){
  if(!(TreeLevel[node] % sqrtL))
    TreeDadH[node] = TreeDad[node];
  else
    TreeDadH[node] = TreeDadH[ TreeDad[node] ];
  F(i, TreeSons[node].S)
    build_tree(TreeSons[node][i]);
}

int LCA(int x, int y) {
  while (TreeDadH[x] != TreeDadH[y]){
    if(TreeLevel[x] > TreeLevel[y]) x = TreeDadH[x];
    else y = TreeDadH[y];
  }
  while (x != y){
    if (TreeLevel[x] > TreeLevel[y]) x = TreeDad[x];
    else y = TreeDad[y];
  }
  return x;
}

int main(){
  int l, a, Q, s, t;
  while(scanf("%d", &N) && N){
    F(i, N) TreeSons[i].clear();
    int MaxLevel = 0;
    FOR(i, 1, N){
      scanf("%d %d", &a, &l);
      TreeDad[i] = a;
      TreeLen[i] = TreeLen[a] + LL(l);
      TreeLevel[i] = TreeLevel[a] + 1;
      TreeSons[a].PB(i);
      MaxLevel = max(MaxLevel, TreeLevel[i]);
    }
    sqrtL = sqrt(MaxLevel);
    build_tree(0);

    scanf("%d", &Q);
    F(i, Q){
      if(i) printf(" ");
      scanf("%d %d", &s, &t);
      printf("%lld", TreeLen[s] + TreeLen[t] - (TreeLen[LCA(s, t)]*2LL) );
    }
    printf("\n");
  }
}
