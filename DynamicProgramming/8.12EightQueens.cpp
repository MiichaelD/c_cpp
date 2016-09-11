/*
	Description:	8.12 Eight Queens: Write an algorithm to print all ways of arranging 
					eight queens on a 8x8 chess board so that none of them share the same
					row, column or diagonal. In this case "diagonal" means all diagonals
					not just the 2 that bisect the board.

	Programmer:		Michael Duarte

	Date:			Sep 9, 2016.	
*/

#include <vector>
#include <iostream>
#include <utility>
#include <string>

using namespace std;

const int GRID_SIZE = 8;

void print(const vector<int> &vec){
	cout << "vec: ["; 
	for (int i : vec){
		cout << i << " ";
	}
	cout << ']' << endl;
}


void print(const vector<vector<int>> &vec){
	for (const vector<int> &v : vec){
		print(v);
	}
}

// Check if (row1, column1) is a valid spot for a queen by checking if there i 
// a queen in the same column or diagonal. We don't need to check it for queens
// in the same row because the calling placeQueen only attempts to place one 
// queen at a time. We know this row is empty.
bool checkValid(const vector<int> &columns, int row1, int column1){
	for (int row2 = 0; row2 < row1; ++ row2){
		int column2 = columns[row2];

		// check if rows have a queen in the same column
		if (column1 == column2){
			return false;
		}

		// Check diagonals: if the distance between columns equals the distance
		// between the rows, they're in teh same diagonal.
		int columnDistance = abs(column2 - column1);

		// row2 > row1, so no need for abs
		int rowDistance = row1 - row2;
		if (columnDistance == rowDistance)
			return false;
	}
	return true;
}

void placeQueens(vector<vector<int>> &results, vector<int> &columns, int row = 0){
	if (row == GRID_SIZE){
		results.push_back(columns);
	} else {
		for (int col = 0 ; col < GRID_SIZE; ++col){
			if (checkValid(columns, row, col)){
				columns[row] = col; // place queen
				// cout << "\t"; print(columns); 
				placeQueens(results, columns, row + 1 );
			}
		}
	}
}

int main(){
	vector<vector<int>> results;
	vector<int> columns(8);
	placeQueens(results, columns);
	print(results);
	return 0;
} 