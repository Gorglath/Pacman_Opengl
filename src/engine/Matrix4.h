#ifndef MATHS_MATRIX4_H
#define MATHS_MATRIX4_H

#include <memory>
#include "Vector4.h"
#include <array>
#include "Quaternion.h"

using std::array;

// Col major order 4*4 matrix
class Matrix4
{
public:
	array<float, 16> mat;

	Matrix4()
	{
		*this = Matrix4::identity;
	}

	Matrix4(const array<float, 16>& that)
    {
        for(int n = 0; n < 16; ++n) {
			mat[n] = that[n];
		}
    }

	const float* getAsFloatPtr() const
	{
		return reinterpret_cast<const float*>(&mat[0]);
	}

	inline float& operator()(const int i, const int j)
	{
		return mat[i * 4 + j];
	}

	inline Matrix4& operator=(const Matrix4& that)
    {
        for(int n = 0; n < 16; ++n) {
			mat[n] = that.mat[n];
		}
		return *this;
    }

	inline Matrix4 operator+(const Matrix4& that) const
    {
        Matrix4 result;
        int n;
        for (n = 0; n < 16; n++)
            result.mat[n] = mat[n] + that.mat[n];
        return result;
    }

    inline Matrix4& operator+=(const Matrix4& that)
    {
        return (*this = *this + that);
    }

    inline Matrix4 operator-(const Matrix4& that) const
    {
        Matrix4 result;
        int n;
        for (n = 0; n < 16; n++)
            result.mat[n] = mat[n] - that.mat[n];
        return result;
    }

    inline Matrix4& operator-=(const Matrix4& that)
    {
        return (*this = *this - that);
    }

	// Matrix multiplication (a * b)
	friend Matrix4 operator*(Matrix4& a, Matrix4& b)
	{
		Matrix4 retVal;

		retVal(0, 0) = 
		a(0,0) * b(0,0) +
		a(1,0) * b(0,1) +
		a(2,0) * b(0,2) +
		a(3,0) * b(0,3);

		retVal(0, 1) = 
		a(0,1) * b(0,0) +
		a(1,1) * b(0,1) +
		a(2,1) * b(0,2) +
		a(3,1) * b(0,3);

		retVal(0, 2) = 
		a(0,2) * b(0,0) +
		a(1,2) * b(0,1) +
		a(2,2) * b(0,2) +
		a(3,2) * b(0,3);

		retVal(0, 3) = 
		a(0,3) * b(0,0) +
		a(1,3) * b(0,1) +
		a(2,3) * b(0,2) +
		a(3,3) * b(0,3);

		retVal(1, 0) = 
		a(0,0) * b(1,0) +
		a(1,0) * b(1,1) +
		a(2,0) * b(1,2) +
		a(3,0) * b(1,3);

		retVal(1, 1) = 
		a(0,1) * b(1,0) +
		a(1,1) * b(1,1) +
		a(2,1) * b(1,2) +
		a(3,1) * b(1,3);

		retVal(1, 2) = 
		a(0,2) * b(1,0) +
		a(1,2) * b(1,1) +
		a(2,2) * b(1,2) +
		a(3,2) * b(1,3);

		retVal(1, 3) = 
		a(0,3) * b(1,0) +
		a(1,3) * b(1,1) +
		a(2,3) * b(1,2) +
		a(3,3) * b(1,3);

		retVal(2, 0) = 
		a(0,0) * b(2,0) +
		a(1,0) * b(2,1) +
		a(2,0) * b(2,2) +
		a(3,0) * b(2,3);

		retVal(2, 1) = 
		a(0,1) * b(2,0) +
		a(1,1) * b(2,1) +
		a(2,1) * b(2,2) +
		a(3,1) * b(2,3);

		retVal(2, 2) = 
		a(0,2) * b(2,0) +
		a(1,2) * b(2,1) +
		a(2,2) * b(2,2) +
		a(3,2) * b(2,3);

		retVal(2, 3) = 
		a(0,3) * b(2,0) +
		a(1,3) * b(2,1) +
		a(2,3) * b(2,2) +
		a(3,3) * b(2,3);

		retVal(3, 0) = 
		a(0,0) * b(3,0) +
		a(1,0) * b(3,1) +
		a(2,0) * b(3,2) +
		a(3,0) * b(3,3);

		retVal(3, 1) = 
		a(0,1) * b(3,0) +
		a(1,1) * b(3,1) +
		a(2,1) * b(3,2) +
		a(3,1) * b(3,3);

		retVal(3, 2) = 
		a(0,2) * b(3,0) +
		a(1,2) * b(3,1) +
		a(2,2) * b(3,2) +
		a(3,2) * b(3,3);

		retVal(3, 3) = 
		a(0,3) * b(3,0) +
		a(1,3) * b(3,1) +
		a(2,3) * b(3,2) +
		a(3,3) * b(3,3);

		return retVal;
	}

