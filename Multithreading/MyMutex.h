#pragma once
#include <atomic>
#include <cstdint>
#include <thread>
#include <memory>

#include "Concepts.h"

namespace thread_sync {

	class ImprovedBakeryLock : public Lockable {
	public:
		ImprovedBakeryLock();
		~ImprovedBakeryLock();
		bool try_lock(int i) override;
		void lock(int i) override;
		void unlock(int i) override;
	private:
		std::atomic<uint64_t> _ticket_counter;
		volatile uint64_t* _token;
		volatile bool* _choosing;
		const int _n;
	};

	class BlackWhiteBakeryLock : public Lockable {
	private:
		int _produce_ticket(int num);
	public:
		BlackWhiteBakeryLock();
		~BlackWhiteBakeryLock();
		bool try_lock(int i) override;
		void lock(int i) override;
		void unlock(int i) override;
	private:
		volatile bool _shared_color;
		volatile bool* _my_color;
		volatile bool* _choosing;
		volatile int* _number;
		const int _n;
	};

	class TicketLock : public Lockable {
	private:
		uint32_t _bound_ticket(uint32_t ticket_value) const;
	public:
		TicketLock(uint32_t max_waiting_number = 0);
		~TicketLock() = default;
		void lock(int) override;
		bool try_lock(int) override;
		void unlock(int) override;
	private:
		std::atomic<uint32_t> _ticket_counter, _now_serving;
		const uint32_t _max_waiting;
		// when we now the maximum number of threads waiting at the same time
		// for a shared resource, we can bound the ticket value
	};
}
