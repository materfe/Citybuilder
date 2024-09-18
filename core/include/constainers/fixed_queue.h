#ifndef CORE_CONTAINERS_FIXED_QUEUE_H_
#define CORE_CONTAINERS_FIXED_QUEUE_H_
#include <stdexcept>

namespace core
{
	/**
	 * \brief a queue that uses an array and a specific max capacity
	 * \tparam T
	 * \tparam Capacity max capacity
	 */
	template <typename T, size_t Capacity>
	class FixedQueue
	{
	private:
		T container_[Capacity];
		int front_index_;
		int back_index_;
		size_t size_;

	public:
		// Constructor to initialize the queue -> front_index,back_index,count
		FixedQueue() : front_index_(0), back_index_(0), size_(0) {}

		// Push an element onto the queue
		void Push(const T& value)
		{
			if (size_ < Capacity)
			{
				container_[back_index_] = value;
				back_index_ = (back_index_ + 1) % Capacity;
				size_++;
			}
			else
			{
				throw std::overflow_error("FixedQueue<>::Push(): queue overflow");
				//std::terminate
			}
		}

		// Pop an element from the queue -> does not erase it but does move what is considered as stârt of queue and end
		void Pop()
		{
			if (size_ > 0)
			{
				front_index_ = (front_index_ + 1) % Capacity;
				size_--;
			}
			else
			{
				throw std::underflow_error("FixedQueue<>::Pop(): queue underflow");
				//std::terminate
			}
		}

		// Get the first element of the queue
		[[nodiscard]] const T& Front() const
		{
			if (size_ > 0)
			{
				return container_[front_index_];
			}
			else
			{
				throw std::underflow_error("FixedQueue<>::Front(): empty queue");
				//std::terminate
			}
		}

		//return first element as a mutable
		T& Front()
		{
			if (size_ > 0)
			{
				return container_[front_index_];
			}
			else
			{
				throw std::underflow_error("FixedQueue<>::Front(): empty queue");
				//std::terminate
			}
		}

		//return capacity
		static size_t capacity() 
		{
			return Capacity;
		}

		//return size
		[[nodiscard]] size_t size() const
		{
			return size_;
		}

	};

} //core

#endif //CORE_CONTAINERS_FIXED_QUEUE_H_}