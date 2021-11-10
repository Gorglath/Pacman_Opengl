#ifndef MATHS_VECTOR3_H
#define MATHS_VECTOR3_H
#include "Maths.h"

class Vector3
{

public:
	float x { 0.0f };
	float y { 0.0f };
	float z { 0.0f };

	Vector3() = default;

	explicit Vector3(float xP, float yP, float zP)
		:x { xP} , y { yP }, z {zP } {}

	void set(float xP, float yP, float zP);
	float lengthSq() const;
	float length() const;
	void normalize();

	const float* getAsFloatPtr() const
	{
		return reinterpret_cast<const float*>(&x);
	}

	// Vector addition (a + b)
	friend Vector3 operator+(const Vector3& a, const Vector3& b)
	{
		return Vector3(a.x + b.x, a.y + b.y, a.z + b.z);
	}

	// Vector subtraction (a - b)
	friend Vector3 operator-(const Vector3& a, const Vector3& b)
	{
		return Vector3(a.x - b.x, a.y - b.y, a.z - b.z);
	}

	// Component-wise multiplication
	friend Vector3 operator*(const Vector3& left, const Vector3& right)
	{
		return Vector3(left.x * right.x, left.y * right.y, left.z * right.z);
	}

	// Scalar multiplication
	friend Vector3 operator*(const Vector3& vec, float scalar)
	{
		return Vector3(vec.x * scalar, vec.y * scalar, vec.z * scalar);
	}

	// Scalar multiplication
	friend Vector3 operator*(float scalar, const Vector3& vec)
	{
		return Vector3(vec.x * scalar, vec.y * scalar, vec.z * scalar);
	}

	// Scalar *=
	Vector3& operator*=(float scalar)
	{
		x *= scalar;
		y *= scalar;
		z *= scalar;
		return *this;
	}

	// Vector +=
	Vector3& operator+=(const Vector3& right)
	{
		x += right.x;
		y += right.y;
		z += right.z;
		return *this;
	}

	// Vector -=
	Vector3& operator-=(const Vector3& right)
	{
		x -= right.x;
		y -= right.y;
		z -= right.z;
		return *this;
	}

	// Normalize the provided vector
	static Vector3 normalize(const Vector3& vec)
	{
		Vector3 temp = vec;
		temp.normalize();
		return temp;
	}

	// Dot product between two vectors (a dot b)
	static float dot(const Vector3& a, const Vector3& b)
	{
		return (a.x * b.x + a.y * b.y + a.z * b.z);
	}

	// Cross product between two vectors (a cross b)
	static Vector3 cross(const Vector3& a, const Vector3& b)
	{
		Vector3 temp;
		temp.x = a.y * b.z - a.z * b.y;
		temp.y = a.z * b.x - a.x * b.z;
		temp.z = a.x * b.y - a.y * b.x;
		return temp;
	}

	// Lerp from A to B by f
	static Vector3 lerp(const Vector3& a, const Vector3& b, float f)
	{
		return Vector3(a + f * (b - a));
	}

	// Reflect V about (normalized) N
	static Vector3 reflect(const Vector3& v, const Vector3& n)
	{
		return v - 2.0f * Vector3::dot(v, n) * n;
	}

	static float distance(const Vector3& a, const Vector3& b)
	{
		return sqrt(pow((b.x - a.x),2) + pow((b.y - a.y),2) + pow((b.z - a.z),2));
	}
	static Vector3 transform(Vector3& vec, class Matrix4& mat, float w = 1.0f);

	// This will transform the vector and renormalize the w component
	static Vector3 transformWithPerspDiv(Vector3& vec, class Matrix4& mat, float w = 1.0f);

	// Transform a Vector3 by a quaternion
	static Vector3 transform(const Vector3& v, const class Quaternion& q);

	static const Vector3 zero;
	static const Vector3 unitX;
	static const Vector3 unitY;
	static const Vector3 unitZ;
	static const Vector3 negUnitX;
	static const Vector3 negUnitY;
	static const Vector3 negUnitZ;
	static const Vector3 infinity;
	static const Vector3 negInfinity;
};

#endif
