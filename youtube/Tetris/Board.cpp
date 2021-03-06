/*
Description:	Design the game of Tetris.

Programmer:		Michael Duarte

Date:			Sep 12, 2016.	
*/

#include "Board.h"
#include <iostream>
#include <algorithm>
#include <climits>
#include <stdexcept>

bool Board::assignPiece(std::shared_ptr<Piece> piece){
	curPiece = piece;
	piece->centerInBoard(cols);
	if (!doesPieceFit()){
		curPiece = nullptr;
		return false;
	}
	return true;
}

bool Board::doesPieceFit() const {
	auto &mat = curPiece->getMatrix();
	int r = curPiece->getRow();
	int c = curPiece->getCol();
	int rowEnd = std::min(rows, curPiece->getSize()+r);
	int colEnd = std::min(cols, curPiece->getSize()+c);

	if (c < 0) c = 0;

	for (int i = r; i < rowEnd; ++i){
		for (int j = c; j < colEnd; ++j){
			if (matrix[i][j] && mat[i-r][j-c])
				return false;
		}
	}
	return true;
}

bool Board::canMovePieceDown() const {
	if (curPiece){
		// 1) Polling column by column
		std::pair<int,int> origin = curPiece->getPosition();
		int rowSize = curPiece->getSize();
		for (int c = 0 ; c < rowSize; ++c){
			int col = origin.second + c;
			if (col < 0 || col >= cols)
				continue; // we don't care about this column
			int row = curPiece->getBottomForCol(col);
			// std::cout << row << ", "<< col << "\t";
			if (row == INT_MIN) // we don't care about this column
				continue;
			if (row >= rows || matrix[row][col]){
				// std::cout << ". Unacceptable" <<std::endl;
				return false;
			}
		}
		// std::cout << std::endl;

		// 2) getting all bottom points at once
		// auto bottom = curPiece->getBottom();
		// auto column = curPiece->getCol();
		// for (int c = 0 ; c < bottom.size(); ++c){
		// 	int col = column + c;
		// 	int row = bottom[c];
		// 	// std::cout << "\tpos: r=" << row << ", c=" << col;
		// 	if (row >= rows || col >= cols || matrix[row][col]){
		// 		std::cout << std::endl;
		// 		return false;
		// 	}
		// }

		return true;
	}
	return false;
}

bool Board::movePieceDown(){
	if (canMovePieceDown()){
		curPiece->moveDown();
		return true;
	}
	return false;
}

bool Board::canMovePieceLeft() const {
	if (curPiece){
		std::pair<int,int> origin = curPiece->getPosition();
		int colSize = curPiece->getSize();
		for (int r = 0 ; r < colSize; ++r){
			int row = origin.first + r;
			if (row >= rows)
				break; // we don't care about this nor any next row
			int col = curPiece->getLeftForRow(row);
			// std::cout << row << ", "<< col << "\t";
			if (col == INT_MAX) // we don't care about this row
				continue;
			if (col < 0 || col >= cols || matrix[row][col]){
				// std::cout << ". Unacceptable" <<std::endl;
				return false;
			}
		}
		// std::cout << std::endl;
		return true;
	}
	return false;
}

bool Board::movePieceLeft(){
	if (canMovePieceLeft()){
		curPiece->moveLeft();
		return true;
	}
	return false;
}

bool Board::canMovePieceRight() const {
	if (curPiece){
		std::pair<int,int> origin = curPiece->getPosition();
		int colSize = curPiece->getSize();
		for (int r = 0 ; r < colSize; ++r){
			int row = origin.first + r;
			if (row >= rows)
				break; // we don't care about this nor any next row
			int col = curPiece->getRightForRow(row);
			// std::cout << row << ", "<< col << "\t";
			if (col == INT_MIN) // we don't care about this row
				continue;
			if (col < 0 || col >= cols || matrix[row][col]){
				// std::cout << ". Unacceptable" <<std::endl;
				return false;
			}
		}
		// std::cout << std::endl;
		return true;
	}
	return false;
}

bool Board::movePieceRight(){
	if (canMovePieceRight()){
		curPiece->moveRight();
		return true;
	}
	return false;
}

void Board::rotatePiece(bool clockwise){
	if(curPiece){
		// if the piece loses some cells when rotating (i.e. some cells are
		// left out of the board), don't rotate
		int row = curPiece->getRow();
		int size = curPiece->getSize();
		int lastCell = row + size;
		if (lastCell <= rows){
			curPiece->rotate(clockwise);

			// fix for cases where the piece is out of board bounds
			// when we rotate them they should be moved to be fully
			// inside of board's boundaries.
			int col = curPiece->getCol();
			if (col < 0){
				curPiece->moveRight(-col);
			} else {
				lastCell = col + size;
				if (lastCell > cols){
					curPiece->moveLeft(lastCell - cols);
				}
			}

			// if the piece colides with other cells after being rotated, revert.
			if (!doesPieceFit()){
				curPiece->rotate(!clockwise);
			}

		}
	}
}

bool Board::importPiece(){
	if (curPiece){
		auto &mat = curPiece->getMatrix();
		int r = curPiece->getRow();
		int c = curPiece->getCol();
		int rowEnd = std::min(rows, curPiece->getSize()+r);
		int colEnd = std::min(cols, curPiece->getSize()+c);

		for (int i = r; i < rowEnd; ++i){
			for (int j = (c < 0 ? 0 : c); j < colEnd; ++j){
				if (mat[i-r][j-c]){ // piece's cell is occupied
					if (matrix[i][j]){ // board's cell is occupied
						throw std::runtime_error("Importing a piece's cell to an occupied cell in board");
					}
					matrix[i][j] = mat[i-r][j-c];
				}
			}
		}
		return true;
	}
	return false;
}

bool Board::tick(){
	bool result = true;

	if (!movePieceDown()){
		if (importPiece()){
			curPiece = nullptr;
		} else {
			// we cannot move down and have no piece
			result = false;
		}
	}
	return result;
}

void Board::clearRow(int row){
	int r = row;
	int cells = 0;
	for (; r > 0; --r){
		cells = 0;
		for (int c = 0; c < cols ; ++c){
			matrix[r][c] = matrix[r-1][c];
			if (matrix[r][c])
				++cells;
		}

		if (cells == 0)
			break;
	}

	// if we have cells in the first row, fill them with 0s
	if (r == 0 && cells > 0){
		for (int c = 0 ; c < cols; ++c)
			matrix[r][c] = 0;
	}
}

uint32_t Board::clearLines(){
	uint32_t clearedLines = 0;
	for (int r = rows - 1; r >= 0; --r){
		int cells = 0;
		for (int c = 0; c < cols ; ++c){
			if (matrix[r][c])
				++cells;
		}
		if (cells == cols){
			++clearedLines;
			clearRow(r);
			std::cout << "Clearing row: " << r << std::endl;
			++r; // repeat this line
		} else if (cells == 0){
			break;
		}
	}



	return clearedLines;
}

void Board::print(){
	using namespace std;
	for (int r = 0; r < rows; ++r){
		for (int c = 0; c < cols; ++c){
			cout << '|';
			if (matrix[r][c]){
				cout << matrix[r][c];
			} else if (curPiece && curPiece->isPointContained(r,c)){
				cout << curPiece->getPoint(r,c);
			} else {
				cout << ' ';
			}
			cout << '|';
		}
		cout << endl;
	}
}

void Board::restart(){
	// clear board matrix
	for (int r = 0 ; r < rows; ++r){
		for (int c = 0; c < cols; ++c){
			matrix[r][c] = 0;
		}
	}

	// clear piece
	curPiece = nullptr;
}