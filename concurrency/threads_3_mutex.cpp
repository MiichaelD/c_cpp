//############################################################################
/*
 *  Concurrent C++
 *	https://www.youtube.com/watch?v=LL8wkskDlbs&list=PL5jc9xFGsL8E12so1wlMS0r0hTQoJL74M
 */

#include <iostream>
#include <string>
#include <thread>
#include <mutex>
/* Using mutex to synchronize threads */
std::mutex m_mutex;

void shared_print(std::string id, int value) {
	std::lock_guard<std::mutex> locker(m_mutex); // lock_guard will lock and unlock using RAII
   //m_mutex.lock();
   // if (m_mutex.trylock()) {...}
	std::cout << "From " << id << ": " << value << std::endl;
   //m_mutex.unlock();
}

class Fctor {
public:
	void operator()() {
		for (int i=0; i>-100; i--) 
			shared_print("t1", i);
	}
};

int main() {
	Fctor fctor;
	std::thread t1(fctor);

	for (int i=0; i<100; i++)
		shared_print("main", i);

	t1.join(); // wait for thread to finish (if it hasn't yet)

	return 0;
}

