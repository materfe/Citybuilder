#include <gtest/gtest.h>
#include <constainers/basic_vector.h>


//what values it takes -> pair of fixedqueue
struct BasicVectorOperationFixture : public ::testing::TestWithParam<std::pair<core::BasicVector<int, 3>,
	core::BasicVector<float, 3>>>
{};

//test by itself -> Front()
TEST_P(BasicVectorOperationFixture, Front)
{
	core::BasicVector<int, 2> s1;

	s1.PushBack(1);
	s1.PushBack(2);

	const auto result = s1.Front();

	EXPECT_EQ(result, 1);
}


//test by itself -> size()
TEST_P(BasicVectorOperationFixture, size)
{
	core::BasicVector<int, 3> s1;

	auto size_result = s1.Size();

	EXPECT_EQ(size_result, 0);

	s1.PushBack(1000);
	s1.PushBack(1);
	s1.PushBack(2);

	size_result = s1.Size();

	EXPECT_EQ(size_result, 3);
}

//test by itself -> push_back()
TEST_P(BasicVectorOperationFixture, push_back)
{
	core::BasicVector<int, 3> s1;

	auto size_result = s1.Size();

	EXPECT_EQ(size_result, 0);

	s1.PushBack(1000);
	s1.PushBack(1);
	s1.PushBack(2);

	size_result = s1.Size();

	const auto result = s1.Front();

	EXPECT_EQ(size_result, 3);
	EXPECT_EQ(result, 1000);
}

//test by itself -> operator[]
TEST_P(BasicVectorOperationFixture, op)
{
	core::BasicVector<int, 5> s1;

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

//instantiate tes by itself and their specific values
INSTANTIATE_TEST_SUITE_P(PositiveNumbers, BasicVectorOperationFixture, testing::Values(
	std::make_pair([]
		{core::BasicVector<int, 3> q1;
return q1;
		}(), []
			{
				core::BasicVector<float, 3> q2;
				return q2;
			}())
));