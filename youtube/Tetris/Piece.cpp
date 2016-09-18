/*
Description:	Design the game of Tetris.

Programmer:		Michael Duarte

Date:			Sep 12, 2016.	
*/

#include "Piece.h"


Piece::Piece(int i):id(i){}

const Matrix<int> &Piece::rotate(bool clockwise){ // some pieces might not need rotation
	rotateMatrix(matrix, clockwise);
	return matrix;
}

void Piece::setPosition(int r, int c){
	row = r;
	col = c;
}

std::pair<int,int> Piece::getPosition(){
	return {row,col};
}

void Piece::centerInBoard(int boardWidth){
	int startCol = (boardWidth - matrixSize)/2;
	setPosition(0,startCol);
}

bool Piece::isPointContained(int r, int c, bool relativeToBoard){
	if (relativeToBoard)
		return r >= row && c >= col && r < (row + matrixSize) && c < (col + matrixSize);
	return r >= 0 && c>=0 && r < matrixSize && c < matrixSize;
}

int Piece::getPoint(int r, int c, bool relativeToBoard){
	if (isPointContained(r,c, relativeToBoard)){
		if (relativeToBoard)
			return matrix[r-row][c-col];
		return matrix[r][c];
	}
	return 0;
}

bool Piece::colidesAtPoint(int r, int c, bool relativeToBoard){
	return getPoint(r,c,relativeToBoard) != 0;
}

int Piece::getBottomRowForCol(int c, bool relativeToBoard){
	if(isPointContained(row,c, relativeToBoard)){
		if (matrix[matrixSize-1][c] == id){
			return relativeToBoard ? row+matrixSize : matrixSize;
		}
		return relativeToBoard ? row + matrixSize-1 : matrixSize-1;
	}
}

bool Piece::moveDown(int i){
	row += i;
	return true;
}

bool Piece::moveLeft(int i){
	col -= i;
	return true;
}
bool Piece::moveRight(int i){
	col += i;
	return true;
}



Stick::Stick(): Piece(1){ 
	definePiece();
}

void Stick::definePiece() {
	matrixSize = 4;
	matrix = createMatrix<int>(matrixSize);

	matrix[0][1] = id;
	matrix[1][1] = id;
	matrix[2][1] = id;
	matrix[3][1] = id;
}


Jay::Jay():Piece(2){
	definePiece();
}

void Jay::definePiece() {
	matrixSize = 3;
	matrix = createMatrix<int>(matrixSize);

	matrix[0][2] = id;
	matrix[1][2] = id;
	matrix[2][2] = id;
	matrix[2][1] = id;
}


El::El():Piece(3){
	definePiece();
}

void El::definePiece() {
	matrixSize = 3;
	matrix = createMatrix<int>(matrixSize);

	matrix[0][0] = id;
	matrix[1][0] = id;
	matrix[2][0] = id;
	matrix[2][1] = id;
}


Square::Square():Piece(4){
	definePiece();
}

void Square::definePiece() {
	matrixSize = 2;
	matrix = createMatrix<int>(matrixSize);

	matrix[0][0] = id;
	matrix[0][1] = id;
	matrix[1][0] = id;
	matrix[1][1] = id;
}

const Matrix<int> &Square::rotate(bool clockwise) {
	return matrix;
}


Ess::Ess():Piece(5){ definePiece(); }

void Ess::definePiece() {
	matrixSize = 3;
	matrix = createMatrix<int>(matrixSize);

	matrix[0][2] = id;
	matrix[0][1] = id;
	matrix[1][1] = id;
	matrix[1][0] = id;
}


Tee::Tee():Piece(6){ definePiece(); }

void Tee::definePiece() {
	matrixSize = 3;
	matrix = createMatrix<int>(matrixSize);

	matrix[1][1] = id;
	matrix[0][0] = id;
	matrix[0][1] = id;
	matrix[0][2] = id;
}


Zeta::Zeta():Piece(7){ definePiece(); }

void Zeta::definePiece() {
	matrixSize = 3;
	matrix = createMatrix<int>(matrixSize);

	matrix[0][0] = id;
	matrix[0][1] = id;
	matrix[1][1] = id;
	matrix[1][2] = id;
}
