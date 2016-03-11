//https://en.wikipedia.org/wiki/Curiously_recurring_template_pattern#Static_polymorphism
#include <iostream>

using namespace std;
template <class T> 
class GameInterface {
public:
	~GameInterface(){ cout << "Destroying GameInterface..." << endl;}

	virtual void doStuff(){
		cout << "GameInterface doing stuff"<< endl;
		// static_cast<T*>(this)->doMoreStuff();
	}


	static T* getInstance(){
		static T *instance = new T;
		return static_cast<T*>(instance);
	}
};

class Game : public GameInterface<Game> {
public:
	~Game(){
		cout << "Destructing Game..." << endl;
	}

    void doMoreStuff(){
    	cout << "Game doing more and more stuff" << endl;

    }

    void doStuff(){
    	cout << "Game doing stuff" << endl;

    }
};

int main(){
	Game *g = Game::getInstance();

	g->GameInterface<Game>::doStuff();
	g->doStuff();
	g->doMoreStuff();

	delete g; 
	return 0;
}