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

// void printPermutations(const string &str, const string &prefix = ""){
//   if (str.length() == 0) {
//     cout << prefix << endl;
//   }
//   else {
//     for (int i = 0; i < str.length(); ++i) {
//       string rem = str.substr(0, i) + str.substr(i + 1);
//       // cout << "\tremaining: " << rem << ", prefix: " << prefix << str[i] << endl;
//       printPermutations(rem, prefix + str[i]);
//     }
//   }
// }

// deque<string> getPermutations(const string &str){
//   deque<string> result;
//   if (str.empty()){
//     result.push_back(str);
//     return result;
//   }

//   char first = str[0];
//   deque<string> words = getPermutations(str.substr(1));
//   for (string &word : words){
//     for (int i = 0; i <= word.length(); ++i){
//       string newWord = word.substr(0, i) + first + word.substr(i);
//       result.push_back(newWord);
//     }
//   }
//   return result;
// }

// void print(const deque<string> &deck){
//   for(const string &word : deck){
//     cout << word << endl;
//   }
//   cout << endl;
// }


// int main(){
//   string str = "12340";
//   printPermutations(str);
//   cout << endl << endl;
//   auto permutations = getPermutations(str);
//   print(permutations);
//   return 0;
// } 