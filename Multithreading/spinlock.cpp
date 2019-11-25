#include "spinlock.h"

namespace thread_sync {
	spinlock::spinlock()
	{

	}


	spinlock::~spinlock()
	{
	}

	bool spinlock::try_lock(int i)
	{
		return !_lock.test_and_set(std::memory_order_acquire);;
	}

	void thread_sync::spinlock::lock(int i)
	{
		while (_lock.test_and_set(std::memory_order_acquire));
	}

	void thread_sync::spinlock::unlock(int i)
	{
		_lock.clear(std::memory_order_release);
	}
}