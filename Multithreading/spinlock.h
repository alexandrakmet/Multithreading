#pragma once
#include "Concepts.h"
#include <atomic>


namespace thread_sync {
	class spinlock : public Lockable
	{
	private:
		std::atomic_flag m_lock = ATOMIC_FLAG_INIT;
	public:
		spinlock();
		~spinlock();
		bool try_lock(int i) override;
		void lock(int i) override;
		void unlock(int i) override;
	};

}