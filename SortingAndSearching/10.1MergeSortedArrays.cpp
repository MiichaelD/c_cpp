/*
	Description:	Merge Sorted Arrays: You are given 2 sorted arrays, A and B, where A
					has a large enough buffer at the end to hold B. Write a method to merge
					B into A in sorted order.

	Programmer:		Michael Duarte

	Date:			Aug 5, 2016.	
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>

using namespace std;

void mergeSortedArrays(int arrayA[], int lenA, int arrayB[], int lenB) {
	int lastInd = lenA + lenB -1;
	--lenA;
	--lenB;
	for (; lenB >=0 ; --lastInd) {
    arrayA[lastInd] = (lenA >= 0 && arrayA[lenA] > arrayB[lenB])
        ? arrayA[lenA--]
        : arrayB[lenB--];
	}
	// cout << "Stopped with indexes: last: " << lastInd << ". A: " << lenA << ". B: " << lenB<< endl;  
}

void printArray(int arr[], size_t len) {
	cout << "Array of size  " << len << ": [";
	for (int i = 0; i < len; ++i) {
		cout << arr[i] << ", ";
	}
	cout << "]" << endl;
}

int main() {
	int a[21] = { 0,1,2,3,7,8,9,12,15,16,17,19,20,25,30};
	int b[] = { 3,4,5,6,10,11 };
	int lenA = 15;
	int lenB = sizeof(b) / sizeof(int);
	printArray(a, lenA);
	printArray(b, lenB);

	mergeSortedArrays(a, lenA, b, lenB);
	printArray(a, lenA+lenB);
	return EXIT_SUCCESS;
}

