/*
Description:	Design the game of Tetris.

Programmer:		Michael Duarte

Date:			Sep 12, 2016.	
*/

#ifndef _TETRIS_BOARD_CLASS_H_
#define _TETRIS_BOARD_CLASS_H_

#include "Piece.h"
#include <memory>

class Board{
private:
	int rows = 20;
	int cols = 10;
	Matrix<int> matrix;
	std::shared_ptr<Piece> curPiece;

	void initMatrix(){
		matrix = createMatrix<int>(rows, cols);
	}

	bool doesPieceFit() const;
	bool importPiece();
	void clearRow(int row);

public:
	Board(){//:Board(cols,rows){
		initMatrix();
	}

	Board(int w, int h):rows(w), cols(h){
		initMatrix();
	}

	int getWidth() const {return cols;}
	int getHeight() const {return rows;}

	std::shared_ptr<Piece> getPiece() {return curPiece;}
	bool assignPiece(std::shared_ptr<Piece> piece);
	bool tick();
	void print();
	void restart();
	uint32_t clearLines();

	bool canMovePieceDown() const;
	bool movePieceDown();
	bool canMovePieceLeft() const;
	bool movePieceLeft();
	bool canMovePieceRight() const;
	bool movePieceRight();

	void rotatePiece(bool clockwise = true);
};
#endif //_TETRIS_BOARD_CLASS_H_