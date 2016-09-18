/*
Description:	Design the game of Tetris.

Programmer:		Michael Duarte

Date:			Sep 12, 2016.	
*/

#ifndef _PIECE_FACTORY_CLASS_H_
#define _PIECE_FACTORY_CLASS_H_
#include "Piece.h"
#include <memory>


enum PieceType {kStick = 1, kJay, kEl, kSquare, kTee, kEss, kZeta };
const int TOTAL_PIECES = 7;

using SPiece = std::shared_ptr<Piece>;


class PieceFactory{
private:
	PieceFactory();

	PieceFactory(const PieceFactory &other) = delete;
	PieceFactory(const PieceFactory &&other) = delete;
	PieceFactory operator=(const PieceFactory &other) = delete;
	PieceFactory operator=(const PieceFactory &&other) = delete;
	
public:
	static PieceFactory &shared();
	std::shared_ptr<Piece> newPiece(PieceType type);
	std::shared_ptr<Piece> newRandomPiece();
};

#endif //_PIECE_FACTORY_CLASS_H_