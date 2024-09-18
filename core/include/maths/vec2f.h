#ifndef CORE_MATHS_VEC2F_H_
#define CORE_MATHS_VEC2F_H_
#include <cmath>
#include <complex>
#include <SFML/System/Vector2.hpp>

namespace core
{
	/**
	 * \brief Vec2f is a struct that allow basic maths
	 */
	struct Vec2f
	{
		float x = 0, y = 0;

		//Vec2f() = default;

		//// Constructor from Vec2f
		//explicit Vec2f(const Vec2i& vec) : x(static_cast<float>(vec.x)), y(static_cast<float>(vec.y)) {}

		//// Constructor
		//Vec2f(float x, float y) : x(x), y(y) {}

		//add system
		constexpr Vec2f operator+(Vec2f other)const
		{
			return { x + other.x , y + other.y };
		}

		//sub system
		constexpr Vec2f operator-(Vec2f other)const
		{
			return { x - other.x, y - other.y };
		}

		//negative numbers system
		constexpr Vec2f operator-()const
		{
			return { -x, -y };
		}

		//multiply
		constexpr Vec2f operator*(float scalaire) const
		{
			return { x * scalaire, y * scalaire };
		}

		//divide
		constexpr Vec2f operator/(float scalar) const
		{
			if (scalar == 0)
			{
				//can't devide by 0
				std::terminate();
			}
			else
			{
				return { x / scalar, y / scalar };
			}
		}

		//dot product (produit scalaire) system
		static constexpr float Dot(Vec2f v1, Vec2f v2)
		{
			return v1.x * v2.x + v1.y * v2.y;
		}

		//perpenducular
		[[nodiscard]] constexpr Vec2f Perpendicular() const //FAIRE perpendicular 2
		{
			return { -y, x };
		}

		//Lerp
		[[nodiscard]] static constexpr Vec2f Lerp(Vec2f a, Vec2f b, float t)
		{
			return { a.x + (b.x - a.x) * t, a.y + (b.y - a.y) * t };
		}

		//normalise and sqr normalise your vector
		Vec2f  Normalise() const
		{
			const float norm_x = x == 0 ? 0 : x / Magnitude();
			const float norm_y = y == 0 ? 0 : y / Magnitude();
			return { norm_x, norm_y };

		}


		//calculate magnitude and sqr magnitude
		[[nodiscard]] float Magnitude() const
		{
			const float length = std::sqrt(x * x + y * y);
			return  length;
		}

		[[nodiscard]] constexpr float SqrMagnitude() const
		{
			const float length = x * x + y * y;
			return  length;
		}


	}; //struct Vec2i

	//operator for float in left side
	constexpr Vec2f operator*(float t, const Vec2f& vec)
	{
		return { t * vec.x, t * vec.y };
	}
	constexpr Vec2f operator/(float t, const Vec2f& vec)
	{
		return { t /vec.x, t / vec.y };
	}

} //namespace core


[[nodiscard]] inline float squaredMagnitude(sf::Vector2f v)
{
	return  (v.x * v.x + v.y * v.y);
}

[[nodiscard]] inline float Magnitude(sf::Vector2f v)
{
	return  std::sqrt(squaredMagnitude(v));
}

[[nodiscard]] inline sf::Vector2f Normalized(sf::Vector2f v)
{

	// IF/ELSE Style
	float norm_x = 0;
	if (v.x == 0) {
		norm_x = 0;
	}
	else {
		norm_x = v.x / Magnitude(v);
	}

	// Ternary style
	float norm_y = v.y == 0 ? 0 : v.y / Magnitude(v);

	return { norm_x, norm_y };

}


#endif //CORE_MATHS_VEC2I_H_