
/*
	Description:	Return the percentage of license plates that consist
					only of 3 alphanumeric values from all possible license plates
					Eg. of valid license plates
						123123
						112233
						111123
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

uint64_t memo[32];

uint64_t factorialMemo(int n){
	if (n <= 1)
		return 1;

	if (memo[n] == 0)
		memo[n] = n * factorialMemo(n-1);

	cout << "\tfactorial of " << n << " = " << memo[n] << endl; 
	return memo[n];
}

uint64_t factorial(int n, int lastFactor = 0){
	if (n <= 1 || lastFactor == n)
		return 1;

	uint64_t res = n * factorial(n-1, lastFactor);
	// cout << "\tfactorial of " << n << " = " << res << endl; 
	return res;
}

uint64_t getCombination(int n, int r){
	uint64_t nFact = factorial(n, n - r);
	uint64_t rFact = factorial(r);
	return nFact / rFact;
}

uint64_t getPermutation(int n, int k){
	uint64_t nFact = factorial(n, n - k);
	return nFact;
}

int main(){
	std::ios::sync_with_stdio(false); // http://en.cppreference.com/w/cpp/io/ios_base/sync_with_stdio
	cin.tie(NULL);

	const uint64_t TOTAL_PLATE_COMBINATIONS = 2176782336;
	const int ALPHANUM_CHARS = 26 + 10;
	const int DIFFERENT_CHARS = 3;
	const int PLACES_IN_LICENSE_PLATE = 6;

	uint64_t picking3DifCharsFrom36 = getCombination(ALPHANUM_CHARS, DIFFERENT_CHARS);
	cout << "Picking 3 chars from 36 possible 36C3: " << picking3DifCharsFrom36 << endl;
	uint64_t waysToArrange3CharsIn6Spaces = getPermutation(PLACES_IN_LICENSE_PLATE,DIFFERENT_CHARS);
	cout << "Ways to organize 3 chars in 6 spaces 6P3: " << waysToArrange3CharsIn6Spaces << endl;
	uint64_t totalCombination = picking3DifCharsFrom36 * waysToArrange3CharsIn6Spaces;
	cout << "TotalCombination (36C3)*(6P3): " << totalCombination << endl; 

	cout << "Total Plates 36^6: " << TOTAL_PLATE_COMBINATIONS <<endl;
	cout << "Percentage: " << (static_cast<double>(totalCombination)/TOTAL_PLATE_COMBINATIONS)*100 << "%" << endl; 
	// cout << "Combination 15C4: " << getCombination(15,4) << endl;
	// cout << "Permutation 15P4: " << getPermutation(15,4) << endl;
	
	return 0;
}