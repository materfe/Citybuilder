#ifndef CORE_CONTAINERS_STACK_H_
#define CORE_CONTAINERS_STACK_H_
#include <vector>

namespace core
{
	/**
	 * \brief home made stack that uses a std::vector
	 * \tparam T 
	 */
	template <typename T>
	class Stack {
	private:
		std::vector<T> container_;

	public:

		// Push an element onto the stack
		void Push(const T& value)
		{
			container_.push_back(value);
		}

		// Pop an element from the stack
		void Pop() {
			if (!container_.empty())
			{
				container_.pop_back();
			}
			else
			{
				throw std::out_of_range("Stack<>::Pop(): empty stack");
				//std::terminate
			}
		}

		// Get the last added element
		[[nodiscard]] const T& Top() const
		{
			if (!container_.empty())
			{
				return container_.back();
			}
			else
			{
				throw std::out_of_range("Stack<>::Top(): empty stack");
				//std::terminate
			}
		}

		//get the last element as a mutable
		T& Top()
		{
			if (!container_.empty())
			{
				return container_.back();
			}
			else
			{
				throw std::out_of_range("Stack<>::Top(): empty stack");
				//std::terminate
			}
		}


	};
} //core

#endif // CORE_CONTAINERS_STACK_H_
