
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

 /* For threads to return values: future */
static int factorial(int N) {
	int res = 1;
	for (int i=N; i>1; i--)
		res *= i;

	return res;
}

/* Asynchronously provide data with promise */
static int factorialf(future<int>& f) {
	// do something else
	int N = f.get();     // If promise is distroyed, exception: std::future_errc::broken_promise
	cout << "Got from parent: " << N << endl; 
	int res = 1;
	for (int i=N; i>1; i--)
		res *= i;

	return res;
}

/* shared_future */
int factorialsf(shared_future<int> f) {
	// do something else

	int N = f.get();     // If promise is distroyed, exception: std::future_errc::broken_promise
	f.get();
	cout << "Got from parent: " << N << endl; 
	int res = 1;
	for (int i=N; i>1; i--)
		res *= i;

	return res;
}

void simpleFuture(){
	// this function will wait for the thread it creates to return a *future* value after
	// finishing processing it.

	// future<int> fu = std::async(factorial, 4); 
	auto launch_policy = (std::launch::deferred | std::launch::async);// this is the default policy, works just as the line above
	// this will create a new thread depending on the implementation, to make sure a new
	// thread will be born, we should just use: std::launch::async
	std::future<int> fu = std::async(launch_policy, factorial, 4);
	cout << "Got from child thread #: " << fu.get() << endl;
	// fu.get();  // crash
}

void promisedFuture(){
	// this function will send a *future* value to the thread using a promise, when the thread
	// receives the value, it will return the processed value to the parent thread via another 
	// future
	promise<int> p;
	future<int> f = p.get_future();
	future<int> fu2 = std::async(std::launch::async, factorialf, std::ref(f));

	// Do something else
	int i = 0;
	std::this_thread::sleep_for(chrono::milliseconds(20));
	for (; i < 7; ++i){}
	// Finish something else and set the value promised value 
	p.set_value(i);    // Keep your promise.
	// p.set_value(28);  // It can only be set once
	// p.set_exception(std::make_exception_ptr(std::runtime_error("I lied, didn't did what I promise")));

	cout << "Got from child thread #: " << fu2.get() << endl;
}

void sharedFuture(){
	// Both promise and future cannot be copied, they can only be moved.
	promise<int> p;
	future<int> f = p.get_future();
	shared_future<int> sf = f.share(); // share can be copied

	future<int> fu1 = std::async(std::launch::async, factorialsf, sf);
	future<int> fu2 = std::async(std::launch::async, factorialsf, sf);

	// Do something else
	std::this_thread::sleep_for(chrono::milliseconds(20));
	p.set_value(5);

	cout << "Got from child thread1 #: " << fu1.get() << endl;
	cout << "Got from child thread2 #: " << fu2.get() << endl;
}


int main() { 
	// if parameter function is a member function it should be binded to the object containing it
	// or it should be static: http://stackoverflow.com/a/30195794

	// simpleFuture();
	promisedFuture();
	// sharedFuture();
	return 0;
}
