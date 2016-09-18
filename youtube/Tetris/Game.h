/*
Description:	Design the game of Tetris.

Programmer:		Michael Duarte

Date:			Sep 12, 2016.	
*/

#ifndef _TETRIS_GAME_CLASS_H_
#define _TETRIS_GAME_CLASS_H_

#include "PieceFactory.h"
#include "PieceQueue.h"
#include "Board.h"
#include "Score.h"

class Game{
private:
	int 
	Board board;
	Score score;
	PieceQueue nextQueue;

public:
	Board(){//:Board(cols,rows){
		initMatrix();
	}

	Board(int w, int h):rows(w), cols(h){
		initMatrix();
	}

	bool tick(){
		bool piecesFell = false;
		for (int r = rows-1; r > 0; --r){
			int emptyCells = cols;
			for (int c = 0; c < cols; ++c){
				if (matrix[r][c]){
					--emptyCells;
				} else {
					if (matrix[r-1][c] > 0 && matrix[r-1][c] < 10){
						matrix[r][c] = matrix[r-1][c];
						piecesFell = true;
					}

				}
			}
			if (emptyCells == cols) break; // there are no more 
		}
	}
};
#endif // _TETRIS_GAME_CLASS_H_