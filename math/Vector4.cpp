#include "Vector4.h"
#include <memory>
#include <assert.h>
#include <math.h>
#include "Vector3.h"

namespace owen
{
namespace math
{
Vector4::Vector4()
	:x(0.0f)
	, y(0.0f)
	, z(0.0f)
	, w(0.0f)
{
}

Vector4::Vector4(float _x, float _y, float _z, float _w)
	:x(_x)
	, y(_y)
	, z(_z)
	, w(_w)
{
}

Vector4::Vector4(float* pValue)
	:x(pValue[0])
	, y(pValue[1])
	, z(pValue[2])
	, w(pValue[3])
{
}

Vector4::Vector4(const Vector3& vec3)
	:x(vec3.x)
	, y(vec3.y)
	, z(vec3.z)
	, w(1.0f)
{
}

Vector4::Vector4(const Vector4& other)
	:x(other.x)
	, y(other.y)
	, z(other.z)
	, w(other.w)
{
}

Vector4& Vector4::operator=(const Vector4& other)
{
	if (this == &other)
	{
		return *this;
	}
	x = other.x;
	y = other.y;
	z = other.z;
	w = other.w;
	return *this;
}

float Vector4::operator[](unsigned int index) const
{
	switch (index)
	{
	case 0:
		return x;
	case 1:
		return y;
	case 2:
		return z;
	case 3:
		return w;

	default:
		assert(false && "The index erroe.");
		break;
	}
	return 0.0f;
}

float& Vector4::operator[](unsigned int index)
{
	switch (index)
	{
	case 0:
		return x;
	case 1:
		return y;
	case 2:
		return z;
	case 3:
		return w;

	default:
		assert(false && "The index erroe.");
		break;
	}
	return x;
}

Vector4 Vector4::operator+(const Vector4& other) const
{
	return Vector4(x + other.x, y + other.y, z + other.z, w + other.w);
}

Vector4& Vector4::operator+=(const Vector4& other)
{
	x += other.x;
	y += other.y;
	z += other.z;
	w += other.w;
	return *this;
}

Vector4 Vector4::operator-(const Vector4& other) const
{
	return Vector4(x - other.x, y - other.y, z - other.z, w - other.w);
}

Vector4& Vector4::operator-=(const Vector4& other)
{
	x -= other.x;
	y -= other.y;
	z -= other.z;
	w -= other.w;
	return *this;
}

Vector4 Vector4::operator*(float scale) const
{
	return Vector4(x * scale, y * scale, z * scale, w * scale);
}

Vector4& Vector4::operator*=(float scale)
{
	x *= scale;
	y *= scale;
	z *= scale;
	w *= scale;
	return *this;
}

Vector4 Vector4::operator*(const Vector4& scale) const
{
	return Vector4(x * scale.x, y * scale.y, z * scale.z, w * scale.w);
}

Vector4& Vector4::operator*=(const Vector4& scale)
{
	x *= scale.x;
	y *= scale.y;
	z *= scale.z;
	w *= scale.w;
	return *this;
}

Vector4 Vector4::operator*(const Vector3& scale) const
{
	return Vector4(x * scale.x, y * scale.y, z * scale.z, w);
}

Vector4& Vector4::operator*=(const Vector3& scale)
{
	x *= scale.x;
	y *= scale.y;
	z *= scale.z;
	//w *= 1.0f
	return *this;
}

bool Vector4::operator==(const Vector4& other) const
{
	return (x == other.x)
		&& (y == other.y)
		&& (z == other.z)
		&& (w == other.w);
}

bool Vector4::operator!=(const Vector4& other) const
{
	return !(*this == other);
}

bool Vector4::Equal(const Vector4& left, const Vector4& right)
{
	return left == right;
}

bool Vector4::NotEqual(const Vector4& left, const Vector4& right)
{
	return left != right;
}

float Vector4::Dot(Vector4& other) const
{
	return x * other.x + y * other.y + z * other.z + w * other.w;
}

float Vector4::Dot(const Vector4& left, const Vector4& right)
{
	return left.x * right.x + left.y * right.y + left.z * right.z + left.w * right.w;
}

Vector4 Vector4::Lerp(const Vector4& left, const Vector4& right, float t)
{
	if (t < 0.0f || t > 1.0f)
	{
		assert(false && "Interpolation param is error.");
		return Vector4();
	}

	float xVal = left.x * (1 - t) + right.x * t;
	float yVal = left.y * (1 - t) + right.y * t;
	float zVal = left.z * (1 - t) + right.z * t;
	float wVal = left.w * (1 - t) + right.w * t;

	return Vector4(xVal, yVal, zVal, wVal);
}

Vector4 Vector4::Nlerp(const Vector4& left, const Vector4& right, float t)
{
	return Normalize(Lerp(left, right, t));
}

float Vector4::Length() const
{
	return sqrtf(x * x + y * y + z * z + w * w);
}

Vector4 Vector4::Normalize() const
{
	float len = Length();
	if (len > float_epsilon)
	{
		float lenInv = 1 / len;
		return Vector4(x * lenInv, y * lenInv, z * lenInv, z * lenInv);
	}
	return Vector4();
}

Vector4 Vector4::Normalize(const Vector4& vector)
{
	return vector.Normalize();
}

float Vector4::EuclideanDistance(const Vector4& left, const Vector4& right)
{
	float a = left.x - right.x;
	float b = left.y - right.y;
	float c = left.z - right.z;
	float d = left.w - right.w;
	return sqrtf(a * a + b * b + c * c + d * d);
}
}
}

