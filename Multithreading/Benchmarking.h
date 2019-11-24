#pragma once
#include <string>
#include <ctime>
#include <iostream>
#include "MyMutex.h"
#include "spinlock.h"
using namespace std;

namespace thread_sync {
	class Benchmarking
	{
	private:
		static const int NUM_TYPES = 3;
		static long* _time_waiting;
		static int* _counters;
		static Lockable* _types[NUM_TYPES];
		static std::string _type_names[NUM_TYPES];
		static int _increment;
		static int _test_lock(Lockable*, int);
		static void _print_results(int);
	public:
		Benchmarking();
		~Benchmarking();
		static void test(int);
	};

}
