#include <gtest/gtest.h>
#include <constainers/small_vector.h>


//what values it takes -> pair of fixedqueue
struct SmallVectorOperationFixture : public ::testing::TestWithParam<std::pair<core::SmallVector<int, 3>,
	core::SmallVector<float, 3>>>
{};

//test by itself -> front()
TEST_P(SmallVectorOperationFixture, front)
{
	core::SmallVector<int, 2> s1;

	s1.PushBack(1);
	s1.PushBack(9);

	const auto result = s1.Front();
	const auto real_result = *result;

	EXPECT_EQ(real_result, 1);
}


//test by itself -> PushBack()
TEST_P(SmallVectorOperationFixture, push_back)
{
	core::SmallVector<int, 3> s1;

	s1.PushBack(1);
	s1.PushBack(2);

	const auto size_result = s1.Size();
	const auto result = s1.Front();
	const auto int_result = *result;

	EXPECT_EQ(size_result, 2);
	EXPECT_EQ(int_result, 1);
}

//test by itself -> operator[]
TEST_P(SmallVectorOperationFixture, op)
{
	core::SmallVector<int, 5> s1;

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

//test by itself -> Begin()/End()
TEST_P(SmallVectorOperationFixture, begin_and_end)
{
	core::SmallVector<int, 3> s1;

	s1.PushBack(1);
	s1.PushBack(700);
	s1.PushBack(2000);

	//get Begin() and End()
	const auto result_begin = s1.Begin();
	const int result_begin_int = *result_begin; //should be 1
	const auto result_end = s1.End();
	const int result_end_int = *result_end; // should be 2000

	EXPECT_EQ(result_begin_int, s1[0]);
	EXPECT_EQ(result_end_int, s1[2]);
}

//test by itself -> capacity and size
TEST_P(SmallVectorOperationFixture, capacity_and_size)
{
	core::SmallVector<int, 3> s1;

	auto capacity_result = s1.getCapacity();
	auto result_size = s1.Size();

	//first check
	EXPECT_EQ(capacity_result, 3);
	EXPECT_EQ(result_size, 0);

	//adding elements
	s1.PushBack(5);
	s1.PushBack(5);

	result_size = s1.Size();
	capacity_result = s1.getCapacity();

	//secound check
	EXPECT_EQ(result_size, 2);
	EXPECT_EQ(capacity_result, 3);
}


//test by itself -> Reserve()
TEST_P(SmallVectorOperationFixture, reserve)
{
	core::SmallVector<int, 5> s1;

	s1.PushBack(1);

	s1.Reserve(7);

	const auto capacity_result = s1.getCapacity();
	const auto front_result = s1.Front();
	const int usable_front_result = *front_result;

	EXPECT_EQ(capacity_result, 7);
	EXPECT_EQ(usable_front_result, 1);


	for(int i = 1; i < 7;i++)
	{
		s1.PushBack(i);
	}
}

//instantiate tes by itself and their specific values
INSTANTIATE_TEST_SUITE_P(PositiveNumbers, SmallVectorOperationFixture, testing::Values(
	std::make_pair([]
		{core::SmallVector<int, 3> q1;
return q1;
		}(), []
			{
				core::SmallVector<float, 3> q2;
				return q2;
			}())
));