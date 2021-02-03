#include <iostream>
#include <vector>

using namespace std;

int totalLlamadas = 0;
vector<int> fibs {0,1};

inline void printDepth(int d) {
  for (int i = 0; i < d; ++i) {
    cout << "  ";
  }
}

int fib(int n, int depth = 0) {
  ++totalLlamadas;
  printDepth(depth);
  cout << n << endl;
  if (n <= 1) {
    return n;
  }
  int result = fib(n-1, depth+1) + fib(n-2, depth+1);
  return result;
}
// "Memoization"
int fibMemo(int n, int depth = 0) {
  ++totalLlamadas;
  printDepth(depth);
  cout << n << endl;
  if (n < fibs.size()) {
    return fibs[n];
  }
  int result = fibMemo(n-1, depth+1) + fibMemo(n-2, depth+1);
  while (fibs.size() <= n) { fibs.push_back(1); } 
  fibs[n] = result;
  return result;
}

void printFibs() {
  for (int x : fibs) {
    cout << x << ",";
  }
  cout << endl;
}


int main () {
  int n = 8, res = 0;
  totalLlamadas = 0;
  res = fib(n);
  cout << "Fibonacci (" << n << ") = " << res << endl;
  cout << "Llamadas totales: " << totalLlamadas << endl << endl;
  
  totalLlamadas = 0;
  res = fibMemo(n); 
  cout << "FibonacciMemo (" << n << ") = " << res << endl;
  cout << "Llamadas totales: " << totalLlamadas << endl << endl << endl;

  printFibs();

}