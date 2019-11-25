#pragma once
#include "Concepts.h"
#include "IDAllocator.h"

#include <vector>

namespace thread_sync {
	class AbstractFixnumLockable : public FixnumLockable {
	public:
		using FixnumLockable::lock;
		using FixnumLockable::unlock;

		AbstractFixnumLockable();
		AbstractFixnumLockable(int max_number_of_threads);
		AbstractFixnumLockable(allocator::IDAllocator* allocator);
		int get_id()override;
		bool register_thread()override;
		void unregister_thread()override;
		bool reset(unsigned int new_max_id)override;
		bool reset(unsigned int new_min_id, unsigned int new_max_id)override;
		void lock(int i)override;
		void unlock(int i)override;
		bool try_lock(int i)override;
		int get_max_number_of_threads()override;
		virtual ~AbstractFixnumLockable();
	private:
		allocator::IDAllocator* allocator;
		thread_local static int thread_id;
		int max_number_of_threads;
	};
}