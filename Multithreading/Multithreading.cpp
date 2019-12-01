

#include <iostream>
#include "Benchmarking.h"
#include "Producer_Consumer_monitor.h"
#include "Test_atomic.h"
using namespace thread_sync;

void producer_consumer_problem() {
	ProducerConsumer pc;
	pc.test(5, 3);
}

void atomic_counter_threads_test() {
	Test_atomic test;
	test.test(5);
}

void benchmarking() {
	Benchmarking b;
	b.test(2);
	b.test(5);
	b.test(10);
}
int main()
{
	benchmarking();
	//producer_consumer_problem();
	//atomic_counter_threads_test();
	cin.get();
}
