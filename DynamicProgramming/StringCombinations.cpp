/*
  Description:  Prints all the string combinations possible given a input string.
  From:         https://javahungry.blogspot.com/2014/02/algorithm-for-combinations-of-string-java-code-with-example.html
  Date:         Sep 20, 2019.  
*/

#include <iostream>
#include <string>
#include <sstream>
#include <deque>
#include <memory>

using namespace std;

void combine(const string &inputString, string &modified, int start = 0) {
  for(int i = start; i < inputString.length(); ++i ){
    modified += inputString[i];
    cout << modified << endl;
    if (i < inputString.length()){
      combine(inputString, modified, i + 1);
    }
    // Removes last character from stringstream
    modified.pop_back();
  }
}

void combine(const string &inputString, int start = 0) {
  string output;
  combine(inputString, output, start);
}

int main(){
  string inputString;
  cin >> inputString;
  cout << "input: " << inputString << endl << "All possible combinations are:" << endl;
  combine(inputString);
  return 0;
} 
