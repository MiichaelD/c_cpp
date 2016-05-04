//############################################################################
/*
 *  Concurrent C++
 *	https://www.youtube.com/watch?v=LL8wkskDlbs&list=PL5jc9xFGsL8E12so1wlMS0r0hTQoJL74M
 */
 #include <thread>
 #include <iostream>
 #include <fstream>
 using namespace std;
 
// Second Example: Racing condition
class Fctor {
	ofstream& m_str;
public:
	Fctor(ofstream& s):m_str(s) {}   // Reference member can only be initialized
	void operator()() {
		for (int i=0; i>-100; i--)
			m_str << "from t1: " << i << endl;
	}
};

// 1. expeirment with t1.join()
// 2. expeirment with t1.detach()
// 3. expeirment with t1 closing file
// 4. expeirment with  cout instead of f and m_str
// 4. experiment with t1.get_id();
// 4. experiment with thread::hardware_concurrentcy();

// A common solution: do not share, make a copy.


// Alternative way: RAII
class ThreadJoiner {
	thread& m_th;
	ofstream &m_f;
public:
	explicit ThreadJoiner(thread& t, ofstream &out):m_th(t),m_f(out) {}
	~ThreadJoiner() {
		if(m_th.joinable()) {
			m_th.join();
			m_f.close();
		}
	}
};


// Paramters are always passed by value (copied).  why? same reason as bind(): deferred execution means the parmeter objects might not be valid at the time of execution
// To pass by reference:
// 1. use std::ref or std::cref (for constant references)
// 2. use pointer
// or if the object is not going to be needed again in the main thread just move it
// 1. use std::move

// Passing parameters to a thread 
void call_from_thread(string& msg) { // by reference
	msg = "Beauty2 is only skin-deep";
	cout << "t2 says: " << msg << endl;
}

class A {
public:
	void call_from_thread(string* msg) { // by pointer
		*msg = "Beauty3 is only skin-deep";
		cout << "t3 says: " << *msg << endl;
	}
};

// Thread with moving parameters
void call_from_thread4(string msg) { // by value (but can receive a moved string too)
	cout << "t4 says: " << msg << endl;
}

// If exception happens in the main()'s for loop, t1.join() will not be called.
int main() {
	cout << "Hello Michael, ideal number of threads: " << std::thread::hardware_concurrency() << endl << endl;
	ofstream f;
	f.open("log.txt");

	//Thread one running Fctor
	Fctor fctor(f);
	std::thread t1(fctor);

	
	string s = "A friend in need is a friend indeed.";
	string *moved = new string ("This value will be moved");
	// Function templates ref and cref are helper functions that generate an object of type std::reference_wrapper
	std::thread t2(call_from_thread, std::ref(s));

	A a;
	std::thread t3(&A::call_from_thread, &a, &s);

	std::thread t4(call_from_thread4, std::move(*moved));
	// join thread if an exception happens.
	// try {
	// 	for (int i=0; i<100; i++)
	// 		f << "from main: " << i << endl;  // Exception may happen here
	// } catch (...) {
	// 	t1.join();
	//  f.close();
	// 	throw;
	// }
	// t1.join();
	// f.close();

	//Or alternatively use RAII:
	ThreadJoiner tj(t1, f);
	for (int i=0; i<100; i++)
		f << "from main: " << i << "\t" << s << endl;

	cout << "moved str: " << *moved << endl;
	delete moved;

	//tj will be destructed, calling t1.join and f.close();
	return 0;
}


/*
// A thread object cannot be copied
// But it can be moved.  Like fstream, unique_ptr, etc.

//Case 1:
std::thread t1(call_from_thread);
std::thread t2 = move(t1);  // t2 become the owner of the thread
t2.join();

//Case 2:
thread f() {
   // ...
   return std::thread(call_from_thread);   // move semantics 
}

//Case 3:
void f(std::thread t);
int main() {
   f(std::thread(call_from_thread));  // move semantics
   //...
}

// Revisit the RAII example with move semantics
*/
