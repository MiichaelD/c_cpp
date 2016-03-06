/**
	B:2) Write a Car class.
	Assuming you are given a class “Engine” that has the “start()” method
	prototyped below,	write a “Car” class with a “turnKey()” method that
	tells you whether the car started or not. The Car class should
	encapsulate an “Engine”.

	bool Engine::start();
	


	Programmer:	Michael Duarte
	Compile:	g++ test2.cpp tools/debug_new.cpp -o Main2
					g++ test2.cpp -o Main2
	Date:		October/2014
*/

#include <iostream>
class Car{

private:
	Engine *mEngine;

public:
	Car(){
		mEngine = new Engine();
	}

	~Car(){
		if(mEngine != NULL)
			delete mEngine;
	}

	bool turnKey(){
		bool started = pEngine->start();
		if(started){
			cout << (started? "The engine started" : "The engine didn't start") << endl;
		}
		return started;
	}
}