/*
	Description:	Group Anagrams: Write a method to sort an array of strings so that all
					the anagrams are next to each other.

	Programmer:		Michael Duarte

	Date:			Sep 11, 2016.	
*/
#include <iostream>
#include <algorithm>
#include <cmath>
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include <set>
#include <algorithm>

using namespace std;


int main() {
	int a[15] = { 1,2,3,7,8,9,12 };
	int b[] = { 3,4,5, 6,10,11 };
	int lenA = 7, lenB = sizeof(b) / sizeof(int);
	printArray(a, lenA);
	printArray(b, lenB);

	mergeSortedArrays(a, lenA, b, lenB);
	printArray(a, lenA+lenB);

	return EXIT_SUCCESS;
}

