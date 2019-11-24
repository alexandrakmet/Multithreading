#pragma once
#include <string>
#include <ctime>
#include <iostream>
#include "MyMutex.h"

namespace thread_sync {
	class Benchmarking
	{
	private:
		static long* time_waiting;
		static std::time_t* time_ending;
		static std::string* types;
		static int increment;
		template<class T> static void test_lock(int);
	public:
		Benchmarking();
		~Benchmarking();

		static void test(int);


	};

}
