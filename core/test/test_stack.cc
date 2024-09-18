#include <gtest/gtest.h>
#include <constainers/stack.h>


//what values it takes -> pair of stacks
struct StackOperationFixture : public ::testing::TestWithParam<std::pair<core::Stack<int>, core::Stack<float>>>
{};

//test by itself -> top()
TEST_P(StackOperationFixture, top)
{
	auto [v1, v2] = GetParam();
	const auto result1 = v1.Top();
	const auto result2 = v2.Top();

	EXPECT_EQ(result1, 2);
	EXPECT_FLOAT_EQ(result2, 5.5f);


}

//test by itself -> Pop()
TEST_P(StackOperationFixture, pop)
{
	auto [v1, v2] = GetParam();
	v1.Pop();
	v2.Pop();
	const auto result1 = v1.Top();
	const auto result2 = v2.Top();

	EXPECT_EQ(result1, 1);
	EXPECT_FLOAT_EQ(result2, 1.2f);
}

//test by itself -> Push()
TEST_P(StackOperationFixture, push)
{
	auto [v1, v2] = GetParam();
	v1.Push(5);
	v2.Push(8.5f);

	const auto result1 = v1.Top();
	const auto result2 = v2.Top();

	EXPECT_EQ(result1, 5);
	EXPECT_FLOAT_EQ(result2, 8.5f);

}


//instantiate tes by itself and their specific values
INSTANTIATE_TEST_SUITE_P(PositiveNumbers, StackOperationFixture, testing::Values(
	std::make_pair([]
		{core::Stack<int> q1;
q1.Push(0);
q1.Push(1);
q1.Push(2);
return q1;
		}(), []
			{
				core::Stack<float> q2;
				q2.Push(1.2f);
				q2.Push(5.5f);
				return q2;
			}())
));