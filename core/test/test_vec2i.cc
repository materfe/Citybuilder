#include <maths/vec2i.h>

#include <gtest/gtest.h>

//what values it takes -> pair of Vec2i
struct Vec2iOperationFixture : public ::testing::TestWithParam<std::pair<core::Vec2i, core::Vec2i>>
{};

//test by itself -> add
TEST_P(Vec2iOperationFixture, add)
{
	auto [v1, v2] = GetParam();
	const auto result = v1 + v2;
	EXPECT_EQ(result.x, v1.x + v2.x);
	EXPECT_EQ(result.y, v1.y + v2.y);
}

//test by itself -> sub
TEST_P(Vec2iOperationFixture, sub)
{
	//substraction
	auto [v1, v2] = GetParam();
	const auto result = v1 - v2;
	EXPECT_EQ(result.x, v1.x - v2.x);
	EXPECT_EQ(result.y, v1.y - v2.y);

	//nagative numbers
	const auto neg1 = -v1;
	const auto neg2 = -v2;
	EXPECT_EQ(neg1.x, -v1.x);
	EXPECT_EQ(neg2.x, -v2.x);
}

//test by itself -> calculate perpendicular
TEST_P(Vec2iOperationFixture, perpendicular)
{
	//substraction
	auto [v1, v2] = GetParam();
	const auto p1 = v1.Perpendicular();
	const auto p2 = v2.Perpendicular();
	EXPECT_EQ(core::Vec2i::Dot(v1, p1), 0);
	EXPECT_EQ(core::Vec2i::Dot(v2, p2), 0);
}

//test by itself -> calculate multiply
TEST_P(Vec2iOperationFixture, multiply)
{
	//substraction
	auto [v1, v2] = GetParam();
	const auto p1 = v1 * 2;
	const auto p2 = v2 * 2;
	EXPECT_EQ(p1.x, v1.x * 2);
	EXPECT_EQ(p1.y, v1.y * 2);
	EXPECT_EQ(p2.x, v2.x * 2);
	EXPECT_EQ(p2.y, v2.y * 2);
}

//test by itself -> calculate multiply
TEST_P(Vec2iOperationFixture, divide)
{
	//substraction
	auto [v1, v2] = GetParam();
	const auto p1 = v1 / 2;
	const auto p2 = v2 / 2;
	EXPECT_EQ(p1.x, v1.x / 2);
	EXPECT_EQ(p1.y, v1.y / 2);
	EXPECT_EQ(p2.x, v2.x / 2);
	EXPECT_EQ(p2.y, v2.y / 2);
}

//instantiate tes by itself and their specific values
INSTANTIATE_TEST_SUITE_P(PositiveNumbers, Vec2iOperationFixture, testing::Values(
	std::pair{ core::Vec2i{1,3}, core::Vec2i{2,4} }));