#ifndef CORE_CONTAINERS_FIXED_VECTOR_H_
#define CORE_CONTAINERS_FIXED_VECTOR_H_
#include <vector>
#include <stdexcept>

namespace core
{
	/**
	 * \brief home made class that reproduce std::vector but with a manual reallocation system
	 * \tparam T
	 */
	template <typename T, size_t InitialSize, size_t Dividende, size_t Divisor>
	class FixedVector
	{
	private:
		std::vector<T> data_;
		size_t dividende_;
		size_t divisor_;

	public:
		FixedVector()
		{
			dividende_ = Dividende;
			divisor_ = Divisor;

			if (divisor_ == 0)
			{
				throw std::invalid_argument("can not divide by 0");
			}
			data_.reserve(InitialSize);
		}

		void PushBack(const T& value)
		{
			if (data_.size() >= data_.capacity())
			{
				size_t new_capacity = data_.capacity() * dividende_ / divisor_;
				data_.reserve(new_capacity);
			}
			data_.push_back(value);
		}

		T& operator[](size_t index)
		{
			return data_[index];
		}

		const T& operator[](size_t index) const
		{
			return data_[index];
		}

		[[nodiscard]] size_t Size() const
		{
			return data_.size();
		}

		[[nodiscard]] size_t Capacity() const
		{
			return data_.capacity();
		}

		void Reserve(size_t new_capacity)
		{
			data_.reserve(new_capacity);
		}

	};
} //core
#endif //CORE_CONTAINERS_FIXED_VECTOR_H_