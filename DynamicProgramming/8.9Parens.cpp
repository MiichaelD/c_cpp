/*
	Description:	8.9 Parens: Implement an algorithm to print all valid (i.e., properly
					opened and closed) combinations of n pairs of parentheses.

	Programmer:		Michael Duarte

	Date:			Sep 9, 2016.	
*/

#include <unordered_set>
#include <iostream>
#include <utility>
#include <string>
#include <memory>
#include <deque>

using namespace std;

void print(const deque<string> &list){
	int i = 0;
	for(const auto &word : list){
		cout << ++i << ": " << word << endl;
	}
	cout << endl;
}

void print(const unordered_set<string> &set){
	int i = 0;
	for(const auto &word : set){
		cout << ++i << ": " << word << endl;
	}
	cout << endl;
}


// This implementation is slower bc we process duplicates,
// to avoid printing them both we contain the strings in a set
// but still, we process them.
unordered_set<string> buildParensSlower(int n){
	unordered_set<string> set;
	if (n == 0){
		set.emplace("");
	} else {
		auto aux = buildParensSlower(n-1);
		for (const string &built : aux){
			for (int i = 0 ; i < built.length(); ++i){
				if (built[i] == '('){
					string prefix = built.substr(0, i+1);
					string suffix = built.substr(i+1);
					set.emplace(prefix+"()"+suffix);			
				}
			}
			set.emplace("()"+built);
		}
	}
	return set;
}

void buildParens(deque<string> &list, int leftRem, int rightRem, char *str, int index = 0){
	if (leftRem < 0 || rightRem < leftRem)
		return;

	if (leftRem == 0 && rightRem == 0){ // we finished all left and right parens
		list.emplace_back(str);
	} else {
		str[index] = '('; // add left paren and recurse
		buildParens(list, leftRem-1, rightRem, str, index+1);

		str[index] = ')'; // add right paren and recurse
		buildParens(list, leftRem, rightRem-1, str, index+1);
	}
}

deque<string> buildParens(int n){
	const int strSize = 2 * n;
	char *str = new char[strSize+1];
	str[strSize] = '\0';
	deque<string> list;
	buildParens(list, n, n, str);
	delete[] str;
	return list;
}


int main(){
	auto list = buildParens(3);
	print(list);
	return 0;
} 