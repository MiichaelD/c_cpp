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
void printPermutations(const string &str, const string &prefix = ""){
	if (str.length() == 0) {
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

deque<string> getPermutations(const string &str){
	deque<string> result;
	if (str.empty()){
		result.push_back(str);
		return result;
	}

	char first = str[0];
	deque<string> words = getPermutations(str.substr(1));
	for (string &word : words){
		for (int i = 0; i <= word.length(); ++i){
			string newWord = word.substr(0, i) + first + word.substr(i);
			result.push_back(newWord);
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
	string str = "abc";
	printPermutations(str);
	cout << endl << endl;
	auto permutations = getPermutations(str);
	print(permutations);
	return 0;
} 