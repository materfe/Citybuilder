#ifndef CORE_CONTAINERS_FIXED_STACK_H_
#define CORE_CONTAINERS_FIXED_STACK_H_
#include <stdexcept>

namespace core
{
	/**
	 * \brief a stack that uses an array and a specific max capacity
	 * \tparam T 
	 * \tparam Capacity max capacity
	 */
	template <typename T, const int Capacity>
	class FixedStack
	{
	private:
		T container_[Capacity];
		int top_index_;

	public:
		// Constructor to initialize the stack -> Top index
		FixedStack() : top_index_(0) {}

		// Push an element onto the stack
		void Push(const T& value)
		{
			if (top_index_ < Capacity)
			{
				container_[top_index_++] = value;
			}
			else
			{
				throw std::overflow_error("FixedStack<>::Push(): stack overflow");
				//std::terminate
			}
		}

		// Pop an element from the stack
		void Pop()
		{
			if (top_index_ > 0)
			{
				--top_index_;
			}
			else
			{
				throw std::underflow_error("FixedStack<>::Pop(): stack underflow");
				//std::terminate
			}
		}

		// returns the last added element
		[[nodiscard]] const T& Top() const
		{
			if (top_index_ > 0)
			{
				return container_[top_index_ - 1];
			}
			else
			{
				throw std::underflow_error("FixedStack<>::Top(): empty stack");
				//std::terminate
			}
		}

		//get last added element as a mutable
		T& Top()
		{
			if (top_index_ > 0)
			{
				return container_[top_index_ - 1];
			}
			else
			{
				throw std::underflow_error("FixedStack<>::Top(): empty stack");
				//std::terminate
			}
		}
	};
} //core

#endif // CORE_CONTAINERS_FIXED_STACK_H_
