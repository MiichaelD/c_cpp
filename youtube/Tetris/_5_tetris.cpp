/*
Description:	Design the game of Tetris.

Programmer:		Michael Duarte

Date:			Sep 12, 2016.	
*/

#include "PieceQueue.h"
#include "Board.h"
int main(){
	PieceQueue que;
	std::shared_ptr<Piece> piece;
	for (int i = 0 ; i < 5; ++i){
	  	piece = que.getNextPiece();
		printMatrix(piece->getMatrix());
		std::cout << std::endl;
	}
	std::cout << std::endl << std::endl;

	Board board(10,10);
	board.assignPiece(piece);
	piece->rotate();
	board.print();
	for (int i = 0; i < 30 && board.canMovePieceDown(); ++ i){
	// while(board.canMovePieceDown()){
		if (board.canMovePieceRight())
			board.movePieceRight();
		std::cout << std::endl;
		if (!board.tick()){
			if (!board.assignPiece(que.getNextPiece())){
				std::cout << i <<") New Piece doesn't fit: Game Over" << std::endl; 
				board.print();
				break;
			}

		}
		board.print();
	}
	return EXIT_SUCCESS;
}