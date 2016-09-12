/*
	Description:	Search in rotated array: Given a sorted array of n integers that has been
					rotated an unknown number of times, write a code to find an element in the
					array. You may asume that the array was originally sorted in increasing
					order.

	Programmer:		Michael Duarte

	Date:			Sep 11, 2016.	
*/
#include <iostream>
#include <algorithm>
#include <cmath>
#include <climits>
#include <vector>
#include <algorithm>

using namespace std;

int getOffset(const vector<int> &arr){
	for (int i = 1;  i < arr.size(); ++i){
		if (arr[i] < arr[i-1]){
			return i;
		}
	}
	return 0; // no offset
}

void normalizeIndex(int &index, int size, int offset){
	index += offset;
	if (index < 0){
		index = size - index;
	} else {
		index %= size;
	}
}

// This is the first thing I thought of, but ...
// it's runtime is n when trying to find the offset, since there
// might be no offset or it might be at the end of the array, 
// it would be better to do a linear.
// This solution would only be good if we needed to search a lot of items
// and we cached the offset so we don't look for it each search.
int binarySearchRotated(const vector<int> &arr, int x){
	int offset = getOffset(arr);
	// cout << "offset = " << offset << endl; 
	int low = 0;
	int high = arr.size() - 1;
	int mid;
	int index;
	while (low <= high){
		index = mid = (low + high) / 2;
		normalizeIndex(index, arr.size(), offset);
		// cout << "index: " << mid << " = " << index << " has val: " <<arr[index]<< endl; 
		if (arr[index] == x)
			return index;
		if (arr[index] < x)
			low = mid + 1;
		else 
			high = mid - 1;
	}
	return -1;
}

struct PendingSearch{
	int left, right;
	PendingSearch();
	PendingSearch(int l, int r):left(l),right(r){}
};

int bookSearchIt(const vector<int> &arr, int x){
	// stack for pending searches, in case we need to look at both sides
	vector<PendingSearch> ps; 
	ps.emplace_back(0,arr.size()-1);
	int left;
	int right;
	int mid;

	while (!ps.empty()) {
		left = ps.back().left;
		right = ps.back().right;
		ps.pop_back();

		while(left <= right){
			mid = (left+right)/2;
			if (arr[mid] == x)
				return mid;

			// Either the left or right side must be normally ordered. Find out which side
			// is normally ordered, then use it to figure out which side to search to find x
			if (arr[left] < arr[mid]){ // left side is normally ordered
				if (x >= arr[left] && x < arr[mid])
					right = mid - 1; //search left
				else 
					left = mid + 1; // search right
			} else if (arr[left] > arr[mid]){ // right side is normally ordered
				if (x > arr[mid] && x <= arr[right])
					left = mid + 1; // search right
				else
					right = mid - 1; // search left
			} else if (arr[left] == arr[mid]){ // left or right half is all repeats
				if (arr[mid] != arr[right]) // if right is different, search it
					left = mid + 1;
				else {
					//search both halves :(
					right = mid - 1; // search left

					// set a pending search if we don't find it on the left side
					ps.emplace_back(mid + 1, right);
				}
			}
		}
	}
	return -1;
}

int bookSearchRec(const vector<int> &arr, int x, int left, int right){
	int mid = (left + right) / 2;
	if (arr[mid] == x) return mid;

	if (right < left) return -1;

	// Either the left or right side must be normally ordered. Find out which side
	// is normally ordered, then use it to figure out which side to search to find x
	if (arr[left] < arr[mid]){ // left side is normally ordered
		if (x >= arr[left] && x < arr[mid]){
			right = mid - 1; //search left
			return bookSearchRec(arr, x, left, right);
		} else {
			left = mid + 1; // search right
			return bookSearchRec(arr, x, left, right);
		}
	} else if (arr[left] > arr[mid]){ // right side is normally ordered
		if (x > arr[mid] && x <= arr[right]){
			left = mid + 1; // search right
			return bookSearchRec(arr, x, left, right);
		} else{
			right = mid - 1; // search left
			return bookSearchRec(arr, x, left, right);
		}
	} else if (arr[left] == arr[mid]){ // left or right half is all repeats
		if (arr[mid] != arr[right]){ // if right is different, search it
			left = mid + 1;
			return bookSearchRec(arr, x, left, right);
		} else {
			//search both halves :(
			int result = bookSearchRec(arr, x, left, mid - 1); // search left
			if (result == -1)
				return bookSearchRec(arr, x, mid + 1, right); // search right
		}
	}
	return -1;
}

int bookSearchRec(const vector<int> &arr, int x){
	return bookSearchRec(arr, x, 0, arr.size()-1);
}

void print(const vector<int> &arr){
	cout << "["; 
	for (int i : arr){
		cout << " " << i;
	}
	cout << "]" << endl; 
}

int main() {
	// vector<int> arr = {15,16,19,20,25,1,3,4,5,7,10,14};
	vector<int> arr = {2,2,2,3,4};
	print(arr);
	// for (int i : {5, 14, 4, 24, 26}){
	for (int i : {0, 1, 2, 3, 4, 5}){
		// int index = binarySearchRotated(arr, i);
		int index = bookSearchIt(arr, i);
		// int index = bookSearchRec(arr, i);
		if (index < 0){
			cout << "Element " << i << " NOT found." << endl;
		} else {
			cout << "Element " << i << " was found at index: " << index << endl; 
		}
	}
	return EXIT_SUCCESS;
}

