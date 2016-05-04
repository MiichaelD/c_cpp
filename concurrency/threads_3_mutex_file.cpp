//############################################################################
/*
 *  Concurrent C++
 *	https://www.youtube.com/watch?v=LL8wkskDlbs&list=PL5jc9xFGsL8E12so1wlMS0r0hTQoJL74M
 */
#include <fstream>
#include <string>
#include <thread>
#include <mutex>

using namespace std;

/* Important: Do not let your user work on protected data directly 
 * 1. Avoid global variables
 * 2. Mutex should bundle together with the resource it is protecting.
 */
class LogFile {
	std::mutex m_mutex;
	ofstream f;
public:
	LogFile() {
		f.open("log.txt");
	} // Need destructor to close file
	void shared_print(string id, int value) {
		std::lock_guard<mutex> locker(m_mutex);
		f << "From " << id << ": " << value << endl;
	}
	// Never leak f to outside world, like this:
	void processf(void fun(ofstream&)) {
		fun(f);
	}

};

class Fctor {
	LogFile& m_log;
public:
	Fctor(LogFile& log):m_log(log) {}
	void operator()() {
		for (int i=0; i>-100; i--) 
			m_log.shared_print("t1", i);
	}
};

int main() {
	LogFile log;
	Fctor fctor(log);
	std::thread t1(fctor);

	for (int i=0; i<100; i++)
		log.shared_print("main", i);

	t1.join();

	return 0;
}

// /* the ofstream will not be protected if it is leaked out */
// // Example: add a LogFile method:
// 	ofstream* getStream() {
// 		return &f;
// 	}
// // main():
// 	ofstream* fs = log.getStream();
// 	*fs << "ddummy" << endl;  // Unprotected access

// // A more hidden leakage:
// 	void formated_print(function<ofstream (ofstream&)> usrFunc){
// 		std::lock_guard<mutex> locker(m_mutex);
// 		usrFunc(f);
// 	}

