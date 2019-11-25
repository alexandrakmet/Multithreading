#include "Benchmarking.h"
#include <vector>
#include <mutex>
#include <future>

namespace thread_sync {


	Benchmarking::Benchmarking()
	{
		_time_waiting = new long[NUM_TYPES];
		_counters = new int[NUM_TYPES];
		_types[0] = new BlackWhiteBakeryLock;
		_types[1] = new ImprovedBakeryLock;
		_types[2] = new spinlock;
		_types[3] = new DekkerLock;
		_type_names[0] = "BlackWhiteBakeryLock";
		_type_names[1] = "ImprovedBakeryLock";
		_type_names[2] = "Spinlock\t";
		_type_names[3] = "DekkerLock\t";
		_increment = 0;
	}


	Benchmarking::~Benchmarking()
	{
		delete _time_waiting;
		delete _counters;
	}

	void Benchmarking::test(int num_threads) {

		std::thread threads[NUM_TYPES];

		auto f = [&](int num_threads, int i) {
			_counters[i] = _test_lock<Lockable>(_types[i], num_threads, i);
		};

		for (int i = 0; i < NUM_TYPES; i++) {
			if(num_threads == 2 || i != NUM_TYPES-1 ) threads[i] = std::thread(f, num_threads, i);
		}
		for (int i = 0; i < NUM_TYPES; i++) {
			if (num_threads == 2 || i != NUM_TYPES - 1) threads[i].join();
		}
		
		_print_results(num_threads);

	}

	template <class T>
	int Benchmarking::_test_lock(T* lk, int num_threads, int i)
	{
		std::chrono::time_point<std::chrono::system_clock> start, end;
		
		int counter = 0;
		std::vector<std::thread> threads(num_threads);
		
		auto func = [&lk, &counter](int i) {
				lk->lock(i);
				for(int j = 0; j < 1000000; j++)
				counter++;
				lk->unlock(i);
		};

		start = std::chrono::system_clock::now();
		for (int i = 0; i < num_threads; ++i) {
			threads[i] = std::thread(func, i);
		}

		for (int i = 0; i < num_threads; ++i) {
			threads[i].join();
		}
		end = std::chrono::system_clock::now();

		_time_waiting[i] = std::chrono::duration_cast<std::chrono::milliseconds>
			(end - start).count();
		return counter;

	}

	void Benchmarking::_print_results(int num_threads)
	{
		cout << "Number of threads: " << num_threads << endl;
		cout << "\t\t\tTime" << "\t\tCounter" << endl;
		for (int i = 0; i < NUM_TYPES; i++) {
			if (num_threads == 2 || i != NUM_TYPES - 1) cout << _type_names[i] << "\t" << _time_waiting[i] << "(ms)\t\t" << _counters[i] << endl;
		}
	}
}