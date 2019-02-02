/**
  Description:  Check if a string is a palindrome (ignoring spaces) or if it is a permutation of
                a palindrome.
                i.e. racecar => palindrome.
                     carrace => palindrome permutation.

  Compiling:    g++ -std=c++11 palindrome.cc -o main
               
  Programmer:   Michael Duarte.

  Date:         02/02/2019
 */

#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

bool checkPalindrome(const std::string& str) {
    int len = str.length();
    for(int i =0, j = len-1;i<j;i++, j--){
        while(str[i] == ' ') i++;
        while(str[j] == ' ') j--;
        if (str[i] != str[j]) return false;
    }
    return true;
} 

bool checkPalindromePermutation(const std::string &str) {
  using namespace std;
  bool isStringLengthOdd = str.length() % 2;
  unordered_set<char> chars;

  for (int i = 0; i < str.length(); ++i) {
    char c = str[i];
    if (c == ' ') continue;
    if (chars.find(c) == chars.end()) {
      chars.insert(c);
    } else {
      chars.erase(c);
    }
  }
  return (chars.size() == 0 || (chars.size() == 1 && isStringLengthOdd));
}

void printPalindrome(const std::string& str) {
  std::cout << str << " is" << std::endl << "\t";
  std::cout << (checkPalindrome(str) ? "" : "not ") << "a palindrome." << std::endl;
  std::cout << "\t" << (checkPalindromePermutation(str) ? "" : "not ");
  std::cout << "a palindrome permutation" << std::endl;
}

int main() {
  std::string test1 = "tacocat";
  std::string test2 = "carrace";
  printPalindrome(test1);
  printPalindrome(test2);
}