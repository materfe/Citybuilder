#include <gtest/gtest.h>
#include <constainers/fixed_queue.h>


//what values it takes -> pair of fixedqueue
struct FixedQueueOperationFixture : public ::testing::TestWithParam<std::pair<core::FixedQueue<int,3>, core::FixedQueue<float,3>>>
{};

//test by itself -> Front()
TEST_P(FixedQueueOperationFixture, front)
{
	auto [v1, v2] = GetParam();
	const auto result1 = v1.Front();
	const auto result2 = v2.Front();

	EXPECT_EQ(result1, 0);
	EXPECT_EQ(result2, 1.2f);


	/*v1.Pop();
	v1.Pop();
	v1.Pop();

	const auto result4 = v1.Front();

	EXPECT_THROW(result4, std::out_of_range);*/

}

//test by itself -> Pop()
TEST_P(FixedQueueOperationFixture, pop)
{
	auto [v1, v2] = GetParam();
	v1.Pop();
	v2.Pop();
	const auto result1 = v1.Front();
	const auto result2 = v2.Front();

	EXPECT_EQ(result1, 1);
	EXPECT_FLOAT_EQ(result2, 5.5f);
}

//test by itself -> Push()
TEST_P(FixedQueueOperationFixture, push)
{
	auto [v1, v2] = GetParam();

	//Pop all initial numbers
	v1.Pop();
	v1.Pop();
	v1.Pop();
	//Pop all initial numbers
	v2.Pop();
	v2.Pop();
	v2.Pop();

	v1.Push(5);
	v2.Push(8.5f);

	const auto result1 = v1.Front();
	const auto result2 = v2.Front();

	EXPECT_EQ(result1, 5);
	EXPECT_FLOAT_EQ(result2, 8.5f);

	const auto result5 = v1.capacity();

	EXPECT_EQ(result5, 3);

}

//test that the capacity is fine
TEST_P(FixedQueueOperationFixture, capacity)
{
	core::FixedQueue<int, 50> fixed;

	//add 50 elements
	for (int i = 1; i < 51; i++)
	{
		fixed.Push(i);
	}

	//get capacity and size
	auto capacity = fixed.capacity();
	auto size = fixed.size();

	EXPECT_EQ(capacity, 50);
	EXPECT_EQ(size, 50);

	//take out 25 elements
	for (int i = 0; i < 25; i++)
	{
		fixed.Pop();
	}

	//get capacity and elements
	capacity = fixed.capacity();
	size = fixed.size();

	EXPECT_EQ(capacity, 50);
	EXPECT_EQ(size, 25);

	//add again 25 elements
	for (int i = 0; i < 25; i++)
	{
		fixed.Push(i);
	}

	//get elements
	capacity = fixed.capacity();
	size = fixed.size();

	EXPECT_EQ(capacity, 50);
	EXPECT_EQ(size, 50);
}

//instantiate tes by itself and their specific values
INSTANTIATE_TEST_SUITE_P(PositiveNumbers, FixedQueueOperationFixture, testing::Values(
	std::make_pair([]
		{core::FixedQueue<int,3> q1;
q1.Push(0);
q1.Push(1);
q1.Push(2);
return q1;
		}(), []
			{
				core::FixedQueue<float,3> q2;
				q2.Push(1.2f);
				q2.Push(5.5f);
				q2.Push(7.5f);
				return q2;
			}())
));