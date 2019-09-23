#include <iostream>
#include <thread>
#include <mutex>

using std::cout;
using std::endl;
using std::thread;
using std::mutex;

mutex globalLock;

void func(int a)
{
	globalLock.lock();
	cout<< "Hello world: " << a << " " << std::this_thread::get_id() << endl;
	globalLock.unlock();
}

int main(int argc, char const *argv[])
{
	thread t1(func, 10);
	thread t2(func, 20);
	t1.join();
	t2.join();
	return 0;
}
