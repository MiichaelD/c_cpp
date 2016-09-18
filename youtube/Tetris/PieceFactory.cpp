/*
Description:	Design the game of Tetris.

Programmer:		Michael Duarte

Date:			Sep 12, 2016.	
*/

#include "PieceFactory.h"
#include <ctime>


PieceFactory::PieceFactory(){
  	srand (time(NULL)); // initialize random seed.
}

PieceFactory &PieceFactory::shared(){
	static PieceFactory factory;
	return factory;
}

std::shared_ptr<Piece> PieceFactory::newPiece(PieceType type){
	switch(type){
		case kStick:
			return std::make_shared<Stick>();
		case kJay:
			return std::make_shared<Jay>();
		case kEl:
			return std::make_shared<El>();
		case kSquare:
			return std::make_shared<Square>();
		case kTee:
			return std::make_shared<Tee>();
		case kEss:
			return std::make_shared<Ess>();
		case kZeta:
			return std::make_shared<Zeta>();
		default:
			break;
	}
	return std::shared_ptr<Piece>(nullptr);
}

std::shared_ptr<Piece> PieceFactory::newRandomPiece(){
  	PieceType type = static_cast<PieceType>(1 + (rand() % TOTAL_PIECES));
  	return newPiece(type);
}