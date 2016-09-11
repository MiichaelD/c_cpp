/*
	Description:	8.11 Coins: Given an infinite number of quarters, dimes, nickels and
					pennies, write code to calculate the number of ways of representing n
					cents.

	Programmer:		Michael Duarte

	Date:			Sep 9, 2016.	
*/

#include <unordered_map>
#include <iostream>
#include <utility>
#include <string>

using namespace std;

const int TOTAL_DENOM = 4;
const int DENOM[TOTAL_DENOM] = {25, 10, 5, 1};


// <10, 0>
//    <10, 1>
//      <10, 2>
//        <10, 3>
//		  = 1
//        <5, 3>
//        = 1
//        <0, 3>
//        = 1
//      = 3
//      <0, 2>
//        <0, 3>
//        = 1
//      = 1
//   = 4
// = 4
int count (int amount, int index = 0){
		for (int i = 0 ; i <= index; ++i)
		cout << "  ";
	cout << "<"<<amount<<", "<<index<<">: "<<endl;

	int ways;
	if (amount && index < TOTAL_DENOM-1){
		ways = 0;
		for (int i = 0 ; i <= amount; i+= DENOM[index]){
			int remaining = amount - i;
			ways += count(remaining, index+1);
		}
	} else{
		ways = 1;
	}

	for (int i = 0 ; i <= index; ++i)
		cout << "  ";
	cout << "= "<<ways<<endl;

	return ways;
}

// using memoization to avoid repeating calls already processed.
int countWays(int amount, unordered_map<int, unordered_map<int, int>> &memo,int index = 0){
	if (memo[amount][index] > 0){
		// cout << "cached: " << amount << " , " << index << " = " << memo[amount][index] << endl; 
		return memo[amount][index];
	}

	for (int i = 0 ; i < index; ++i)
		cout << "  ";
	cout << "<"<<amount<<", "<<index<<">: "<<endl;

	int ways = 1;
	if (amount && index < TOTAL_DENOM-1){

		ways = 0;
		for (int i = 0 ; i <= amount; i+= DENOM[index]){
			int remaining = amount - i;
			ways += countWays(remaining, memo, index+1);
		}
	}
	for (int i = 0 ; i < index; ++i)
		cout << "  ";
	cout << "= " << ways << endl;

	memo[amount][index] = ways;
	return ways;
}

int countWays(int amount){
	unordered_map<int,unordered_map<int,int>> map;
	return countWays(amount, map);
}

int main(){
	uint32_t cents;
	while(true){
		cin >> cents;

		if (cents == 0)
			break;

		auto ways = countWays(cents);	
		cout << cents << " cents can be represented in " << ways <<
				" different ways" << endl; 
	}
	return 0;
} 