	Matrix4 operator*=(Matrix4& right)
	{
		Matrix4 retVal = *this * right;
		return retVal;
	}

	// Matrix4 operator*=(Matrix4& a,Vector4 b)
	// {
	// 	Matrix4 retVal;

	// 	retval(0,0) = a(0,0) * b()
	// }
	// Invert the matrix - super slow
	void invert();

	Vector3 getTranslation() const
	{

		return Vector3(mat[12], mat[13], mat[14]);
	}

	Vector3 getXAxis() const
	{
		return Vector3::normalize(Vector3(mat[0], mat[1], mat[2]));
	}

	Vector3 getYAxis() const
	{
		return Vector3::normalize(Vector3(mat[4], mat[5], mat[6]));
	}

	Vector3 getZAxis() const
	{
		return Vector3::normalize(Vector3(mat[8], mat[9], mat[10]));
	}

	Vector3 getScale() const
	{
		Vector3 retVal;
		retVal.x = Vector3(mat[0], mat[1], mat[2]).length();
		retVal.y = Vector3(mat[4], mat[5], mat[6]).length();
		retVal.z = Vector3(mat[8], mat[9], mat[10]).length();
		return retVal;
	}

	static Matrix4 createScale(float xScale, float yScale, float zScale)
	{
		array<float, 16> temp =
		{
			xScale, 0.0f, 0.0f, 0.0f,
			0.0f, yScale, 0.0f, 0.0f,
			0.0f, 0.0f, zScale, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		};
		return Matrix4(temp);
	}

	static Matrix4 createScale(const Vector3& scaleVector)
	{
		return createScale(scaleVector.x, scaleVector.y, scaleVector.z);
	}

	static Matrix4 createScale(float scale)
	{
		return createScale(scale, scale, scale);
	}

	static Matrix4 createRotationX(float theta)
	{
		array<float, 16> temp =
		{
			1.0f, 0.0f, 0.0f , 0.0f,
			0.0f, Maths::cos(theta), -Maths::sin(theta), 0.0f,
			0.0f, Maths::sin(theta), Maths::cos(theta), 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f,
		};
		return Matrix4(temp);
	}

	static Matrix4 createRotationY(float theta)
	{
		array<float, 16> temp =
		{
			Maths::cos(theta), 0.0f, Maths::sin(theta), 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			-Maths::sin(theta), 0.0f, Maths::cos(theta), 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f,
		};
		return Matrix4(temp);
	}

	static Matrix4 createRotationZ(float theta)
	{
		array<float, 16> temp =
		{
			Maths::cos(theta), -Maths::sin(theta), 0.0f, 0.0f,
			Maths::sin(theta), Maths::cos(theta), 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f,
		};
		return Matrix4(temp);
	}

	static Matrix4 createTranslation(const Vector3& trans)
	{
		array<float, 16> temp =
		{
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			trans.x, trans.y, trans.z, 1.0f
		};
		return Matrix4(temp);
	}

