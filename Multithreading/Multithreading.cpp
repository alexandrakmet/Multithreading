

#include <iostream>
#include "Benchmarking.h"
#include "spinlock.h"
#include "Producer_Consumer_monitor.h"
using namespace thread_sync;

int main()
{
	ProducerConsumer pc;
	pc.test(5, 3);
	int k;
	std::cin >> k;
}
