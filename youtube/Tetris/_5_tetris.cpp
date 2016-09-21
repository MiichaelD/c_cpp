/*
Description:	Design the game of Tetris.

Programmer:		Michael Duarte

Date:			Sep 12, 2016.	
*/

#include "Game.h"

// int test(){
// 	PieceQueue que;
// 	std::shared_ptr<Piece> piece;
// 	for (int i = 0 ; i < 5; ++i){
// 	  	piece = que.getNext();
// 		printMatrix(piece->getMatrix());
// 		std::cout << std::endl;
// 	}
// 	std::cout << std::endl << std::endl;

// 	Board board(10,10);
// 	board.assignPiece(piece);
// 	piece->rotate();
// 	board.print();
// 	for (int i = 0; i < 30 && board.canMovePieceDown(); ++ i){
// 	// while(board.canMovePieceDown()){
// 		if (board.canMovePieceRight())
// 			board.movePieceRight();
// 		std::cout << std::endl;
// 		if (!board.tick()){
// 			if (!board.assignPiece(que.getNext())){
// 				std::cout << i <<") New Piece doesn't fit: Game Over" << std::endl; 
// 				board.print();
// 				break;
// 			}

// 		}
// 		board.print();
// 	}
// 	return EXIT_SUCCESS;
// }

int main(){
	Game game;
	game.start();
	do {
		std::cout << "Main finished. Do you want to play again?? y/n" << std::endl; 
		char c;
		std::cin >> c;
		if (c == 'y' || c == 'Y'){
			game.restart();
		} else {
			break;
		}
	} while (true);

	return EXIT_SUCCESS;
}
