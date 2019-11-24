#include "Benchmarking.h"

namespace thread_sync {

	long* Benchmarking::_time_waiting = new long[Benchmarking::NUM_TYPES];
	int* Benchmarking::_counters = new int[Benchmarking::NUM_TYPES];
	Lockable* Benchmarking::_types[Benchmarking::NUM_TYPES] = { new BlackWhiteBakeryLock, new ImprovedBakeryLock, new spinlock };
	std::string Benchmarking::_type_names[Benchmarking::NUM_TYPES] = { "BlackWhiteBakeryLock", "ImprovedBakeryLock", "Spinlock\t" };
	int Benchmarking::_increment = 0;

	Benchmarking::Benchmarking()
	{
	}


	Benchmarking::~Benchmarking()
	{
		
	}

	void Benchmarking::test(int n) {
		std::chrono::time_point<std::chrono::system_clock> start, end;

		for (int i = 0; i < NUM_TYPES; i++) {
			start = std::chrono::system_clock::now();
			_counters[i] = _test_lock(_types[i], n);
			end = std::chrono::system_clock::now();

			_time_waiting[i] = std::chrono::duration_cast<std::chrono::milliseconds>
				(end - start).count();

		}
		_print_results(n);
	}

	int Benchmarking::_test_lock(Lockable* lk, int n)
	{
		int counter = 0;
		std::thread *threads = new std::thread[n];
		
		auto func = [&lk, &counter](int i) {
				lk->lock(i);
				counter++;
				lk->unlock(i);
		};

		for (int i = 0; i < n; ++i) {
			threads[i] = std::thread(func, i);
		}

		for (int i = 0; i < n; ++i) {
			threads[i].join();
		}

		return counter;

	}
	void Benchmarking::_print_results(int n)
	{
		cout << "Number of threads: " << n << endl;
		cout << "\t\t\tTime\t\tCounter"<< endl;
		for (int i = 0; i < NUM_TYPES; i++) {
			cout << _type_names[i] << "\t" << _time_waiting[i] << "\t\t" << _counters[i] << endl;
		}
	}
}