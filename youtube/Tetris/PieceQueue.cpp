/*
Description:	Design the game of Tetris.

Programmer:		Michael Duarte

Date:			Sep 12, 2016.	
*/

#include "PieceQueue.h"
#include "PieceFactory.h"
#include <iostream>

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

void PieceQueue::restart(){
	pieceDeque.clear();
	populate();
}

void PieceQueue::print() const {
	std::cout << "Piece Queue:";
	for (auto it = pieceDeque.begin(); it != pieceDeque.end(); ++it){
		std::cout << " " << (*it)->getId();
	} 
	std::cout << std::endl;
}

void PieceQueue::populate(){
	while(pieceDeque.size() < maxPiecesInQueue){
		auto piece = PieceFactory::shared().newRandomPiece();
		pieceDeque.push_back(piece);
	}
}

std::shared_ptr<Piece> PieceQueue::getNext(){
	auto piece = popFront(); // consume one piece
	populate(); // push one piece
	return piece;
}