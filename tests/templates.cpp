
#include <iostream>

using namespace std;

template<class T> 
T multiplyBy2(T in){
	return in + 2;
}

int main(){

	int x = 10;
	double y = 11;
	char z = 'a';

	cout << "x: " << x << endl << "y: " << y << endl << "z: " << z << endl;

	cout << "x: " << multiplyBy2(x) << endl << "y: " << multiplyBy2(y) << endl << "z: " << multiplyBy2(z) << endl;

}