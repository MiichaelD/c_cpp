/*
Description:	Design the game of Tetris.

Programmer:		Michael Duarte

Date:			Sep 12, 2016.	
*/
#ifndef _PIECE_CLASS_H_
#define _PIECE_CLASS_H_
#include "Matrix.h"
#include <utility>

class Piece{
protected:
	int id;
	Matrix<int> matrix;
	int matrixSize = 0;
	int row = 0;
	int col = 0;

	Piece(int i);
	
public:
	virtual ~Piece() {}

	virtual const Matrix<int> &rotate(bool clockwise = true); // some pieces might not need rotation
	const Matrix<int> &getMatrix() const { return matrix; }
	int getSize() const { return matrixSize; }
	int getId() const {return id;}
	int getRow() const {return row;}
	int getCol() const {return col;}

	void setPosition(int r, int c);
	std::pair<int,int> getPosition();
	void centerInBoard(int boardWidth);
	bool isPointContained(int r, int c, bool relativeToBoard = true);
	int  getPoint(int r, int c, bool relativeToBoard = true);
	bool colidesAtPoint(int r, int c, bool relativeToBoard = true);
	int  getBottomRowForCol(int c, bool relativeToBoard = true);
	bool moveDown(int i = 1);
	bool moveLeft(int i = 1);
	bool moveRight(int i = 1);
};

class Stick : public Piece{
public:
	Stick();
	void definePiece();
};

class Jay : public Piece{
public:
	Jay();
	void definePiece();
};

class El : public Piece{
public:
	El();
	void definePiece();
};

class Square : public Piece{
public:
	Square();
	void definePiece();
	virtual const Matrix<int> &rotate(bool clockwise = true) override;
};

class Ess : public Piece{
public:
	Ess();
	void definePiece();
};

class Tee : public Piece{ // trapeze
public:
	Tee();
	void definePiece();
};

class Zeta : public Piece{
public:
	Zeta();
	void definePiece();
};
#endif //_PIECE_CLASS_H_