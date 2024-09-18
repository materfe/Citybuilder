#include <gtest/gtest.h>
#include <constainers/queue.h>


//what values it takes -> pair of queues
struct QueueOperationFixture : public ::testing::TestWithParam<std::pair<core::Queue<int>, core::Queue<float>>>
{};

//test by itself -> front()
TEST_P(QueueOperationFixture, front)
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
TEST_P(QueueOperationFixture, pop)
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
TEST_P(QueueOperationFixture, push)
{
	auto [v1, v2] = GetParam();
	v1.Push(5);
	v2.Push(8.5f);

	v1.Pop();
	v1.Pop();
	v1.Pop();
	v2.Pop();
	v2.Pop();

	const auto result1 = v1.Front();
	const auto result2 = v2.Front();

	EXPECT_EQ(result1, 5);
	EXPECT_FLOAT_EQ(result2, 8.5f);

}


//instantiate tes by itself and their specific values
INSTANTIATE_TEST_SUITE_P(PositiveNumbers, QueueOperationFixture, testing::Values(
	std::make_pair([]
		{core::Queue<int> q1;
q1.Push(0);
q1.Push(1);
q1.Push(2);
return q1;
		}(), []
			{
				core::Queue<float> q2;
				q2.Push(1.2f);
				q2.Push(5.5f);
				return q2;
			}())
));