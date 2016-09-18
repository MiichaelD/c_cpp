/*
Description:	Design the game of Tetris.

Programmer:		Michael Duarte

Date:			Sep 12, 2016.	
*/

#include "Score.h"
#include <cmath> // log2()

Score::Score(uint32_t sco, uint32_t line, uint32_t lev):score(sco),lineCounter(line),level(lev){
	updateLevel();
}

void Score::updateLevel(){
	level = log2(lineCounter);
	if (level < 1)
		level = 1;
}

void Score::incrementLevel(uint32_t delta){
	level += delta;
}

void Score::incrementLines(uint32_t delta){
	lineCounter += delta;
}

void Score::incrementScore(uint32_t delta, bool ignoreLevel){
	score += delta * (ignoreLevel ? 1: level);
}

void Score::onLinesCleared(uint32_t lines){
	//increment line counter
	incrementLines(lines);
	
	//increment score
	uint32_t deltaScore= BASE_SCORE;
	if (lines > 3){
		deltaScore = BASE_SCORE*lines*2;
	} else if (lines > 1){
		deltaScore = BASE_SCORE*(lines+1);
	}
	incrementScore(deltaScore);
	
	// update level
	updateLevel();
}