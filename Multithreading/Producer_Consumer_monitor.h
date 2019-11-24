#pragma once

#include <iostream>
#include <condition_variable>
#include <mutex>
#include <random>

class Producer_Consumer_monitor
{
private:
	static const int N = 100;
	std::mutex m;
	std::condition_variable full, empty;
	int count = 0, start = 0, end = 0;
	int buffer[N];

public:
	Producer_Consumer_monitor();
	~Producer_Consumer_monitor();
	void insert(int);
	int remove();

};

class ProducerConsumer
{
public:
	ProducerConsumer();
	~ProducerConsumer();
	Producer_Consumer_monitor monitor;
	void test(int, int);
private:
	void prod_func();
	int produce_item();

	void cons_func();
	void consume_item(int);

	std::default_random_engine generator;
};
