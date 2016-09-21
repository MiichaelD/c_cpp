//############################################################################
/*
 *  Concurrent C++
 *	https://www.youtube.com/watch?v=LL8wkskDlbs&list=PL5jc9xFGsL8E12so1wlMS0r0hTQoJL74M
 */

#include <fstream>
#include <string>
#include <thread>
#include <mutex>
#include <memory>

using namespace std;

 /* Lock for Initialization */
class LogFileBad {
	std::mutex m_mutex;
	ofstream f;
public:
	void shared_print(string id, int value) {
		if (!f.is_open()) {   // lazy initialization
			std::unique_lock<mutex> locker(m_mutex);
			f.open("log.txt");   // This must be synchronized
		}
		f << "From " << id << ": " << value << endl;  // I don't care this is not synchronized
	}
};

// Problem: log.txt still will be opened multiple times

class LogFileBad2 {
	std::mutex m_mutex;
	ofstream f;
public:
	void shared_print(string id, int value) {
		if (!f.is_open()) {   // lazy initialization   -- A
			std::unique_lock<mutex> locker(m_mutex);
	        if (!f.is_open()) {
				f.open("log.txt");   // This must be synchronized  -- B
	        }
		}
		f << "From " << id << ": " << value << endl;  // I don't care this is not synchronized
	}
};
// Double-checked locking
// Problem: race condition between point A and point B


// C++ 11 solution:
class LogFile {
   static int x;
	std::mutex m_mutex;
	ofstream f;
	std::once_flag m_flag;
	void init() { f.open("log.txt"); }
public:
	~LogFile() {f.close();}
	void shared_print(string id, int value) {
      std::call_once(m_flag, &LogFile::init, this); // init() will only be called once by one thread
		//std::call_once(m_flag, [&](){ f.open("log.txt"); });  // Lambda solutioncat
		f << ++x <<  ") From " << id << ": " << value << endl;
	}
};
int LogFile::x = 0;

//Note: once_flag and mutex cannot be copied or moved.
//      LogFile can neither be copy constructed nor copy assigned

// static member data are guaranteed to be initialized only once.

LogFile f;

void childThread(){
	for (int i = 10; i>0; --i)
		f.shared_print("Child", i);
}

int main(){
	std::thread t1(childThread);
	for (int i = 0; i < 10; ++i){
		f.shared_print("Main", i);
	}

	t1.join();
}



