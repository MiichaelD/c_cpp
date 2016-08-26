// PairwiseSwap: Write a program to swap odd and even bits in a n integer
// with as few instructions as possible (e.g., bit 0 and bit 1 are swapped,
// bit 2 and bit 3 are swapped, and so on).

// #include "stdafx.h"
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

int swapOddEvenBits(int x){
	// if we cared about sign bit to become 0 we could use '>>>'
	// the logial right shift instead of the aritmetic shift.
	int evenToOdd = (x & 0xaaaaaaaa) >> 1; 
	int oddToEven = (x & 0x55555555) << 1;
	return evenToOdd | oddToEven;
}

int main() {
	cout << swapOddEvenBits( 1042 ) << " swapped ->  " << swapOddEvenBits( 2081 ) << endl;
	return EXIT_SUCCESS;
}

