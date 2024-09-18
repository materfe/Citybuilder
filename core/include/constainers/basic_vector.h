#ifndef CORE_CONTAINERS_BASIC_VECTOR_H_
#define CORE_CONTAINERS_BASIC_VECTOR_H_
#include <variant>
#include <array>
#include <vector>


namespace core
{
    // Define the threshold for using an array versus a vector
    constexpr size_t kArrayThreshold = 10;

    /**
     * \brief vector class that switches on the stack in memory or the heap depending on a capacity
     * \tparam T 
     * \tparam Capacity 
     */
    template <typename T, size_t Capacity>
    class BasicVector
	{
    private:
        using ArrayType = std::array<T, Capacity>;
        using VectorType = std::vector<T>;

        std::variant<ArrayType, VectorType> storage_;
        size_t size_;

    public:
        BasicVector()
    	{
            if (Capacity <= kArrayThreshold)
            {
                storage_ = ArrayType{};
            }
            else
            {
                storage_ = VectorType{};
            }
            size_ = 0;
        }

        void PushBack(const T& value)
    	{
            if (Capacity <= kArrayThreshold) 
            {
                //get the array of the variant
                auto& arr = std::get<ArrayType>(storage_);

                for (size_t i = 0; i < Capacity; ++i)
                {
                    //if value = default template value (like NULL) then do some
                    if (arr[i] == T{}) 
                    {
                        arr[i] = value;
                        size_++;
                        break;
                    }
                }
            }
            else 
            {
                auto& vec = std::get<VectorType>(storage_);
                vec.push_back(value);
            }
        }

        T& Front()
        {
	        if (Capacity <= kArrayThreshold)
	        {
                auto& array = std::get<ArrayType>(storage_);

                if(array[0] == T{})
                {
                    throw std::out_of_range("empty array");
                }
                return array[0];
	        }
	        else
	        {
                auto& vec = std::get<VectorType>(storage_);

                if (vec[0] == T{})
                {
                    throw std::out_of_range("empty vector");
                }
                return vec[0];
	        }
        }


        [[nodiscard]] size_t Size() const
        {
            return size_;
        }

        T& operator[](size_t index)
    	{
            if (Capacity <= kArrayThreshold)
            {
                return std::get<ArrayType>(storage_)[index];
            }
            else
            {
                return std::get<VectorType>(storage_)[index];
            }
        }

        const T& operator[](size_t index) const
    	{
            if (Capacity <= kArrayThreshold)
            {
                return std::get<ArrayType>(storage_)[index];
            }
            else
            {
                return std::get<VectorType>(storage_)[index];
            }
        }
    };
} //core
#endif //CORE_CONTAINERS_BASIC_VECTOR_H_
