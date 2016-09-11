/*
	Description:	8.2 Robot on a Grid: Imagine a roboy sitting on the upper left corner
					of a grid with r rows and c columns, the robot can only move in two
					directions, right and down, but certain cells are off-limits such that
					the robot cannot stop on them. Design an algorithm to find a path for
					the robot from the top left to the bottom right.

	Programmer:		Michael Duarte

	Date:			Sep 10, 2016.	
*/

#include <unordered_set>
#include <iostream>
#include <utility>
#include <vector>
#include <string>

using namespace std;

const int MAX_NUMBER_OF_COLUMNS = 1024;
int pathChecksCount;

struct Point{
	const int row, column;
	Point(int r, int c):row(r),column(c){}
	// size_t operator()(const Point &p) const noexcept {
	// 	return row * MAX_NUMBER_OF_COLUMNS + column;
	// }
};

//http://stackoverflow.com/questions/17016175/c-unordered-map-using-a-custom-class-type-as-the-key
namespace std{
	template<>
	struct hash<Point>{
		// hash function for unordered_set this will return a 
		// unique number for a point with c < 1024: [0 - 1023]
		size_t operator()(const Point &p) const noexcept{
			return p.row * MAX_NUMBER_OF_COLUMNS + p.column;
		}
	};	
}

bool operator==(const Point &p1, const Point &p2) noexcept{
	return p1.row == p2.row && p1.column == p2.column;
}



void print(const vector<Point> &vec){
	int prevRow = -1;
	if (vec.empty()){
		cout << "No path found." << endl; 
	} else {
		for (const Point &p : vec){
			if (prevRow != p.row){
				if (prevRow != -1)
					cout << endl;
				prevRow = p.row;
			} else {
				cout << ".   ";
			}
			cout << p.row << ", " << p.column;
		}
		cout << endl;
	}
	cout << "Number of points checked: " << pathChecksCount << endl;
}

bool getPath(const vector<vector<bool>> &maze, vector<Point> &path,
	unordered_set<Point> &repeated, int r, int c){
	if (r < 0 || c < 0 ){
		// cout << "\tIlegal point: " << r << ", " << c << endl;
		return false;
	}
	if (!maze[r][c]){
		cout << "\tInvalid Position: " << r << ", " << c << endl;  
		return false;
	}
	cout << "Checking: " << r << ", " << c << endl;  

	Point p(r,c);
	if (repeated.find(p) != repeated.end()){
		return false;
	}
	++pathChecksCount;

	bool atOrigin = ( r == 0 ) && ( c == 0 );
	if (atOrigin || getPath(maze, path, repeated, r-1, c) ||
		getPath(maze, path, repeated, r, c-1)){

		path.push_back(p);
		return true;
	}

	repeated.insert(p); // comment this line to make it slower
	return false;
}

vector<Point> getPath(const vector<vector<bool>> &maze){
	vector<Point> path;
	if (maze.empty() || maze.back().empty()){
		return path;
	}

	int bottom = maze.size() - 1;
	int right = maze.back().size() - 1;
	unordered_set<Point> repeated;
	getPath(maze, path, repeated, bottom, right);
}

int main(){
	pathChecksCount = 0;
	vector<vector<bool>> maze = {{false, true, true, true, true, false},
								{true, true, true, true, false, true},
								{true, true, true, false, true, true},
								{true, true, true, false, true, true},
								{true, true, true, false, true, true},
								{true, true, false, true, true, true},
								{true, true, true, false, true, true},
								{true, true, true, true, false, true},
								{true, true, true, true, true, false},
								{false, true, true, true, true, true}};
	vector<Point> path = getPath(maze);
	print(path);
	return 0;
} 