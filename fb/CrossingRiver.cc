/**
 *  Problem:      CrossingRiver.cc
 *  Programmer:   Michael Duarte
 *  Date:         November 14th 2019
 *  Description: There is a character trying to cross a river, but he can only cross it by stepping
 *                on stones otherwise they die x.x.
 *                The character can only do 3 different actions:
 *                - Keeping the same speed.
 *                - Incrementing speed by 1.
 *                - Decrementing speed by 1.
 * 
 *                Given an array of booleans indicating where the stones are, define a function:
 *                    'bool canCross(const vector<bool> &stones);'
 *                
 *                Example: *|_ _  _  _| => [1,0,1,0,0,1,0,0,1]
 *                Character starts before position 0 (represented by *) with initial speed of 0.
 *                Solution: 
 *                1) Increment speed by one (speed = 1): |* _  _  _|
 *                2) Increment speed by one (speed = 2): |_ *  _  _|
 *                3) Increment speed by one (speed = 3): |_ _  *  _|
 *                4) Either 
 *                  4a) Incrementing speed by one (speed = 4): |_ _  _  _|* SOLUTION: CAN CROSS
 *                  4b) Keeping same speed (speed = 3): |_ _  _  *|
 *                    Either:
 *                    4b1) Incrementing speed by one (speed = 4): |_ _  _  _|* SOLUTION: CAN CROSS
 *                    4b2) Keeping same speed (speed = 3): |_ _  _  _|* SOLUTION: CAN CROSS
 *                    4b3) Decrementing speed by one (speed = 2): |_ _  _  _|* SOLUTION: CAN CROSS
 * 
 * 
 *                While debugging my own test case I realized we could use memoization to avoid
 *                repeating the same computation. As follow up question I was asked the big O time
 *                complexity of the basic solution w/o memoization: Nˆ3.
 */

#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <sstream>
#include <unordered_set>

using namespace std;

size_t totalCalls = 0;

struct pair_hash {
	template <class T1, class T2>
	std::size_t operator () (std::pair<T1, T2> const &pair) const {
		std::size_t h1 = std::hash<T1>()(pair.first);
		std::size_t h2 = std::hash<T2>()(pair.second);
		return h1 ^ h2;
	}
};

void printIndent(int indentLevel) {
  for (int i = 0; i < indentLevel; ++i) {
    cout << "\t";
  }
}

bool canCrossMemo(
    const vector<bool> &stones, unordered_set<pair<int,int>, pair_hash> &memo, int index = 0,
    int speed = 1) {
  ++totalCalls;
  if (index >= stones.size()) {
    return true;
  }
  auto idPair = make_pair(index, speed);
  if (!stones[index] || speed <= 0 || memo.find(idPair) != memo.end()) {
    return false;
  }
  if (canCrossMemo(stones, memo, index + speed + 1, speed + 1)        // Increase by 1
      || canCrossMemo(stones, memo, index + speed, speed)             // Keep
      || canCrossMemo(stones, memo,index + speed - 1, speed - 1)) {   // Decrease by 1
    return true;
  }
  memo.insert(idPair);
  return false;
}

bool canCross(const vector<bool> &stones, int index = 0, int speed = 1, int level = 0) {
  // printIndent(level);
  // cout << "Index: " << index << ", Speed: " << speed << endl;
  ++totalCalls;
  if (index >= stones.size()) {
    return true;
  }
  if (!stones[index] || speed <= 0) {
    // printIndent(level);
    // cout << "\tCharacter (died x.x ) || (got stuck)" << endl;
    return false;
  }
  if (canCross(stones, index + speed + 1, speed + 1, level+1)        // Increase by 1
      || canCross(stones, index + speed, speed, level+1)             // Keep
      || canCross(stones, index + speed - 1, speed - 1, level+1)) {  // Decrease by 1
    return true;
  }
  return false;
}

void printTest(const vector<bool> &test) {
  cout << '|';
  for (bool b : test) {
    cout << (b ? '_' : '.');
  }
  cout << '|' << " (Size: " << test.size() << ")";
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  vector<vector<bool>> tests = {
    {1,0,1,0,0,1,0,0,1},
    {1,0,1,0,1,0,0,0,1},
    {1,1,1,1,1,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
  };
  for (const auto &test : tests) {
    totalCalls = 0;
    printTest(test);
    unordered_set<pair<int,int>, pair_hash> memo;
    cout << (canCrossMemo(test, memo) ? " => Can be crossed" : " => Cannot be crossed") << endl;
    // cout << (canCross(test) ? " => Can be crossed" : " => Cannot be crossed") << endl;
    // cout << "Total calls: "<< totalCalls << endl;
  }
  return EXIT_SUCCESS;
}