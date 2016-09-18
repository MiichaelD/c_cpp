/*
	Description:	8.4 Power Set: Write a method to return all subsets of a set.

	Programmer:		Michael Duarte

	Date:			Sep 8, 2016.	
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

void print(const vector<int> &subset){
	cout << "subset: ["; 
	auto it = subset.rbegin();
	for(;it != subset.rend(); ++it){
		cout << " " << *it;
	}
	cout << "]" << endl; 
}

void print(const vector<vector<int>> &subsets){
	auto it = subsets.rbegin();
	for(;it != subsets.rend(); ++it){
		print(*it);
	}
	cout << endl;
}

vector<vector<int>> getSubsets(const vector<int> &set, int index = 0){
	vector<vector<int>> results;
	if (set.size() == index){ // base case
		results.emplace_back();
	} else {
		results = getSubsets(set, index + 1);

		vector<vector<int>> moreSets;
		moreSets.reserve(results.size());
		for (const vector<int> &result : results){
			moreSets.push_back(result);
			moreSets.back().push_back(set[index]);
		}
		results.insert(results.end(), moreSets.begin(), moreSets.end());
	}
	return results;
}

int main(){
	// total subsets   =  2 ^ n;
	// space complexity=  n * (2 ^ ( n-1)); // total of elements thru all subsets
	vector<int> set = {2, 4, 8, 16, 32};
	auto subsets = getSubsets(set);
	print(subsets);
	return 0;
} 