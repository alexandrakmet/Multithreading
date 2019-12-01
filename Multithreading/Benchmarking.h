#pragma once
#include <string>
#include <ctime>
#include <iostream>
#include "MyMutex.h"
#include "spinlock.h"
#include "DekkerLock.h"
#include "Test_atomic.h"
using namespace std;

#define NUM_TYPES 5

namespace thread_sync {
	class Benchmarking
	{
	private:
		 long* _time_waiting;
		 int* _counters;
		 Lockable* _types[NUM_TYPES];
		 std::string _type_names[NUM_TYPES];

		template<class T>
		 int _test_lock(T*, int, int);
		 int _test_atomic_counter(int, int);
		 void _print_results(int);
	public:
		Benchmarking();
		~Benchmarking();
		 void test(int);
	};

}
