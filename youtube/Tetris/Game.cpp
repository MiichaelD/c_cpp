/*
Description:	Design the game of Tetris.

Programmer:		Michael Duarte

Date:			Sep 12, 2016.	
*/

#include "Game.h"
#include <thread>
#include <chrono>
#include <mutex>

std::thread m_thread;
std::mutex m_mutex;

const uint32_t SLEEP_TIME = 20;
// const size_t TICK_TIME = 1000;

bool Game::isTimeForUpdate(){
	using namespace std::chrono;
	static auto lastUpdate = system_clock::now();//.time_since_epoch());

	auto diff = duration_cast<milliseconds>(system_clock::now() - lastUpdate);

	if (diff.count() >= m_tickTime){
		lastUpdate = system_clock::now();
		return true;
	}
	return false;
}

void Game::run(){
	print();

	while(isGameRunning()){
		std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_TIME));
		
		processCommands();
		
		if (!isTimeForUpdate())
			continue;

		if (!m_board.tick()){
			auto piece = m_piecesQueue.getNext();
			if (!m_board.assignPiece(piece)){
				// no moves available and new piece doesn't fit
				std::cout << "...:GAME OVER:..." << std::endl;
				setGameRunning(false);
			}
		}
		uint32_t cleared = m_board.clearLines();
		if (cleared){
			m_score.onLinesCleared(cleared);
		}
		print();
	}
	std::cout << "\t\t m_thread has finished." << std::endl; 
}

void Game::print(){
	m_board.print();
	m_score.print();
	m_piecesQueue.print();
	std::cout << std::endl << std::endl;
}

void Game::processCommands(){
	while (m_commandsQueue.size()){
		auto command = m_commandsQueue.front();
		switch(command){
			case 'a':
			case 'A':
				m_board.movePieceLeft();
				break;
			case 's':
			case 'S':
				m_board.movePieceDown();
				break;
			case 'd':
			case 'D':
				m_board.movePieceRight();
				break;
			case 'w':
			case 'W':
				m_board.rotatePiece(true);
				break;
			case 'p':
			case 'P':
				pause();
			default:
				std::cout << "Command not found" << std::endl; 
				break;
		}
		m_commandsQueue.pop_front();
	}
}

bool Game::isGameRunning() const{
	std::lock_guard<std::mutex> locker(m_mutex);
	return m_gameRunning;
}

void Game::setGameRunning(bool running){
	std::lock_guard<std::mutex> locker(m_mutex);
	m_gameRunning = running;
}

void Game::toggleGameRunning(){
	std::lock_guard<std::mutex> locker(m_mutex);
	m_gameRunning = !m_gameRunning;
}

void Game::restart(){
	stop();
	start();
}

void Game::start(){
	if (!isGameRunning()){
		// wait for thread to die, if it's still running
		if(m_thread.joinable()) {
			m_thread.join(); 
		}

		// set game running 
		setGameRunning(true);

		// start new thread.
		m_thread = std::thread(&Game::run, this);
		while (m_thread.joinable()){
			char c;
			std::cin >> c;
			m_commandsQueue.push_back(c);
		}

		std::cout << "Game started" << std::endl;
	}
}

void Game::pause(){
	toggleGameRunning();
}

void Game::stop(){
	setGameRunning(false);

	if(m_thread.joinable()) {
		m_thread.join(); 
	}

	m_board.restart();
	m_piecesQueue.restart();
	m_score.restart();
}

void Game::exit(){
	stop();

}

