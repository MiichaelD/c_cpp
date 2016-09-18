/*
Description:	Design the game of Tetris.

Programmer:		Michael Duarte

Date:			Sep 12, 2016.	
*/

#ifndef _TETRIS_SCORE_CLASS_H_
#define _TETRIS_SCORE_CLASS_H_

// sometimes compiler complains if this header is not added:
// error: ‘uint32_t’ was not declared in this scope
// it only happens in this file, maybe bc it has no other std header
#include <cstdint> 


class Score{
private:
	const static uint32_t BASE_SCORE = 100;

	uint32_t score;
	uint32_t level;
	uint32_t lineCounter;

public:
	Score(uint32_t sco = 0, uint32_t line = 0, uint32_t lev = 1);

	uint32_t getScore() {return score; }
	uint32_t getLevel() {return level; }
	uint32_t getLines() {return lineCounter; }

	uint32_t setScore(uint32_t s) {score = s; }
	uint32_t setLevel(uint32_t s) {level = s; }
	uint32_t setLines(uint32_t s) {lineCounter = s; }

	void updateLevel();
	void incrementLevel(uint32_t delta = 1);
	void incrementLines(uint32_t delta = 1);
	void incrementScore(uint32_t delta = BASE_SCORE, bool ignoreLevel= false);

	void onLinesCleared(uint32_t lines);
};
#endif//_TETRIS_SCORE_CLASS_H_