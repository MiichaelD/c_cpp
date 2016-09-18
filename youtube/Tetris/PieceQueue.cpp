/*
Description:	Design the game of Tetris.

Programmer:		Michael Duarte

Date:			Sep 12, 2016.	
*/

#include "PieceQueue.h"
#include "PieceFactory.h"


PieceQueue::PieceQueue(uint32_t numPieces): maxPiecesInQueue(numPieces){
	populate();
}

std::shared_ptr<Piece> PieceQueue::popFront(){
	if (pieceDeque.empty())
		populate();

	auto piece = pieceDeque.front();
	pieceDeque.pop_front();

	return piece;
}

void PieceQueue::populate(){
	while(pieceDeque.size() < maxPiecesInQueue){
		auto piece = PieceFactory::shared().newRandomPiece();
		pieceDeque.push_back(piece);
	}
}


std::shared_ptr<Piece> PieceQueue::getNextPiece(){
	auto piece = popFront(); // consume one piece
	populate(); // push one piece
	return piece;
}