#include "Vector4.h"
#include "Maths.h"

float Vector4::lengthSq() const
{
	return (x * x + y * y + z * z + w * w);
}

float Vector4::length() const
{
	return (Maths::sqrt(lengthSq()));
}

void Vector4::normalize()
{
	float len = length();
	x /= len;
	y /= len;
	z /= len;
    w /= len;
}
