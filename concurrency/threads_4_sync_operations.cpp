
//############################################################################
/*
 *  Concurrent C++
 *	https://www.youtube.com/watch?v=LL8wkskDlbs&list=PL5jc9xFGsL8E12so1wlMS0r0hTQoJL74M
 */
#include <deque>
#include <functional>
#include <iostream>
#include <fstream>
#include <thread>
#include <string>
#include <mutex>
#include <condition_variable>

/* Synchrosizing Operations */
using namespace std;

std::deque<int> q;
std::mutex mu;
std::condition_variable cond;

void function_1b() {
	int count = 10;
	while (count > 0) {
		std::unique_lock<mutex> locker(mu);
		q.push_front(count);
		locker.unlock();
		std::this_thread::sleep_for(chrono::seconds(1));
		count--;
	}
}

void function_2b() {
	int data = 0;
	while ( data != 1) {
		std::unique_lock<mutex> locker(mu);
		if (!q.empty()) {
			data = q.back();
			q.pop_back();
			locker.unlock();
			cout << "t2 got a value from t1: " << data << endl;
		} else {
			locker.unlock();
		}
		std::this_thread::sleep_for(chrono::milliseconds(10));
	}
}
// It is hard to set the sleep time.


// Using conditional variable and mutex
void function_1g() {
	int count = 10;
	while (count > 0) {
		std::unique_lock<mutex> locker(mu); // lock
		q.push_front(count); // add value
		locker.unlock(); // unlock
		cond.notify_one();  // Notify one waiting thread, if there is one.
		std::this_thread::sleep_for(chrono::seconds(1));
		count--;
	}
}

void function_2g() {
	int data = 0;
	while ( data != 1) {
		std::unique_lock<mutex> locker(mu);
		cond.wait(locker, [](){ return !q.empty();} );  // Unlock mu and wait to be notified if q is empty
			// relock mu
		data = q.back();
		q.pop_back();
		locker.unlock();
		cout << "t2 got a value from t1: " << data << endl;
	}
}

void cond_var(){
	std::thread t1(function_1g);
	std::thread t2(function_2g);
	t1.join();
	t2.join();	
}

void polling(){
	std::thread t1(function_1b);
	std::thread t2(function_2b);
	t1.join();
	t2.join();
}

int main() {
	cond_var();
	//polling();
	return 0;
}
