/**  
 * Name:        ArithmeticCombinationToTarget.cpp
 * Description: Given a String and an int as Input and a target, using standard integer arithmetic 
 *              operators +, -, how many different solutions can you find by inserting the operators
 *              between some digits?
 * Example:     INPUT = "123456789". TARGET = 100
 *              OUTPUT: All combinations with '+' and '-' that sums up to 100:
                -1+2-3+4+5+6+78+9
                1+2+3-4+5+6+78+9
                1+2+34-5+67-8+9
                1+23-4+5+6+78-9
                1+23-4+56+7+8+9
                12+3+4+5-6-7+89
                12+3-4+5+67+8+9
                12-3-4+5-6+7+89
                123+4-5+67-89
                123+45-67+8-9
                123-4-5-6-7+8-9
                123-45-67+89
*/

#include <iostream>
#include <string>
#include <sstream>
#include <deque>
#include <memory>

using namespace std;

const int MAX_OPERATORS = 2;
const char OPERATORS[MAX_OPERATORS] = {'+', '-'};

int totalCombinations;

void print(const deque<string> &listOfStrings){
  for(const string &str : listOfStrings){
    cout << str << endl;
  }
  cout << endl << "Total solutions: " << listOfStrings.size();
  cout << " & total permutaions: " << totalCombinations << endl;
}

void helper(deque<string> &result, const string &input, int target, int charCount, string answer = "") {
  ++totalCombinations;
  if (charCount == input.length() && target == 0) {
    cout << "Answer: " << answer  << " => " << target << endl;
    result.push_back(answer);
  } else if (charCount < input.length()) {
    for (int i = 1; i <= (input.length() - charCount); ++i) {
      string substr = input.substr(charCount, i);
      size_t substrLen = substr.length();
      for (int op = 0 ; op < MAX_OPERATORS; ++op) {
        stringstream newAnswer;
        newAnswer << answer;
        if (charCount != 0 || op != 0) {
          newAnswer << OPERATORS[op];
        }
        newAnswer << substr;
        int newTarget = target + (op == 0 ? (- stoi(substr)) : stoi(substr));
        helper(result, input, newTarget, charCount + substrLen, newAnswer.str());
      }
    }
  }
}

deque<string> findSolutions(const string &inputString, int target) {
  totalCombinations = 0;
  deque<string> result;
  helper(result, inputString, target, 0);
  return result;
}

int main(){
  string str = "123456789";
  int target = 100;
  print(findSolutions(str, target)); // complexity: O(3 ^ N) 
  return 0;
} 