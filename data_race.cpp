#include <thread>
#include <string>
#include <mutex>
#include <fstream>
using namespace std;

class LogFile {
	std::mutex m_mutex;
	ofstream f;
public:
	LogFile() {
		f.open("log.txt");
	}
	void shared_printer(string id, int value) {
		std::lock_guard<mutex> locker(m_mutex);
		f << "From " << id << ":" << value << endl;
	}
	// the idea here is to totally protected f by mutex
	// we create ostream f here is because cout is a global variable why could be used by
	// outside user, so mutex_guard could not protected it	fully
};

void function_1(LogFile & log) {
	for (int i = 0; i > -100; i--)
		log.shared_printer(string("t1: "), i);
}
int main() {
	LogFile log;
	std::thread t1(function_1, std::ref(log));

	for (int i = 0; i < 100; i++)
		log.shared_printer(string("main: "), i);
	t1.join();
	system("pause");
	return 0;
}