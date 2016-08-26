
/*
	Description:	Given an array of size N, with integers [0, MAX_INT], calculate the
					H-Index value. H-Index is defined by the largest num k, such that
					there are at least k items in the array >= k.

	Example:	 	Given array [1,4,2,3,3], H-Index value is 3
					Given array [1,5,2,4,2], H-Index value is 2
					Given array [5,5,5,5,5,1], H-Index value is 5
					Given array [5,5,5,5,1], H-Index value is 1
*/

#include <iostream>
#include <string>
#include <utility>
#include <algorithm>
#include <unordered_map>
#include <cmath>
#include <cstdio>
#include <cctype>
#include <climits>
#include <cstdint>
#include <iomanip>

using namespace std;

class ArrayHolder{
	int *arr = nullptr;
	ArrayHolder(int elements){
		arr = new int[elements];
	}
	
	~ArrayHolder(){
		if(arr){
			delete arr;
			arr = nullptr;
		}
	}
};

int getH_index(int arr[], int size){
	sort(arr, arr+size);

	int val = INT_MAX, reps = 0;
	for(int i = size - 1; i >= 0; --i){
		val = arr[i];
		++reps;
		if (reps >= val)
			return val;
	}
}

int main(){
	std::ios::sync_with_stdio(false); // http://en.cppreference.com/w/cpp/io/ios_base/sync_with_stdio
	cin.tie(NULL);
	
	int arr[] = {1,4,2,3,3};
	cout << getH_index(arr, sizeof(arr)/sizeof(int)) << endl;

	int arr2[] = {1,5,2,4,2};
	cout << getH_index(arr2, sizeof(arr2)/sizeof(int)) << endl;	

	int arr3[] = {5,5,5,5,5,1};
	cout << getH_index(arr3, sizeof(arr3)/sizeof(int)) << endl;	

	
	return 0;
}