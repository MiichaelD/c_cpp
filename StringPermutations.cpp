
#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <functional>
using namespace std;

void permutation(const string &str, const string &prefix = "") {
	if (str.length() == 0) {
		cout << prefix << endl;
	}
	else {
		for (int i = 0; i < str.length(); ++i) {
			string rem = str.substr(0, i) + str.substr(i + 1);
			cout << "\tremaining: " << rem << ", prefix: " << prefix << str[i] << endl;
			permutation(rem, prefix + str[i]);
		}
	}
}

// ---------------------------------------------------------------------------//
int numChars = 26;

bool isInOrder(const string &str) {
	for (int i = 1; i < str.length(); ++i) {
		char prev = str[i - 1];
		char curr = str[i];
		if (prev > curr)
			return false;
	}
	return true;
}

char ithLetter(int i) {
	return 'a' + i;
}

void printSortedStrings(int remaining, const string &prefix = "") {
	if (remaining == 0) {
		if (isInOrder(prefix))
		{
			cout << prefix << endl;
		}
	}
	else {
		for (int i = 0; i < numChars; ++i) {
			char c = ithLetter(i);
			printSortedStrings(remaining - 1, prefix + c);
		}
	}
}


int main() {
	string toPermut = "abc";
	//permutation(toPermut);
	printSortedStrings(4);
	return EXIT_SUCCESS;
}
