
/*
	Description:	Print out a matrix in a spiral traversal
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

enum Direction {kRight, kDown, kLeft, kUp};

inline Direction getNextDirection(Direction currentDirection){
	switch(currentDirection){
		case kRight:
			return kDown;
		case kDown:
			return kLeft;
		case kLeft:
			return kUp;
		case kUp:
			return kRight;
	};

	return kRight;
}

void updateIndexes(int &i, int &j, Direction currentDirection){
	switch(currentDirection){
		case kRight:
			++j;
			break;
		case kDown:
			++i;
			break;
		case kLeft:
			--j;
			break;
		case kUp:
			--i;
			break;
	};
}

void printSprially(vector<vector<int>> matrix){
	int numbersToPrint = matrix.size();
	int reps = 1, i = 0, j = -1;
	Direction direction = kRight;

	while (numbersToPrint){
		// cout << "Printing numbers" << endl;
		for (int l = 0 ; l < numbersToPrint; ++l){
			updateIndexes(i,j,direction);
			cout << matrix[i][j];
		}
		cout << endl;
		// cout << "Updating direction" << endl; 
		direction = getNextDirection(direction);

		// cout << "Updating reps" << endl;
		if (++reps % 2 == 0){
			reps = 0;
			--numbersToPrint;
		}
	}
}


int main(){
	std::ios::sync_with_stdio(false); // http://en.cppreference.com/w/cpp/io/ios_base/sync_with_stdio
	cin.tie(NULL);

	vector<vector<int>> matrix = {{1,2,3,4,5,6,7,8},{1,2,3,4,5,6,7,8},{1,2,3,4,5,6,7,8},
						{1,2,3,4,5,6,7,8},{1,2,3,4,5,6,7,8},{1,2,3,4,5,6,7,8},
						{1,2,3,4,5,6,7,8},{1,2,3,4,5,6,7,8}};

	printSprially(matrix);
	
	return 0;
}