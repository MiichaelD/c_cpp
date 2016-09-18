/*
Description:	Design the game of Tetris.

Programmer:		Michael Duarte

Date:			Sep 12, 2016.	
*/

#include "PieceQueue.h"
#include "Board.h"
#include <iostream>
int main(){
	PieceQueue que;
	std::shared_ptr<Piece> piece;
	for (int i = 0 ; i < 5; ++i){
	  	piece = que.getNextPiece();
		printMatrix(piece->getMatrix());
		std::cout << std::endl;
	}
	std::cout << std::endl << std::endl;
	Board board;
	board.assignPiece(piece);
	board.print();
	piece->rotate();
	piece->moveDown(4);
	piece->moveRight(3);
	std::cout << std::endl;
	board.print();
	return EXIT_SUCCESS;
}