
//############################################################################
/*
 *  Concurrent C++
 *	https://www.youtube.com/watch?v=LL8wkskDlbs&list=PL5jc9xFGsL8E12so1wlMS0r0hTQoJL74M
 */
#include <functional>
#include <iostream>
#include <fstream>
#include <thread>
#include <string>
#include <mutex>
#include <future>

using namespace std;

/* async() are used in the same ways as thread(), bind() */
class A {
public:
	A(){ cout << "A created() " << endl;}
	string note;
	void f(int x, char c) { }
	long g(double x) { note = "changed"; return 0;}
	int operator()(int N) { return 0;}
};

/*
	std::thread t1(a, 6);   
	std::async(a, 6);   
    std::bind(a, 6);
    std::call_once(once_flag, a, 6);

	std::thread t2(a, 6); 
	std::thread t3(std::ref(a), 6); 
	std::thread t4(std::move(a), 6);
	std::thread t4([](int x){return x*x;}, 6);

	std::thread t5(&A::f, a, 56, 'z');  // copy_of_a.f(56, 'z')
	std::thread t6(&A::f, &a, 56, 'z');  // a.f(56, 'z') 
*/

int main() { 
	A a;
	a.note = "Original"; 
	std::future<int> fu3 = std::async(A(), 4);    // A tmpA;  tmpA is moved to async(); create a task/thread with tmpA(4);
	std::future<int> fu4 = std::async(a, 7);    
	std::future<int> fu5 = std::async(std::ref(a), 7); // a(7);  Must use reference wrapper
	// std::future<int> fu6 = std::async(&a, 7); // Won't compile

	std::future<void> fu1 = std::async(&A::f, a, 56, 'z'); // A copy of a invokes f(56, 'z') - MD I didn't see any copying, probably it was optimized by the compiler
	std::future<long> fu2 = std::async(&A::g, &a, 5.6);    // a.g(5.6);  a is passed by reference
		// note: the parameter of the invocable are always passed by value, but the invokeable itself can be passed by ref.
	cout << a.note << endl;
	return 0;
}