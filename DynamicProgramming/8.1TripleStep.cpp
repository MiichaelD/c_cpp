/*
	Description:	8.1 Triple Step: A Child is running up a staircase with n steps and
					can hop either 1 step, 2 steps or 3 steps at a time. Implement a method
					to count how many possible ways a child can run up the stairs.

	Programmer:		Michael Duarte

	Date:			Sep 7, 2016.	
*/

#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

void printVector(const vector<int> &vec){
	auto it = vec.begin();
	if (it != vec.end()){
		cout << *it;
		for (++it; it != vec.end(); ++it){
			cout << ' ' << *it;
		}
		cout << endl;
	}
}

// 3 {}
//	2 {1}
//    1 {1 1}
//      0 {1 1 1}
//    0 {1 2}
//  1 {2}
//    0 {2 1}
//  0 {3}


// it actually prints the ways
uint32_t howManyWays(int steps, vector<int> &vec, bool print){
	if (steps == 0){
		if (print)
			printVector(vec);
		return vec.size() ? 1 : 0;
	}

	int total = 0;
	for (int i = 1 ; i <= 3; ++i){
		int remainingSteps = steps - i;
		if (remainingSteps < 0){
			break;
		} 
		vec.push_back(i);
		total += howManyWays(remainingSteps, vec, print);
		vec.pop_back();
	}
	return total;
}

uint32_t howManyWays(int steps, bool print = true){
	vector<int> vec;
	return howManyWays(steps, vec, print);
}

// it could be better
int countWays(int steps){
	if (steps < 0)
		return 0;

	if(steps == 0)
		return 1;

	return countWays(steps-1) + countWays(steps-2) + countWays(steps-3); 
}

//fastest!
int countWaysMemo(int steps, int clear = true){
	static unordered_map<int, int> map;
	if (clear)
		map.clear();

	if (steps < 0)
		return 0;

	if(steps == 0)
		return 1;

	if (map.find(steps) != map.end()){
		return map[steps];
	}

	map[steps] = countWaysMemo(steps-1, false) + countWaysMemo(steps-2, false) +
				 countWaysMemo(steps-3, false); 

	return map[steps];
}

int main(){
	int steps, ways;
	for (;;){
		cin >> steps;
		if (steps == 0)
			break;

		// ways = howManyWays(abs(steps), steps < 0);
		// ways = countWays(abs(steps));
		ways = countWaysMemo(abs(steps));
		cout << "For " << abs(steps) << " steps: there are " << ways << " total ways." << endl;
	}
	return 0;
}