#include "Vector3.h"
#include <memory>
#include <assert.h>
#include <math.h>

namespace owen
{
namespace math
{
Vector3::Vector3()
	:x(0.0f)
	, y(0.0f)
	, z(0.0f)
{
}

Vector3::Vector3(float _x, float _y, float _z)
	:x(_x)
	, y(_y)
	, z(_z)
{
}

Vector3::Vector3(float* pValue)
	:x(pValue[0])
	, y(pValue[1])
	, z(pValue[2])
{
}

Vector3::Vector3(const Vector3& other)
	:x(other.x)
	, y(other.y)
	, z(other.z)
{
}

Vector3& Vector3::operator=(const Vector3& other)
{
	if (&other == this)
	{
		return *this;
	}

	std::memcpy(fv, other.fv, 3 * sizeof(float));
	return *this;
}

float Vector3::operator[](unsigned int index) const
{
	switch (index)
	{
	case 0:
		return x;
	case 1:
		return y;
	case 2:
		return z;
	default:
		assert(false && "The index error.");
		break;
	}
	return 0.0f;
}

float& Vector3::operator[](unsigned int index)
{
	switch (index)
	{
	case 0:
		return x;
	case 1:
		return y;
	case 2:
		return z;
	default:
		assert(false && "The index error.");
		break;
	}
	return x;
}

Vector3 Vector3::operator+(const Vector3& other) const
{
	return Vector3{ x + other.x, y + other.y, z + other.z };
}

Vector3& Vector3::operator+=(const Vector3& other)
{
	x += other.x;
	y += other.y;
	z += other.z;
	return *this;
}

Vector3 Vector3::operator-(const Vector3& other) const
{
	return Vector3{ x - other.x, y - other.y, z - other.z };
}

Vector3& Vector3::operator-=(const Vector3& other)
{
	x -= other.x;
	y -= other.y;
	z -= other.z;
	return *this;
}

Vector3 Vector3::operator*(float scale) const
{
	return Vector3{ x * scale, y * scale, z * scale };
}

Vector3& Vector3::operator*=(float scale)
{
	x *= scale;
	y *= scale;
	z *= scale;
	return *this;
}

Vector3 Vector3::operator*(const Vector3& scale) const
{
	return Vector3{ x * scale.x, y * scale.y, z * scale.z };
}

Vector3& Vector3::operator*=(const Vector3& scale)
{
	x *= scale.x;
	y *= scale.y;
	z *= scale.z;
	return *this;
}

bool Vector3::operator==(const Vector3& other) const
{
	return (fabsf(x - other.x) < float_epsilon)
		&& (fabsf(y - other.y) < float_epsilon)
		&& (fabsf(z - other.z) < float_epsilon);
}

bool Vector3::operator!=(const Vector3& other) const
{
	return !(*this == other);
}

bool Vector3::Equal(const Vector3& left, const Vector3& right)
{
	return left == right;
}

bool Vector3::NotEqual(const Vector3& left, const Vector3& right)
{
	return left != right;
}

float Vector3::Dot(const Vector3& right) const
{
	return x * right.x + y * right.y + z * right.z;
}

float Vector3::Dot(const Vector3& left, const Vector3& right)
{
	return left.x * right.x + left.y * right.y + left.z * right.z;
}

Vector3 Vector3::Cross(const Vector3& left, const Vector3& right)
{
	return Vector3{
		left.y * right.z - left.z * right.y,
		left.z * right.x - left.x * right.z,
		left.x * right.y - left.y * right.x
	};
}

Vector3 Vector3::Lerp(const Vector3& left, const Vector3& right, float t)
{
	if (t > 1.0f || t < 0.0f)
		return Vector3();

	return Vector3{
		left.x * (1 - t) + right.x * t,
		left.y * (1 - t) + right.y * t,
		left.z * (1 - t) + right.z * t
	};
}

Vector3 Vector3::Slerp(const Vector3& left, const Vector3& right, float t)
{
	if (t > 1.0f || t < 0.0f)
		return Vector3();

	//When the value of t is close to 0, 
	//the slerp will yield unexpected results.
	//So when the value of t is close to 0, fall back on lerp.
	if (t < 0.01f)
		return Lerp(left, right, t);

	const Vector3& from = Normalize(left);
	const Vector3& to = Normalize(right);

	float theta = Angle(from, to);
	float sinTheta = sinf(theta);
	float sin1_t_theat = sinf((1 - t) * theta);
	float sin_t_theta = sinf(t * theta);

	return from * (sin1_t_theat / sinTheta) + to * (sin_t_theta / sinTheta);
}

Vector3 Vector3::Nlerp(const Vector3& left, const Vector3& right, float t)
{
	if (t > 1.0f || t < 0.0f)
		return Vector3();

	return Normalize(Slerp(left, right, t));
}

float Vector3::Length() const
{
	float square = x * x + y * y + z * z;
	if (square > float_epsilon)
	{
		return sqrtf(square);
	}
	return 0.0f;
}

Vector3 Vector3::Normalize() const
{
	float length = Length();
	if (length < float_epsilon)
	{
		return Vector3();
	}
	float inv = 1 / length;
	return Vector3{ x * inv, y * inv,z * inv };
}

Vector3 Vector3::Normalize(const Vector3& vector)
{
	return vector.Normalize();
}

/*
* Get the angle between the two vectors.
* Cos(theta) = (A*B)/(|A||B|)
*/
float Vector3::Angle(const Vector3& left, const Vector3& right)
{
	float leftLen = left.Length();
	float rightLen = right.Length();
	float lenProduct = leftLen * rightLen;
	if (lenProduct > float_epsilon)
	{
		float dotProduct = left.x * right.x + left.y * right.y + left.z * right.z;
		return acosf(dotProduct / lenProduct);
	}

	return 0.0f;
}

Vector3 Vector3::Projection(const Vector3& left, const Vector3& right)
{
	float rightLen = right.Length();
	if (rightLen < float_epsilon)
	{
		//Return zero vector
		return Vector3();
	}
	float scale = left.Dot(right) / rightLen;
	//return right * scale;
	return Vector3{ right.x * scale, right.y * scale, right.z * scale };
}

Vector3 Vector3::Rejection(const Vector3& left, const Vector3& right)
{
	Vector3 projection = Projection(left, right);
	//return left - projection;
	return Vector3{ left.x - projection.x, left.y - projection.y, left.z - projection.z };
}

float Vector3::EuclideanDistance(const Vector3& left, const Vector3& right)
{
	return sqrtf((left.x - right.x) * (left.x - right.x) + (left.y - right.y) * (left.y - right.y) + (left.z - right.z) * (left.z - right.z));
}

}
}

