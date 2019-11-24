#include "Benchmarking.h"

//std::cout << "Вычисления закончены в " << std::ctime(&end_time)
namespace thread_sync {
	long* Benchmarking::time_waiting = new long[10];
	time_t* Benchmarking::time_ending = new time_t[10];
	Lockable* Benchmarking::types[3] = { new BlackWhiteBakeryLock, new ImprovedBakeryLock, new spinlock };
	int Benchmarking::increment = 0;

	Benchmarking::Benchmarking()
	{
	}


	Benchmarking::~Benchmarking()
	{
	}

	void Benchmarking::test(int n) {
		std::chrono::time_point<std::chrono::system_clock> start, end;

		for (int i = 0; i < 3; i++) {
			start = std::chrono::system_clock::now();
			test_lock(types[i], n);
			end = std::chrono::system_clock::now();

			time_waiting[0] = std::chrono::duration_cast<std::chrono::milliseconds>
				(end - start).count();
			time_ending[0] = std::chrono::system_clock::to_time_t(end);

			std::cout << "\nComputations ended at " << std::ctime(&time_ending[0]) << "Duration: " << time_waiting[0] << "(ms)" << std::endl;
		}

	}

	void Benchmarking::test_lock(Lockable* lk, int n)
	{
		int counter = 0;
		std::thread *threads = new std::thread[n];
		
		auto func = [&lk, &counter](int i) {
			for (int j = 0; j < 100000; ++j)
			{
				lk->lock(i);
				counter++;
				lk->unlock(i);
			}
		};

		for (int i = 0; i < n; ++i) {
			threads[i] = std::thread(func, i);
		}

		for (int i = 0; i < n; ++i) {
			threads[i].join();
		}

		std::cout << "\ncounter = " << counter;

	}
}