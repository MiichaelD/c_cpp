/*
Description:	Design the game of Tetris.

Programmer:		Michael Duarte

Date:			Sep 12, 2016.	
*/


#ifndef _PIECE_QUEUE_CLASS_H_
#define _PIECE_QUEUE_CLASS_H_

#include "Piece.h" 
#include <memory>
#include <deque>

class PieceQueue{
private:
	uint32_t maxPiecesInQueue;
	std::deque<std::shared_ptr<Piece>> pieceDeque;

	std::shared_ptr<Piece> popFront();
	void populate();

public:
	PieceQueue(uint32_t numPieces = 2);
	std::shared_ptr<Piece> getNextPiece();
	const std::deque<std::shared_ptr<Piece>> getQueue() const;
};
#endif // _PIECE_QUEUE_CLASS_H_