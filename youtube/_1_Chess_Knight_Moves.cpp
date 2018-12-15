/*
	Description:	Given 2 coordinates, start and end, check if a end is a valid next
					move from start from a knight is valid.

	Continuation:	Given 2 coordinates, start and end, return the shortest path between
					them by only using Knight's valid moves. 

	Programmer:		Michael Duarte

	Date:			Sep 12, 2016.	
*/

#include <unordered_set>
#include <unordered_map>
#include <iostream>
#include <sstream>
#include <vector>
#include <deque>
#include <cmath>

using namespace std;

const int BOARD_SIZE = 30;


struct Coordinate{
	int row = - 1;
	int col = - 1;
	
	Coordinate() = default;

	Coordinate(int r, int c):row(r),col(c){}
	
	int getRowDiff(const Coordinate &coord) const {
		return row - coord.row;
	}

	int getColDiff(const Coordinate &coord) const {
		return col - coord.col;
	}

	bool isValid() const {
		return row >= 0 && row < BOARD_SIZE && col >=0 && col < BOARD_SIZE;
	}

	bool isNextStepValid(const Coordinate &nextCoord) const{
		if (!nextCoord.isValid()) return false;
		int rowDiff = abs(getRowDiff(nextCoord));
		int colDiff = abs(getColDiff(nextCoord));

		return (rowDiff == 2 && colDiff == 1) || (rowDiff == 1 && colDiff == 2);
	}

	bool isSame(const Coordinate &coord) const {
		return row == coord.row && col == coord.col;
	}

	string toString() const {
		stringstream ss;
		ss << '[' << row << ", " << col << ']';
		return ss.str();
	}
};

//http://stackoverflow.com/questions/17016175/c-unordered-map-using-a-custom-class-type-as-the-key
namespace std{
	template<>
	struct hash<Coordinate>{
		// hash function for unordered_set this will return a 
		// unique number for a point with col < 8: [0 - 7]
		size_t operator()(const Coordinate &c) const noexcept{
			return c.row * BOARD_SIZE + c.col;
		}
	};	
}

bool operator==(const Coordinate &c1, const Coordinate &c2) noexcept{
	return c1.isSame(c2);
}


bool isValid(const Coordinate &start, const Coordinate &end){
	return start.isValid() && start.isNextStepValid(end);
}

void addValidMovesToQueue(const Coordinate &start, deque<Coordinate> &moves){
	Coordinate coord;
	for (int i = 0 ; i < 4; ++i){
			if (i == 0 || i == 3){
				coord.row = start.row + (i ? 2 : -2);
			} else {
				coord.row = start.row + (i % 2 ? -1: 1);
			}

		for (int j = 0; j < 2; ++j){
			if (i == 0 || i == 3){
				coord.col = start.col + (j ? 1 : -1);
			} else {
				coord.col = start.col + (j ? 2 : -2);
			}

			// cout << coord.toString() << ". is Valid? " << (coord.isValid() ? "Yes" : "No" ) << endl;
			if (coord.isValid()){
				moves.push_back(coord);
			}
		}
	}
}

deque<Coordinate> getValidMoves(const Coordinate &start){
	deque<Coordinate> moves;
	addValidMovesToQueue(start, moves);
	return moves;
}

void normalizePath(vector<Coordinate> &path){
	cout << "Normalizing path found ... from " << path.size() << " to: ";
	vector<Coordinate> normalized;
	Coordinate *aux = &path.back();
	// cout << "Aux: " << aux->toString() << endl;
	for (auto it = path.rbegin(); it < path.rend(); ++it){
		if (isValid(*aux, *it) || aux->isSame(*it)){
			// cout << it->toString() << " is next" << endl;
			aux = &(*it); // update aux to reference previous valid move
			normalized.push_back(*aux);
		}
	}
	cout << normalized.size() << ". Finished." << endl; 
	path = normalized;
}

vector<Coordinate> getShortestPath(const Coordinate &start, const Coordinate &end){
	vector<Coordinate> path;
	unordered_set<Coordinate> set;
	deque<Coordinate> moveQueue;
	moveQueue.push_front(start);
	int index = 0;

	while(!moveQueue.empty()){
		const Coordinate &coord = moveQueue.front();
		// cout << "Checking " << coord.toString() << ": "; 
		if (set.find(coord) != set.end()){
			// cout << "already processed, skipping." << endl;
			moveQueue.pop_front();
			continue;
		}
		set.insert(coord); // mark as visited
		path.push_back(coord); // add coord to path

		if (coord.isSame(end)){ // check if we found the target coordinate
			// cout << "is same as end: " << end.toString() << endl; 
			normalizePath(path);
			return path;
		}

		addValidMovesToQueue(coord, moveQueue);
		moveQueue.pop_front();
		// cout << endl;
	}
	return path;
}

void print(const vector<Coordinate> &path){
	cout << "Path size: " << path.size() << ". coordinates:" ;
	for (auto it = path.rbegin(); it < path.rend(); it++){
		cout << " " << it->toString();
	}
	cout << endl;
}

int main(){
	// Coordinate start(4, 4), end(4, 5); // 4
	// Coordinate start(0, 0), end(7, 7); // 7
	// Coordinate start(4, 3), end(0, 0); // 4
	// Coordinate start(0, 0), end(29, 29); // 21
	Coordinate start(4, 4), end(5, 5); // 3
	auto path = getShortestPath(start, end);
	print(path);
	return EXIT_SUCCESS;
}