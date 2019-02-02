
/**
  Description:  Finds the max profit user can make by selling/buying stocks depending on their
                price.

                I.e. when finding a high price what would be the max profit given we bought at the
                minimum price seen before.

  Compiling:    g++ -std=c++11 stocks.cc -o main
               
  Programmer:   Michael Duarte.

  Date:         02/02/2019
 */
#include <iostream>
#include <string>
#include <vector>
#include <climits>

using namespace std;

int getMaxProfit(const vector<int> &input) {
  int maxProfit = 0;
  int minVal = INT_MAX;
  int maxVal = INT_MIN;
  for (int in : input) {
    if (maxVal < in) {
      maxVal = in;
      maxProfit = maxVal - minVal;
    }
    if (minVal > in) {
      minVal = in;
    }
  }
  return maxProfit;
}

int main() {
  vector<int> input = {6, 0, -1, 10};
  int maxProfit = getMaxProfit(input);
  cout << "Max Profit: " << maxProfit << endl;
}