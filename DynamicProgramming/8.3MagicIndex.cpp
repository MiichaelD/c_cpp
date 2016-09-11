/*
	Description:	8.3 Magic Index: A magic index in an Array A[0..n-1] is defined to be
					an index such that A[i] = i. Given a sorted array of distinct integers,
					write a method to find a magic index, if one exists, in array A.

	Extra:			What if the values are not distinct?

	Programmer:		Michael Duarte

	Date:			Sep 7, 2016.	
*/

#include <iostream>
#include <vector>
#include <memory>

using namespace std;

// 1st solution: binary search
int findMagicIndex(const vector<int> &vec, int start, int end){
	if (start > end) return -1;

	int mid = (start + end) / 2;
	if (mid == vec[mid])
		return mid;
	if (mid < vec[mid]){
		return findMagicIndex(vec, start, mid-1);
	}
	return findMagicIndex(vec, mid+1, end);
}

int findMagicIndex(const vector<int> &vec){
	return findMagicIndex(vec, 0, vec.size()-1);
}


// this solution works with repeated values.
// it looks for the value on both left and right sides of mid.
// i.e. if A[5] = 3, when we check the left side the 1st possible
// magic index is A[3], bc A[4] should be 4, but 4 is not less than 3 (A[5]).
int magicIndex(const vector<int> &vec, int start, int end){
	if (end < start) return -1;

	int mid = (start + end) /2;

	if (mid == vec[mid])
		return mid;

	int index = min(mid-1, vec[mid]);
	int magic = magicIndex(vec, start, index);
	if (magic >= 0)
		return magic;

	index = max(mid+1, vec[mid]);
	magic = magicIndex(vec, index, end);
	return magic;
}

int magicIndex(const vector<int> &vec){
	return magicIndex(vec, 0, vec.size()-1);
}

int main(){
	// vector<int> vec = {6,5,4,3,2,1,0};
	// vector<int> vec = {-40,-20,-1,1,2,3,5,7,9,12,13};
	vector<int> vec = {-10,-5,2,2,2,3,4,8,9,12,13};
	int magicInd = findMagicIndex(vec);
	if (magicInd == -1){
		cout << "Magic Index not found." << endl;
	} else{
		cout << "Magic Index: " << magicInd << endl; 
	} 
	return 0;
}