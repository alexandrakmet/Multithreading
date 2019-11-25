#include "Producer_Consumer_monitor.h"


Producer_Consumer_monitor::Producer_Consumer_monitor()
{
}


Producer_Consumer_monitor::~Producer_Consumer_monitor()
{
}

void Producer_Consumer_monitor::insert(int item)
{
	std::unique_lock<std::mutex> lk(m);
	while (count == N)
	{
		full.wait(lk);
	}
	buffer[end] = item;
	end = (end + 1) % N;
	count++;
	std::cout << "Item " << item << " was produced" << std::endl;
	lk.unlock();
	if (count == 1) empty.notify_one();
}

int Producer_Consumer_monitor::remove()
{
	std::unique_lock<std::mutex> lk(m);
	while (count == 0)
	{
		empty.wait(lk);
	}
	int item = buffer[start];
	start = (start + 1) % N;
	count--;
	std::cout << "Item " << item << " was consumed" << std::endl;

	lk.unlock();
	if (count == N-1) full.notify_one();
	return item;
}


ProducerConsumer::ProducerConsumer()
{
}

ProducerConsumer::~ProducerConsumer()
{
}

void ProducerConsumer::prod_func()
{
	using namespace std::chrono_literals;
	while(true) {
		int item = produce_item();
		monitor.insert(item);
		std::this_thread::sleep_for(100ms);
	}
}

int ProducerConsumer::produce_item()
{

	std::uniform_int_distribution<int> distribution(1, 100);
	int item = distribution(generator);
	return item;
}

void ProducerConsumer::cons_func()
{
	using namespace std::chrono_literals;
	while(true) {
		int item = monitor.remove();
		consume_item(item);
		std::this_thread::sleep_for(100ms);
	}
}

void ProducerConsumer::consume_item(int item)
{
}

void ProducerConsumer::test(int p, int c)
{
	std::thread *producers = new std::thread[p];
	std::thread *consumers = new std::thread[c];
	
	for (int i = 0; i < c; ++i) {
		consumers[i] = std::thread(&ProducerConsumer::cons_func, &*this);
	}
	for (int i = 0; i < p; ++i) {
		producers[i] = std::thread (&ProducerConsumer::prod_func, &*this);
	}
	
	for (int i = 0; i < c; ++i) {
		consumers[i].join();
	}
	for (int i = 0; i < p; ++i) {
		producers[i].join();
	}


	delete[]producers;
	delete[]consumers;
	
}


