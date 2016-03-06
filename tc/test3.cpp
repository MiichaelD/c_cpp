/**
	B:3) Describe precisely what happens in each step of this program and
	what the output will be. Assume that setString sets an instance member
	variable and printString prints it with no additional space or formatting.

	MyClass *a = new MyClass();
	vector<MyClass> myVector;
	myVector.push_back(*a);

	MyClass b = myVector[0];

	a->setString(“Hello World”);
	b.setString(“Goodbye World”);

	a->printString();
	b.printString();
	
	------
	Description per line number:
	1) Declare a pointer “a” and instantiate an object of type MyClass on the heap memory.
	2) Create a vector of type MyClass.
	3) Push at the end the value of the object a (a copy) to myVector.
	4) Create an object in the stack called b and copy the value of the first position of myVector.
	5) Set “Hello World” to the member string of  the object located by the pointer a using its function setString.
	6) Set “Goodbye World” to the member string of the object b using its function setString.
	7) Prints the value of the member string of object a (“Hello World”);
	8) Prints the value of the member string of object b (“Goodbye World”);

	As note: the member string of myVector[0] was not modified. And the allocation made by the first line was never freed using “delete” operator.

	------

	Programmer:	Michael Duarte
	Compile:	g++ test3.cpp tools/debug_new.cpp -o Main3
				g++ test3.cpp -o Main3
	Date:		October/2014
*/

#include <iostream>
#include <string.h>
#include <vector>

using namespace std;

class MyClass{
private:
	string str;
public:
	MyClass(){

	}

	~MyClass(){

	}

	void setString(char * text){
		str = text;
	}

	void printString(){
		cout << str << endl;
	}

};

int main(void) {
	MyClass* a = new MyClass();
	vector<MyClass> myVector;
	a->setString("Hello World blablabla");
	myVector.push_back(*a);

	MyClass b = myVector[0];

	a->setString("Hello World");
	b.setString("GoodBye World");

	a->printString();
	myVector[0].printString();
	b.printString();

	delete a;
}