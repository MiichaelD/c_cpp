
/*
	Description:	Given positive integer N, and positive integer prime K,
					find the summation of 1 to N, excluding multiples of K.

	Extensions:		1 -> 2 Primes?
					K1 = 3
					K2 = 5		
					Summation(N) - MultSum(K1) - MultSum(K2) + MultSum(K1*k2)

	Extension2:		Arbitrary Number of Primes? K1, K2, K3, K4, .... Kn
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

uint64_t sumDivisibleBy(int target, int n){
	uint64_t newTarget = target / n;
	// return (newTarget*(newTarget+1)) * n / 2;
	// I divide first so the number keeps being  as small as possible.
	return (newTarget * (newTarget+1) / 2 ) * n;
}


int main(){
	std::ios::sync_with_stdio(false); // http://en.cppreference.com/w/cpp/io/ios_base/sync_with_stdio
	cin.tie(NULL);
	
	uint64_t total  =sumDivisibleBy(1000, 1); // sum from 1 to 1000
	uint64_t divBy3 =  sumDivisibleBy(1000,3); // sum from 3 + 6 + ... 999
	cout << "Sum from 1 to 1000: " << total << ". sum of multiples of 3 from 1 to 1000: " << divBy3 << endl;
	cout << "Solution: " << total - divBy3 << endl;  
	return 0;
}