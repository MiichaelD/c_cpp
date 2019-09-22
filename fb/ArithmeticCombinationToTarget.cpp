/**  
 * Name:        ArithmeticCombinationToTarget.cpp
 * Description: Given a String and an int as Input and a targetUsing standard integer arithmetic 
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
#include <deque>
#include <memory>

using namespace std;

const int MAX_OPERATORS = 2;
const char OPERATORS[MAX_OPERATORS] = {'+', '-'};

void print(const deque<string> &listOfStrings){
	for(const string &str : listOfStrings){
		cout << str << endl;
	}
	cout << endl;
}

deque<deque<string>> generateListOfCombinations(const string &inputString) {
  string output;
  deque<deque<string>> solutions;
  for (int i = 0 ; i < inputString.length(); ++i) {
    solutions.push_back(deque<string>());
    for (int j = 1; j <= (inputString.length() - i); ++j) {
      solutions.back().push_back(inputString.substr(i, j));
    }
  }
  return solutions;
}

void helper2(deque<string> &result, string answer, deque<deque<string>> combinations, int listIndex, int charactersUsed, int target) {
  if (charactersUsed == combinations[0].size() && target == 0) {
    cout << "Answer: " << answer << "\t=> " << target << endl;
    result.push_back(answer);
  }
  else if (charactersUsed < combinations[0].size()) {
    auto combination = combinations[listIndex];
    for (int op = 0 ; op < MAX_OPERATORS; ++op) {
      for (int i = 0; i < combination.size(); ++ i) {
        const string &substr = combinations[listIndex][i];
        size_t substrLen = substr.length();
        if (charactersUsed != 0 || op != 0) {
           answer += OPERATORS[op];
        }
        answer += substr;
        if (charactersUsed + substrLen > combinations[0].size()) {
          break;
        }
        int newTarget = target + (op == 0 ? (- stoi(substr)) : stoi(substr));
        helper2(result, answer, combinations, listIndex + substrLen, charactersUsed + substrLen , newTarget);
        for (int i = 0; i <= substrLen; ++i) {
          answer.pop_back();
        }
      }
    }
  }
}

deque<string> findSolutions(const string &inputString, int target) {
  auto combinations = generateListOfCombinations(inputString);
  deque<string> result;
  helper2(result, "", combinations, 0, 0, target);
  return result;
}

int main(){
	string str = "123456789";
  int target = 100;
  auto solutions = findSolutions(str, target);
	print(solutions);
	return 0;
} 