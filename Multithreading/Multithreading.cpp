

#include <iostream>
#include "Benchmarking.h"
#include "spinlock.h"
#include "Producer_Consumer_monitor.h"
#include "Test_atomic.h"
using namespace thread_sync;

int main()
{
	//Benchmarking::test(5);
	/*ProducerConsumer pc;
	pc.test(5, 3);
	*/
	Test_atomic test;
	test.test(5);
}
