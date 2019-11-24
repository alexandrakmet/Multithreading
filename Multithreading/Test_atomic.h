#pragma once
#include <atomic>
#include <thread>
#include <iostream>

class Counter
{
public:
	Counter();
	~Counter();
	void increase();
	void decrease();
	int get();
private:
	std::atomic<int> _value = 0;
};

class Test_atomic
{
private:
	Counter _counter;
	void _thread_func();
public:
	Test_atomic();
	~Test_atomic();
	void test(int);
};

