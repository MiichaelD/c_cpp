//############################################################################
/*
 *  Concurrent C++
 *	https://www.youtube.com/watch?v=LL8wkskDlbs&list=PL5jc9xFGsL8E12so1wlMS0r0hTQoJL74M
 */
 #include <thread>
 #include <iostream>
 using namespace std;

// First example:
void thread1() {
	std::cout << "Hello, Worlds from " << std::this_thread::get_id() << std::endl;
}

int main() {
	std::thread t1(thread1);
	cout << "I, thread: " << std::this_thread::get_id() << " created thread: " << t1.get_id() << endl;
	t1.join();   // main thread wait for t1 to finish
	//t1.detach();  // main thread let t1 to run on its own: t1 is a daemon process.
                   // C++ runtime library is responsible returning t1's resources
                   // and main thread may finish before t2 prints "Hello"

	return 0;
}
// If neither detach nor join is called, terminate() will be called for the t1.
// A thread can only be joined once or detached once. After it is joined on detached
// it becomes unjoinable ( t.joinable() returns false )


