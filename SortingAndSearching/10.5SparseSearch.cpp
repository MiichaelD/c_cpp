/*
	Description:	Sparse Search: Given a sorted array of strings that is interspersed with
					empty strings, write a method to find the location of a given string.

	Programmer:		Michael Duarte

	Date:			Sep 11, 2016.	
*/
#include <iostream>
#include <algorithm>
#include <cmath>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int search(const vector<string> &strings, const string &str, int left, int right){
	if (left > right) return -1;

	int mid = (left + right) / 2;
	if (strings[mid].empty()){
		// cout << "\tHit an empty str at index " << mid; 
		int low = mid - 1;
		int high = mid + 1;
		while (true){
			if (low < left && high > right) return -1;

			if (high <= right && !strings[high].empty()){
				mid = high;
				break;
			} else if (low >= left && !strings[low].empty()){
				mid = low;
				break;
			}
			++high;
			--low;
		}
		// cout << ". Chose closest: " << strings[mid] << " at index " << mid << endl; 
	}

	int compareRes = strings[mid].compare(str);
	// cout << "\t\tComparing " <<strings[mid] << " with: " << str << " = " << compareRes << endl;  
	if (compareRes == 0)
		return mid;
	if (compareRes < 0){ // mid is before  str, search right
		return search(strings, str, mid + 1, right);
	}
  return search(strings, str, left, mid - 1); // search left
}

int search(const vector<string> &strings, const string &str){
	if (strings.empty() || str.empty())
		return -1;
	return search(strings, str, 0, strings.size()-1);
}

int main() {
	vector<string> strings = {"abecedario", "", "alfa", "", "", "ball", "beta", "", "", "car",
		"", "delta", "", "", "hello", "", "higado","", "", "", "liver", "lover", "", "", "", 
		"major", "", "", "minor", "", "omega","", "", "", "orange","", "", "", "", "", "", 
		"planet", "", "world", "", "", "zebra"};

	for (const string  &str : {"","abc","abecedario", "alfa", "omega", "zebr", "zebra", "world"}){
		int index = search(strings, str);
		if (index < 0){
			cout << "Element \'" << str << "\' not found." << endl;
		} else {
			cout << "Element \'" << str << "\' was found at index: " << index << endl; 
		}
	}
	return EXIT_SUCCESS;
}

