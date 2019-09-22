/*
	Description:	8.7 Permutations without Dups: write a method to compute all permutations
					of a string of unique characters;

	Programmer:		Michael Duarte

	Date:			Sep 8, 2016.	
*/

#include <iostream>
#include <string>
#include <deque>
#include <memory>

using namespace std;

/**
 *  Prints a list of permutations of the input string.
 *  This solution uses more recursion.
 *  Recursively calls itself by removing a letter of the input string in order, this remainder is
 *  used as the new input string to permutate, while the removed character is appended at the end of
 *  the prefix.
 *  Once the input string to permutate is empty, we print the prefix.
 */
void printPermutations(const string &str, const string &prefix = ""){
	if (str.empty()) {
		cout << prefix << endl;
	}
	else {
		for (int i = 0; i < str.length(); ++i) {
			string rem = str.substr(0, i) + str.substr(i + 1);
			// cout << "\tremaining: " << rem << ", prefix: " << prefix << str[i] << endl;
			printPermutations(rem, prefix + str[i]);
		}
	}
}

/**
 *  Returns a list of permutations of the input string.
 *  This solution uses less recursion, it goes as deep as many characters are in the string.
 *  For each word returned by recursively calling the same function with the remainder of input
 *  string (after removing the 1st character), the 1st character will be moved around each position
 *  of the word.
 *  Once the 1st character has been permutated in each position for each word returned by the
 *  previous recursive call, we return the new resulting array to be used as new list of words.
 */
deque<string> getPermutations(const string &str){
	deque<string> result;
	if (str.empty()){
		result.push_back(str);
		return result;
	}
	char first = str[0];
	deque<string> seedWords = getPermutations(str.substr(1));
	for (string &word : seedWords){
		for (int i = 0; i <= word.length(); ++i){
			result.push_back(word.substr(0, i) + first + word.substr(i));
      // cout << "pushing back: " << result.back() << endl;
		}
	}
	return result;
}

void print(const deque<string> &deck){
	for(const string &word : deck){
		cout << word << endl;
	}
	cout << endl;
}

int main(){
	string str = "123";
	printPermutations(str);
	cout << endl << endl;
	auto permutations = getPermutations(str);
	print(permutations);
	return 0;
} 