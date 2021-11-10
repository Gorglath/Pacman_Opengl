#ifndef MATHS_H
#define MATHS_H

#include <limits>
#include <cmath>

namespace Maths
{
	constexpr float pi = 3.1415926535f;
	constexpr float twoPi = pi * 2.0f;
	constexpr float piOver2 = pi / 2.0f;
	constexpr float infinity = std::numeric_limits<float>::infinity();
	constexpr float negInfinity = -std::numeric_limits<float>::infinity();

	inline float toRadians(float degrees)
	{
		return degrees * pi / 180.0f;
	}

	inline float toDegrees(float radians)
	{
		return radians * 180.0f / pi;
	}

	inline bool nearZero(float val, float epsilon = 0.001f)
	{
		if (fabs(val) <= epsilon)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	template <typename T>
	T max(const T& a, const T& b)
	{
		return (a < b ? b : a);
	}

	template <typename T>
	T min(const T& a, const T& b)
	{
		return (a < b ? a : b);
	}

	template <typename T>
	T clamp(const T& value, const T& lower, const T& upper)
	{
		return min(upper, max(lower, value));
	}

	inline float abs(float value)
	{
		return fabs(value);
	}

	inline float cos(float angle)
	{
		return cosf(angle);
	}

	inline float sin(float angle)
	{
		return sinf(angle);
	}

	inline float tan(float angle)
	{
		return tanf(angle);
	}

	inline float acos(float value)
	{
		return acosf(value);
	}

	inline float atan2(float y, float x)
	{
		return atan2f(y, x);
	}

	inline float cot(float angle)
	{
		return 1.0f / tan(angle);
	}

	inline float lerp(float a, float b, float f)
	{
		return a + f * (b - a);
	}

	inline float sqrt(float value)
	{
		return sqrtf(value);
	}

	inline float fmod(float numer, float denom)
	{
		return std::fmod(numer, denom);
	}

	inline int round(float num)
	{
		return static_cast<int>(std::round(num));
	}
}

#endif