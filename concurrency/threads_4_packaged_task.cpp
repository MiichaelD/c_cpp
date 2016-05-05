
//############################################################################
/*
 *  Concurrent C++
 *	https://www.youtube.com/watch?v=LL8wkskDlbs&list=PL5jc9xFGsL8E12so1wlMS0r0hTQoJL74M
 */
#include <functional>
#include <iostream>
#include <thread>
#include <string>
#include <mutex>
#include <future>
#include <deque>

using namespace std;

/* Summary
 * 3 ways to get a future:
 * - promise::get_future()
 * - packaged_task::get_future()
 * - async() returns a future
 */

/* packaged_task */

std::mutex mu;
std::deque<std::packaged_task<int()> > task_q;

int factorial(int N) {
	int res = 1;
	for (int i=N; i>1; i--)
		res *= i;

	return res;
}

void thread_1() {
	for (int i=0; i<10000; i++) {
		std::packaged_task<int()> t;
		{
			std::lock_guard<std::mutex> locker(mu);
			if (task_q.empty()) {
				cout << "waiting ... " << endl;
				continue;
			}
			t = std::move(task_q.front());
			task_q.pop_front();
		}
		t();
	}
}

int main() {
	std::thread th(thread_1);

	std::packaged_task<int()> t(bind(factorial, 6));  
	std::future<int> ret = t.get_future();
	std::packaged_task<int()> t2(bind(factorial, 9));
	std::future<int> ret2 = t2.get_future();
	{
		std::lock_guard<std::mutex> locker(mu);
		task_q.push_back(std::move(t));
		task_q.push_back(std::move(t2));
	}
	cout << "I see: " << ret.get() << endl;
	cout << "I see: " << ret2.get() << endl;

	th.join();
	return 0;
}