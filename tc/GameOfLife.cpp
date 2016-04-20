// https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life

#include <iostream>
#include <memory>
#include <unistd.h> // usleep(microseconds);

using namespace std;

const size_t MAX_GRID_SIZE = 100;
const size_t SLEEP_MICROSECS = 500000;

class Cell{
private:
    bool m_futureState = false;
    bool m_currentState = false;
    
public:
    void commit(){
        m_currentState = m_futureState;
    }
    
    void setAlive(bool alive, bool commit = false){
        m_futureState = alive;
        if (commit)
            m_currentState = alive;
    }
    
    inline bool isAlive() const {
        return m_currentState;
    }
    
    inline int8_t isAliveNum() const {
        return isAlive() ? 1 : 0;
    }
    
    inline bool willBeAlive() const {
        return m_futureState;
    }
    
    inline int8_t willBeAliveNum() const {
        return willBeAlive() ? 1 : 0;
    }
};

class GameOfLife{
private:
    size_t m_maxX;
    size_t m_maxY;
    size_t m_maxTicks;
    bool m_run = false;
    
    std::unique_ptr<Cell> m_board[MAX_GRID_SIZE][MAX_GRID_SIZE];
    
    size_t getPreviousX(size_t x) const {
        return x == 0 ? m_maxX-1 : x-1;
    }
    
    size_t getPreviousY(size_t y) const {
        return y == 0 ? m_maxY-1 : y-1;
    }
    
    size_t getNextX(size_t x) const {
        return x == m_maxX-1 ? 0 : x+1;
    }
    
    size_t getNextY(size_t y) const {
        return y == m_maxY-1 ? 0 : y+1;
    }
    
    int getLiveNeighborsCount(size_t f, size_t c) const{
        int liveNeighbors = 0;
        size_t prevF = getPreviousX(f);
        size_t prevC = getPreviousY(c);
        liveNeighbors += m_board[prevF][c]->isAliveNum(); // UP
        liveNeighbors += m_board[prevF][prevC]->isAliveNum(); // UP LEFT
        liveNeighbors += m_board[f][prevC]->isAliveNum(); // LEFT
        
        size_t nextF = getNextX(f);
        size_t nextC = getNextY(c);
        liveNeighbors += m_board[nextF][prevC]->isAliveNum(); // DOWN LEFT
        liveNeighbors += m_board[nextF][c]->isAliveNum(); // DOWN
        liveNeighbors += m_board[nextF][nextC]->isAliveNum(); // DOWN RIGHT
        liveNeighbors += m_board[f][nextC]->isAliveNum(); // RIGHT
        liveNeighbors += m_board[prevF][nextC]->isAliveNum(); // UP RIGHT
        return liveNeighbors;
    }
    
    size_t tick(){
        size_t aliveCells = 0;
        for (size_t f= 0; f < m_maxX; ++f){
            for (size_t c= 0; c < m_maxY; ++c){
                int liveNeighbors = getLiveNeighborsCount(f, c);
                Cell *currentCell = m_board[f][c].get();
                
                switch(liveNeighbors) {
                        // if 2 or 3, stay as they are.
                    case 2:
                        aliveCells += currentCell->isAliveNum();
                        break;
                        // if exactly 3 become alive by repoduction
                    case 3:
                        currentCell->setAlive(true);
                        ++aliveCells;
                        break;
                        
                        // if < 2 die by underpopulation
                        // if > 3 die by overpopulation
                    default:
                        currentCell->setAlive(false);
                        break;
                        
                }
            }
        }
        return aliveCells;
    }
    
    void print(){
        for (size_t f= 0; f < m_maxX; ++f){
            for (size_t c= 0; c < m_maxY; ++c){
                Cell *currentCell = m_board[f][c].get();
                currentCell->commit();
                cout << (currentCell->isAlive() ? '#' : ' ');
                
            }
            cout << endl;
        }
        cout << endl;
        usleep(SLEEP_MICROSECS);
    }
    
public:
    GameOfLife(size_t sizeX, size_t sizeY, size_t ticks = 10)
    :m_maxX(sizeX), m_maxY(sizeY), m_maxTicks(ticks){
        for (size_t f= 0; f < m_maxX ; ++f){
            for (size_t c= 0; c < m_maxY ; ++c){
                m_board[f][c].reset(new Cell);
            }
        }
    }
    
    void setAlive(size_t f, size_t c, bool alive = true){
        m_board[f][c]->setAlive(alive, true);
    }
    
    
    void start() {
        m_run = true;
        size_t ticks = 0;
        cout << "Starting with: " << endl;
        print();
        while(m_run){
            ++ticks;
            cout << "Generation: # " << ticks << ": \t Alive: ";
            if (ticks == m_maxTicks)
                stop();
            
            size_t aliveCells = tick();
            cout << aliveCells << endl;
            print();
        }
    }
    
    void stop() {
        m_run = false;
    }
    
};

void setStillLifes(GameOfLife &life){
    //Block
    life.setAlive(1, 1);
    life.setAlive(1, 2);
    life.setAlive(2, 1);
    life.setAlive(2, 2);
    
    //Beehive
    life.setAlive(5, 4);
    life.setAlive(4, 5);
    life.setAlive(4, 6);
    life.setAlive(5, 7);
    life.setAlive(6, 6);
    life.setAlive(6, 5);

}

void setBlinker(GameOfLife &life){
    life.setAlive(0,1);
    life.setAlive(1,1);
    life.setAlive(2,1);
}

void setPulsar(GameOfLife &life){
    int lines[] = {2, 7, 9, 14};
    int lines2[] = {4, 5, 6, 10, 11, 12};
    for (int x : lines){
        for (int y : lines2){
            life.setAlive(x, y);
            life.setAlive(y, x);
        }
    }
}

void setGlider(GameOfLife &life){
    //Glider spaceship
    life.setAlive(0,0);
    life.setAlive(0,2);
    life.setAlive(1,2);
    life.setAlive(1,1);
    life.setAlive(2,1);
}

void setLwss(GameOfLife &life){
    //Lightweight spaceship
    life.setAlive(0,0);
    life.setAlive(0,3);
    life.setAlive(1,4);
    life.setAlive(2,4);
    life.setAlive(3,4);
    life.setAlive(3,3);
    life.setAlive(3,2);
    life.setAlive(3,1);
    life.setAlive(2,0);
}


int main() {
    GameOfLife life(17, 17, 100);
    setPulsar(life);
    life.start();
}
