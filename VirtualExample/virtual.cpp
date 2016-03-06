#include "WindowSpecial.h"
#include <iostream> 

int main(){
	WindowSpecial ws;
	std::cout << "calling on resize for WindowSpecial ... " << std::endl;
	ws.onResize();

	std::cout << "CLEANING UP ... " << std::endl;
	return 0;
}