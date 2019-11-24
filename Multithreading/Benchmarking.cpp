#include "Benchmarking.h"

//std::cout << "Вычисления закончены в " << std::ctime(&end_time)
namespace thread_sync {
	long* Benchmarking::time_waiting = new long[10];
	time_t* Benchmarking::time_ending = new time_t[10];
	std::string* Benchmarking::types = new std::string[10];
	int Benchmarking::increment = 0;

	Benchmarking::Benchmarking()
	{
	}


	Benchmarking::~Benchmarking()
	{
	}

	void Benchmarking::test(int n) {
		std::chrono::time_point<std::chrono::system_clock> start, end;

		start = std::chrono::system_clock::now();
		test_lock<BlackWhiteBakeryLock>( n);
		end = std::chrono::system_clock::now();

		time_waiting[0] = std::chrono::duration_cast<std::chrono::milliseconds>
			(end - start).count();
		time_ending[0] = std::chrono::system_clock::to_time_t(end);

		std::cout << "Computations ended at " << std::ctime(&time_ending[0]) << "\nDuration: " << time_waiting[0]<<"(ms)";


		start = std::chrono::system_clock::now();
		test_lock<ImprovedBakeryLock>(n);
		end = std::chrono::system_clock::now();

		time_waiting[1] = std::chrono::duration_cast<std::chrono::milliseconds>
			(end - start).count();
		time_ending[1] = std::chrono::system_clock::to_time_t(end);

		std::cout << "\nComputations ended at " << std::ctime(&time_ending[0]) << "\nDuration: " << time_waiting[1] << "(ms)";

	}
	template<class T>
	void Benchmarking::test_lock( int n)
	{
		int counter = 0;
		std::thread *threads = new std::thread[n];
		
		T lk;
		auto func = [&lk, &counter](int i) {
			for (int j = 0; j < 100000; ++j)
			{
				lk.lock(i);
				counter++;
				lk.unlock(i);
			}
		};

		for (int i = 0; i < n; ++i) {
			threads[i] = std::thread(func, i);
		}

		for (int i = 0; i < n; ++i) {
			threads[i].join();
		}

		std::cout << "\n counter= " << counter << std::endl;

	}
}