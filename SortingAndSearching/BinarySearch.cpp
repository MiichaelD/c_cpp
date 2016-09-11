/*
	Description:	Binary Search.

	Run-time:		O(log(n))

	Programmer:		Michael Duarte

	Date:			Sep 10, 2016.	
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void print(const vector<int> &arr){
	cout << "["; 
	for (int i : arr){
		cout << " " << i;
	}
	cout << "]" << endl; 
}

int binarySearchRec(const vector<int> &arr, int x, int low, int high){
	if (low <= high){
		int mid = (low + high) / 2;
		cout << "mid: " << mid << endl; 
		if (arr[mid] < x)
			return binarySearchRec(arr, x, mid + 1, high);
		
		if (arr[mid] > x)
			return binarySearchRec(arr, x, low, mid - 1);

		return mid;
	}
	return -1;
}

int binarySearchRec(const vector<int> &arr, int target){
	return binarySearchRec(arr, target, 0, arr.size()-1);
}


int binarySearchIt(const vector<int> &arr, int x){
	int low = 0;
	int high = arr.size() - 1;
	int mid;
	while (low <= high){
		mid = (low + high) / 2;
		if (arr[mid] == x)
			return mid;
		if (arr[mid] < x)
			low = mid + 1;
		else 
			high = mid - 1;
	}
	return -1;
}

int main(){
	// vector<int> arr = {2, 4, 8, 16, 32};
	vector<int> arr = {128, 2, 16, 8, 512, 4, 32, 1, 64, 256};
	sort(arr.begin(), arr.end());
	print(arr);
	for (int i : {5, 4, 64}){
		int index = binarySearchRec(arr, i);
		if (index < 0){
			cout << "Element " << i << " not found." << endl;
		} else {
			cout << "Element " << i << " was found at index: " << index << endl; 
		}
	}
	return 0;
} 