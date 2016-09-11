/*
	Description:	8.8 Permutations with Dups: Write a method to compute all permutations
					of a string whose characters are not necessarily unique. The list of 
					permutations should not have duplicates.

	Programmer:		Michael Duarte

	Date:			Sep 8, 2016.	
*/

#include <iostream>
#include <string>
#include <deque>
#include <memory>
#include <unordered_map>
#include <utility>

using namespace std;

void print(const deque<string> &deck){
	int i = 0;
	for(const string &word : deck){
		cout << ++i << ": " << word << endl;
	}
	cout << endl;
}

unordered_map<char, int> buildFreqTable(const string &str){
	unordered_map<char, int> map;
	for (char c : str){
		++map[c];
		// cout << "char " << c << ": " << map[c] << endl;
	}
	return map;
}

void getPermutations(unordered_map<char, int> &map, deque<string> &res,
		size_t remaining, const string &prefix = ""){
	if (remaining == 0){
		res.push_back(prefix);
		return;
	}

	for (pair<const char, int> &pair: map){
		if (pair.second){
			--pair.second;
			getPermutations(map, res, remaining - 1, prefix+pair.first);
			++pair.second;
		} 
	}
}

deque<string> getPermutations(const string &str){
	deque<string> result;
	unordered_map<char, int> map = buildFreqTable(str);
	getPermutations(map, result, str.length());
	return result;
}



/// WITH NO DUPLICATES
void printPermutations(const string &str, const string &prefix = ""){
	static int counter = 0;
	if (str.length() == 0) {
		cout << ++counter << ": " << prefix << endl;
	}
	else {
		for (int i = 0; i < str.length(); ++i) {
			string rem = str.substr(0, i) + str.substr(i + 1);
			// cout << "\tremaining: " << rem << ", prefix: " << prefix << str[i] << endl;
			printPermutations(rem, prefix + str[i]);
		}
	}
}


int main(){
	string str = "abbbbbbc";
	printPermutations(str);
	cout << endl << endl;
	auto permutations = getPermutations(str);
	print(permutations);
	return 0;
} 