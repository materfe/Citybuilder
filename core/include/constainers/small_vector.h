#ifndef CORE_CONSTAINERS_SMALL_VECTOR_H_
#define CORE_CONSTAINERS_SMALL_VECTOR_H_
#include <iostream>
#include <stdexcept>

namespace core
{
	/**
	 * \brief small vector class that works the same as std::vector but on the stack in the memory
	 * \tparam T 
	 * \tparam Capacity 
	 */
	template<typename T, size_t Capacity>
	class SmallVector
	{
	private:
		size_t capacity_ = Capacity;
		T* data_ = new T[capacity_];
		size_t size_;
	public:
		SmallVector() : size_(0) {}

		void PushBack(const T& value)
		{
			if (size_ >= capacity_)
			{
				throw std::overflow_error("Vector Capacity exceeded");
			}
			data_[size_] = value;
			size_++;
		}

		T& operator[](size_t index)
		{
			if (index >= size_)
			{
				throw std::out_of_range("Index out of range");
			}
			return data_[index];
		}

		const T& operator[](size_t index) const
		{
			if (index >= size_)
			{
				throw std::out_of_range("Index out of range");
			}
			return data_[index];
		}

		T* Begin()
		{
			if (data_[0] == NULL)
			{
				return nullptr;
			}
			return &data_[0];
		}

		[[nodiscard]] const T* Begin() const
		{
			if (data_[0] == NULL)
			{
				return nullptr;
			}
			return &data_[0];
		}

		T* End()
		{
			if (data_[0] == NULL)
			{
				return nullptr;
			}
			return &data_[size_ - 1];
		}

		[[nodiscard]] const T* End() const
		{
			if (data_[0] == NULL)
			{
				return nullptr;
			}
			return &data_[size_ - 1];
		}

		void Reserve(const size_t new_capacity)
		{
			if (new_capacity <= Capacity)
			{
				return;
			}

			T* new_data = new T[new_capacity];
			for (size_t i = 0; i < size_; ++i)
			{
				new_data[i] = data_[i];
			}

			delete[] data_;
			data_ = new_data;
			capacity_ = new_capacity;
		}

		[[nodiscard]] size_t Size() const
		{
			return size_;
		}

		[[nodiscard]] const T* Front () const
		{
			if (data_[0] != NULL)
			{
				return &data_[0];
			}

			throw std::out_of_range("empty vector");
		}

		T* Front() 
		{
			if (data_[0] != NULL)
			{
				return &data_[0];
			}

			throw std::out_of_range("empty vector");
		}

		[[nodiscard]] size_t getCapacity() const
		{
			return capacity_;
		}
	};
}







#endif
