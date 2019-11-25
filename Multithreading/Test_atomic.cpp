#include "Test_atomic.h"


Counter::Counter()
{
}

Counter::~Counter()
{
}

void Counter::increase()
{
	_value.fetch_add(1);
}

void Counter::decrease()
{
	_value.fetch_sub(1);
}

int Counter::get()
{
	return _value.load();
}


Test_atomic::Test_atomic()
{
}

Test_atomic::~Test_atomic()
{
}

void Test_atomic::test(int num_threads)
{
	std::thread *threads = new std::thread[num_threads];

	for (int i = 0; i < num_threads; ++i) {
		threads[i] = std::thread(&Test_atomic::_thread_func, &*this);
	}

	for (int i = 0; i < num_threads; ++i) {
		threads[i].join();
	}

	delete[]threads;

	std::cout << "Number of threads: " << num_threads << std::endl;
	std::cout << "Counter = " << _counter.get();

}

void Test_atomic::_thread_func()
{
	_counter.increase();
}
