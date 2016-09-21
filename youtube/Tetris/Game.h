/*
Description:	Design the game of Tetris.

Programmer:		Michael Duarte

Date:			Sep 12, 2016.	
*/

#ifndef _TETRIS_GAME_CLASS_H_
#define _TETRIS_GAME_CLASS_H_

#include "PieceQueue.h"
#include "Board.h"
#include "Score.h"

class Game{
private:
	bool m_gameRunning = false; 
	Board m_board;
	Score m_score;
	PieceQueue m_piecesQueue;
	const size_t m_tickTime = 1000;

	std::deque<char> m_commandsQueue;

	void run();
	void setGameRunning(bool running);
	void toggleGameRunning();
	void processCommands();
	void print();
	bool isTimeForUpdate();

public:
	Game(){//:Board(cols,rows){
		
	}
	bool isGameRunning() const;
	void restart();
	void start();
	void pause();
	void stop();
	void exit();

};
#endif // _TETRIS_GAME_CLASS_H_