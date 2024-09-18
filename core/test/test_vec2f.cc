#include <maths/vec2f.h>
#include <gtest/gtest.h>


//what values it takes -> pair of Vec2f
struct Vec2fOperationFixture : public ::testing::TestWithParam<std::pair<core::Vec2f, core::Vec2f>>
{};

//test by itself -> add
TEST_P(Vec2fOperationFixture, add)
{
	auto [v1, v2] = GetParam();
	const auto result = v1 + v2;
	EXPECT_EQ(result.x, v1.x + v2.x);
	EXPECT_EQ(result.y, v1.y + v2.y);
}

//test by itself -> sub
TEST_P(Vec2fOperationFixture, sub)
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
TEST_P(Vec2fOperationFixture, perpendicular)
{
	//substraction
	auto [v1, v2] = GetParam();
	const auto p1 = v1.Perpendicular();
	const auto p2 = v2.Perpendicular();
	EXPECT_EQ(core::Vec2f::Dot(v1, p1), 0);
	EXPECT_EQ(core::Vec2f::Dot(v2, p2), 0);
}

TEST_P(Vec2fOperationFixture, multiply)
{
	//substraction
	auto [v1, v2] = GetParam();
	const auto p1 = v1 * 2.2f;
	const auto p2 = v2 * 2.5f;
	const auto p3 = 2.5f * v2;

	EXPECT_FLOAT_EQ(p1.x, v1.x * 2.2f);
	EXPECT_FLOAT_EQ(p1.y, v1.y * 2.2f);
	EXPECT_FLOAT_EQ(p2.x, v2.x * 2.5f);
	EXPECT_FLOAT_EQ(p2.y, v2.y * 2.5f);

	EXPECT_FLOAT_EQ(p3.y, v2.y * 2.5f);
	EXPECT_FLOAT_EQ(p3.x, v2.x * 2.5f);
}

//test by itself -> calculate multiply
TEST_P(Vec2fOperationFixture, divide)
{
	//substraction
	auto [v1, v2] = GetParam();
	const auto p1 = v1 / 2.2f;
	const auto p2 = v2 / 2.5f;
	const auto p3 = 2.5f / v2;

	EXPECT_FLOAT_EQ(p1.x, v1.x / 2.2f);
	EXPECT_FLOAT_EQ(p1.y, v1.y / 2.2f);
	EXPECT_FLOAT_EQ(p2.x, v2.x / 2.5f);
	EXPECT_FLOAT_EQ(p2.y, v2.y / 2.5f);

	EXPECT_FLOAT_EQ(p3.y, 2.5f / v2.y);
	EXPECT_FLOAT_EQ(p3.x, 2.5f / v2.x);
}

//test by itself -> calculate Lerp
TEST_P(Vec2fOperationFixture, Lerp)
{
	//substraction a.x + (b.x - a.x) * t
	auto [v1, v2] = GetParam();
	constexpr float t = 0.0f;
	const auto p1 = v1.Lerp(v1, v2, t);
	const auto p2 = v1.Lerp(v1, v2, t +1.0f);
	EXPECT_FLOAT_EQ(p1.x, v1.x + (v2.x - v1.x) * t);
	EXPECT_FLOAT_EQ(p1.y, v1.y + (v2.y - v1.y) * t);


	if constexpr (t == 0.0f)
	{
		EXPECT_FLOAT_EQ(p1.x, v1.x);
	}
	else if constexpr (t == 1.0f)
	{
		EXPECT_FLOAT_EQ(p2.x, v2.x);
	}

}

//test by itself -> calculate Normalise vector and also check Magnitude/SqrMagnitude
TEST_P(Vec2fOperationFixture, Normalise)
{
	auto [v1, v2] = GetParam();
	const auto p1 = v1.Normalise();
	EXPECT_FLOAT_EQ(p1.Magnitude(), 1.0f);
}

//test by itself -> calculate Magnitude/SqrMagnitude
TEST_P(Vec2fOperationFixture, Magnitude)
{
	auto [v1, v2] = GetParam();
	const auto p1 = v1.Magnitude();
	const auto p2 = v2.SqrMagnitude();

	EXPECT_FLOAT_EQ(p1, std::sqrt(v1.x * v1.x + v1.y * v1.y));
	EXPECT_FLOAT_EQ(p2, v2.x*v2.x + v2.y * v2.y);
}


//instantiate tes by itself and their specific values
INSTANTIATE_TEST_SUITE_P(PositiveNumbers, Vec2fOperationFixture, testing::Values(
	std::pair{ core::Vec2f{1.3f,3.5f}, core::Vec2f{2.0f,4.8f} },
	std::pair{ core::Vec2f{1.5f,3.72f}, core::Vec2f{0.0f,0.0f} }));