	static Matrix4 createSimpleViewProj(float width, float height)
	{
		array<float, 16> temp =
		{
			2.0f / width, 0.0f, 0.0f, 0.0f,
			0.0f, 2.0f / height, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 1.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		};
		return Matrix4(temp);
	}

	static Matrix4 createFromQuaternion(const Quaternion& q)
	{
		array<float, 16> temp;
		temp[0] = 1.0f - 2.0f * q.y * q.y - 2.0f * q.z * q.z;
		temp[1] = 2.0f * q.x * q.y - 2.0f * q.w * q.z;
		temp[2] = 2.0f * q.x * q.z + 2.0f * q.w * q.y;
		temp[3] = 0.0f;

		temp[4] = 2.0f * q.x * q.y + 2.0f * q.w * q.z;
		temp[5] = 1.0f - 2.0f * q.x * q.x - 2.0f * q.z * q.z;
		temp[6] = 2.0f * q.y * q.z - 2.0f * q.w * q.x;
		temp[7] = 0.0f;

		temp[8] = 2.0f * q.x * q.z - 2.0f * q.w * q.y;
		temp[9] = 2.0f * q.y * q.z - 2.0f * q.w * q.x;
		temp[10] = 1.0f - 2.0f * q.x * q.x - 2.0f * q.y * q.y;
		temp[11] = 0.0f;

		temp[12] = 0.0f;
		temp[13] = 0.0f;
		temp[14] = 0.0f;
		temp[15] = 1.0f;

		return Matrix4(temp);
	}

	static Matrix4 createLookAt(const Vector3& eye, const Vector3& target, const Vector3& up)
	{
		Vector3 zaxis = Vector3::normalize(eye - target);
		Vector3 normalizedUp = Vector3::normalize(up);
		Vector3 xaxis = Vector3::normalize(Vector3::cross(normalizedUp, zaxis));
		Vector3 yaxis = Vector3::normalize(Vector3::cross(zaxis, xaxis));

		array<float, 16> temp =
		{
			xaxis.x, yaxis.x, zaxis.x, 0.0f,
			xaxis.y, yaxis.y, zaxis.y, 0.0f,
			xaxis.z, yaxis.z, zaxis.z, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		};
		Matrix4 lookAtRotation { temp };
		Matrix4 eyeTranslation = Matrix4::createTranslation(Vector3(-eye.x, -eye.y, -eye.z));
		auto res = lookAtRotation * eyeTranslation;
		return res;
	}

	static Matrix4 createOrtho(float width, float height, float near, float far)
	{
		array<float, 16> temp =
		{
			2.0f / width, 0.0f, 0.0f, 0.0f,
			0.0f, 2.0f / height, 0.0f, 0.0f,
			0.0f, 0.0f, 2.0f / (near - far), 0.0f,
			0.0f, 0.0f, (far + near) / (far - far), 1.0f
		};
		return Matrix4(temp);
	}

	static Matrix4 createPerspectiveFOV(float fovY, float width, float height, float near, float far)
	{
		float yScale = Maths::cot(fovY / 2.0f);
		float xScale = yScale * height / width;
		array<float, 16> temp =
		{
			xScale, 0.0f, 0.0f, 0.0f,
			0.0f, yScale, 0.0f, 0.0f,
			0.0f, 0.0f, near + far / (near - far), -1.0f,
			0.0f, 0.0f,  2.0f * near * far / (near - far), 0.0f
		};
		return Matrix4(temp);
	}

	static Matrix4 createPerspective(float left, float right, float bottom, float top, float near, float far)
	{
		array<float, 16> temp =
		{
			2 * near / (right - left), 0.0f, 0.0f, 0.0f,
			0.0f, 2 * near / (top - bottom), 0.0f, 0.0f,
			(right + left) / (right - left), (top + bottom) / (top - bottom), (far + near) / (near - far), -1.0f,
			0.0f, 0.0f, 2 * near * far / (near - far), 0.0f
		};
		return Matrix4(temp);
	}

	static const Matrix4 identity;
};

#endif
