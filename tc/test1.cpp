/**
a) List all of the problems you can see with this code and provide specific minimal changes which
would address those problems. 

b) OPTIONAL BONUS: Describe how RAII could help simplify this implementation if it were rewritten.
----
	#include <string.h>

	using namespace std;

	void newBuffer(char* outBuffer, size_t sz) {
	   outBuffer = new char[sz];
	}

	int main(void) {
	   const char* kung = "KUNG";
	   char* foo;
	   size_t len = strlen(kung);
	   newBuffer(foo, len);
	   memset(foo, 0, len+1);
	   strncpy(foo, kung, len);
	   cout << foo << endl;
	}
-----
	There were 2 problems:

	1)	the function:
		void newBuffer(char* outBuffer, size_t sz) {
			outBuffer = new char[sz];
		}
		Didn't actually initialized the outBuffer passed in, so there was a
		segmentation fault when trying to access the foo variable in the main
		function

	2) there was a memory leak because the foo variable were never deleted using
	the operator delete[], this is mandatory because it was initialized using new[]
	and needed to be freed from the heap memory before finishing the program, even
	better, just when finished to be needed.


	Also I read about RAII and changed from a pointer of char to an array of chars
	this causes the program to allocate the memory in the stack memory and free it
	when this function returns (because it uses no new/malloc operator)


	Programmer:	Michael Duarte
	Compile:	g++ test1.cpp tools/debug_new.cpp -o Debug
					g++ test1.cpp -o Main
	Date:		October/2014
*/



#include <iostream>
#include <string.h>
#ifdef DEBUG
	#include "tools/debug_new.h"
#endif

using namespace std;

void newBuffer(char** outBuffer, size_t sz) {
	*outBuffer = new char[sz];
}

int main(void) {
	const char* kung = "KUNG-FU PANDA";
	char* foo;
	size_t len = strlen(kung);
	//char foo[len];

	newBuffer(&foo, len);
	cout << "Foo:" << foo << endl;
	memset(foo, 0, len);
	strncpy(foo, kung, len);

	cout << "FOO: " << foo << " - " << *foo << " - "  << &foo <<endl;
	cout << "KUNG: " << kung << " - " << *kung << " - "  << &kung <<endl;



	delete[] foo;
	cout << "kung:" << kung << endl;
	cout << "Foo:" << foo << endl;
}