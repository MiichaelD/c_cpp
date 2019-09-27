/**  
 * Name:        AddTwoBinaryNumbers.cpp
 * Description: Given 2 strings containing a number in binary representation each, define a function
 *              which adds both numbers and returns the sum result in binary representation in
 *              string
 * 
 * Example:     INPUT = "10101", "1011"
 *              OUTPUT: "100000"
*/
#include <iostream>
#include <cmath>

using namespace std;

// 1st solution
string addTwoBinaryNumbers(const string &s1, const string &s2) {
  int lengthDiff = s1.length() - s2.length(); 
  // sets both strings to same length (could be improved if we removed 0s at the beginning)
  string bs1, bs2;
  if (lengthDiff > 0) { // concatenate 00s at the beginning of s2
    bs1 = s1;
    bs2 = string(lengthDiff, '0') + s2;
  } else if (lengthDiff < 0) { // concatenate 00s at the beginning of s1
    bs1 = string(-lengthDiff, '0') + s1;
    bs2 = s2;
  }
  
  string output;
  bool carreage = false;
  for (int i = bs1.length() - 1; i >= 0; --i) {
    int sum = carreage ? 1 : 0;
    sum += bs1[i] == '1' ? 1 : 0;
    sum += bs2[i] == '1' ? 1 : 0;
    
    output = (sum % 2 == 1 ? '1' : '0') + output;
    carreage = sum > 1;
  }
  if (carreage) {
    output = '1' + output;
  }
  return output;
}

// 2nd approach - parsing strings as numbers, adding them and then getting its string representation
int getIntFromBinary(const string &s) {
  int n = 0;
  for (int i = 0; i < s.length(); ++i) {
    if (s[s.length() - 1 - i] == '1') {
      n += (1 << i);
    }
  }
  return n;
}

string getBinaryFromInt(int n) {
  string output;
  bool onlyZeros = true;
  for (unsigned i = 1 << 31; i > 0; i /= 2) {
    bool one = n & i;
    if (!one && onlyZeros) {
      continue;
    }
    onlyZeros = false;
    output += (one ? '1' : '0');
  }
  return output;
}

string addTwoBinaryNumbers2(const string &s1, const string &s2) {
  return getBinaryFromInt(getIntFromBinary(s1) + getIntFromBinary(s2));
}

int main() {
  string s1 = "10101";
  string s2 = "1011";
  cout << s1 << " + " << s2 << " = " << addTwoBinaryNumbers(s1, s2) << endl;
  return EXIT_SUCCESS;
}

// Original solution was in java.
// class Solution {
//   /**
//    * s1 = 10101   => 5
//    * s2 =  1011   => 4
//    */
//   public String addTwoBinaryNumbers(String s1, String s2) {
//     int lengthDiff = s1.length() - s2.length(); 
//     // sets both strings to same length (could be improved if we removed 0s at the beginning)
//     if (lengthDiff > 0) { // concatenate 00s at the beginning of s2
//       s2 = new String('0', lengthDiff) + s2;
//     } else if (lengthDiff < 0) { // concatenate 00s at the beginning of s1
//       s1 = new String('0', -lengthDiff) + s1;
//     }
    
//     StringBuilder sb = new StringBuilder();
//     boolean carreage = false;
//     for (int i = s1.length() - 1; i >= 0; --i) {
//       int sum = carreage ? 1 : 0;
//       sum += s1.charAt(i) == '1' ? 1 : 0;
//       sum += s2.charAt(i) == '1' ? 1 : 0;
      
//       sb.insert(/*index*/0, sum % 2 == 1 ? '1' : '0');
//       carreage = sum > 1;
//     }
//     if (carreage) {
//       sb.insert(/*index*/0, '1');
//     }
//     return sb.toString();
//   }
// }

