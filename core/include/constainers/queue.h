#ifndef CORE_CONTAINERS_QUEUE_H_
#define CORE_CONTAINERS_QUEUE_H_
#include <vector>

namespace core
{
	/**
	 * \brief home made queue that does not use dequeue
	 * \tparam T
	 */
	template<typename T>
	class Queue {
	private:
		std::vector<T> datas_;

	public:

		//std::initializer_list<T> list -> vector = {......} puis data.reserve and data = list

		//return first element
		[[nodiscard]] const T& Front() const
		{
			if (datas_.empty())
			{
				throw std::out_of_range("Queue is empty");
				//std::terminate
			}
			else
			{
				return datas_.begin();
			}
		}

		//return first element but mutable
		T& Front()
		{
			if (datas_.empty())
			{
				throw std::out_of_range("Queue is empty");
				//std::terminate
			}
			else
			{
				return *datas_.begin();
			}
		}

		//add an element at the end of the vector
		void Push(const T& value)
		{
			//reallocations
			if (datas_.size() >= datas_.capacity())
			{
				datas_.reserve(datas_.capacity() * 2);
			}

			datas_.push_back(value);
		}

		//erase the first element
		void Pop()
		{
			if (datas_.empty())
			{
				throw std::out_of_range("Queue is empty");
				//std::terminate
			}

			datas_.erase(datas_.begin());
		}


		[[nodiscard]] auto Capacity() const
		{
			return datas_.capacity();
		}

	};

} //core

#endif //CORE_CONTAINERS_QUEUE_H_}