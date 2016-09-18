/*
Description:	Design the game of Tetris.

Programmer:		Michael Duarte

Date:			Sep 12, 2016.	
*/

#ifndef _TETRIS_BOARD_CLASS_H_
#define _TETRIS_BOARD_CLASS_H_
#include <iostream>


class Board{
private:
	int rows = 20;
	int cols = 10;
	Matrix<int> matrix;
	std::shared_ptr<Piece> curPiece;

	void initMatrix(){
		matrix = createMatrix<int>(rows, cols);
	}

	int getWidth() {return cols;}
	int getHeight() {return rows;}

public:
	Board(){//:Board(cols,rows){
		initMatrix();
	}

	Board(int w, int h):rows(w), cols(h){
		initMatrix();
	}

	void assignPiece(std::shared_ptr<Piece> piece){
		curPiece = piece;
		piece->centerInBoard(cols);

	}

	void print(){
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

	bool canMovePieceDown(){
		if (curPiece){
			if (curPiece.)
		}
	}

	bool tick(){
		
	}
};
#endif //_TETRIS_BOARD_CLASS_H_