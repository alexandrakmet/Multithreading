#pragma once
#include <string>
#include <ctime>
#include <iostream>
#include "MyMutex.h"
#include "spinlock.h"
using namespace std;

#define NUM_TYPES 3

namespace thread_sync {
	class Benchmarking
	{
	private:
		 long* _time_waiting;
		 int* _counters;
		 Lockable* _types[NUM_TYPES];
		 std::string _type_names[NUM_TYPES];
		 int _increment;

		template<class T>
		 int _test_lock(T*, int, int);
		 void _print_results(int);
	public:
		Benchmarking();
		~Benchmarking();
		 void test(int);
	};

}
