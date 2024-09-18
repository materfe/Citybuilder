#include <gtest/gtest.h>
#include <constainers/fixed_vector.h>


//what values it takes -> pair of fixedqueue
struct FixedVectorOperationFixture : public ::testing::TestWithParam<std::pair<core::FixedVector<int, 1, 1, 1>,
	core::FixedVector<float, 1, 1, 1>>>
{};

//test by itself -> Capacity
TEST_P(FixedVectorOperationFixture, Capacity)
{
	core::FixedVector<int, 50, 5, 1> s1;

	auto result = s1.Capacity();

	EXPECT_EQ(result, 50);

	//forcing realocation
	for (int i = 0; i < 60; i++)
	{
		s1.PushBack(1);
	}

	result = s1.Capacity();
	EXPECT_EQ(result, 50 * 5 / 1); //formula of the realocation
}

//test by itself -> Size()
TEST_P(FixedVectorOperationFixture, size)
{
	core::FixedVector<int, 50, 2, 2> s1;

	auto result = s1.Size();

	EXPECT_EQ(result, 0);

	//adding 41 elements -> Size + 41
	for (int i = 0; i < 41; i++)
	{
		s1.PushBack(1);
	}

	result = s1.Size();
	EXPECT_EQ(result, 41);

}

//test by itself -> PushBack()
TEST_P(FixedVectorOperationFixture, push_back)
{
	core::FixedVector<int, 5,5,1> s1;

	auto size_result = s1.Size();

	s1.PushBack(1000);
	s1.PushBack(1);
	s1.PushBack(2);

	//check if push done correctly
	size_result = s1.Size();
	EXPECT_EQ(size_result, 3);

	//forcing reallocation
	s1.PushBack(1);
	s1.PushBack(1);
	s1.PushBack(1);

	const auto capacity = s1.Capacity();
	EXPECT_EQ(capacity, 5 * 5 / 1); //seeing if it did reallocate proprely
}

//test by itself -> operator[]
TEST_P(FixedVectorOperationFixture, op)
{
	core::FixedVector<int, 5, 8, 2> s1;

	s1.PushBack(1);
	s1.PushBack(2);
	s1.PushBack(5);
	s1.PushBack(7);
	s1.PushBack(1);

	//check every slot
	const auto reslut1 = s1[0]; //should be 1
	const auto reslut2 = s1[1]; //should be 2
	const auto reslut3 = s1[2]; //should be 5
	const auto reslut4 = s1[3]; //should be 7
	const auto reslut5 = s1[4]; //should be 1

	//compare every result with every slot
	EXPECT_EQ(reslut1, 1);
	EXPECT_EQ(reslut2, 2);
	EXPECT_EQ(reslut3, 5);
	EXPECT_EQ(reslut4, 7);
	EXPECT_EQ(reslut5, 1);
}

//test by itself -> Reserve()
TEST_P(FixedVectorOperationFixture, reserve)
{
	core::FixedVector<int, 5, 8, 2> s1;

	s1.PushBack(1);
	s1.PushBack(2);
	s1.PushBack(5);
	s1.PushBack(7);
	s1.PushBack(1);

	//check everything is alright
	auto result = s1.Capacity();
	EXPECT_EQ(result, 5);

	//check if Reserve works proprely
	s1.Reserve(50);
	result = s1.Capacity();
	EXPECT_EQ(result, 50);
}

//instantiate tes by itself and their specific values
INSTANTIATE_TEST_SUITE_P(PositiveNumbers, FixedVectorOperationFixture, testing::Values(
	std::make_pair([]
		{core::FixedVector<int, 1, 1, 1> q1;
return q1;
		}(), []
			{
				core::FixedVector<float, 1, 1, 1> q2;
				return q2;
			}())
));