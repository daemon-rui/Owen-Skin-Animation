#include "Vector2.h"
#include <memory>
#include <assert.h>
#include <math.h>

namespace owen
{
namespace math
{
Vector2::Vector2()
	:x(0.0f)
	, y(0.0f)
{
}

Vector2::Vector2(float _x, float _y)
	:x(_x)
	, y(_y)
{
}

Vector2::Vector2(float* pValue)
	:x(pValue[0])
	, y(pValue[1])
{
}

Vector2::Vector2(const Vector2& other)
	:x(other.x)
	, y(other.y)
{
}

Vector2& Vector2::operator=(const Vector2& other)
{
	if (this == &other)
	{
		return *this;
	}
	x = other.x;
	y = other.y;
	return *this;
}

float Vector2::operator[](unsigned int index) const
{
	if (index == 0)
	{
		return x;
	}
	else if (index == 1)
	{
		return y;
	}
	else
	{
		assert(false && "The index error.");
	}
	return 0.0f;
}

float& Vector2::operator[](unsigned int index)
{
	if (index == 0)
	{
		return x;
	}
	else if (index == 1)
	{
		return y;
	}
	else
	{
		assert(false && "The index error.");
	}
	return x;
}

Vector2 Vector2::operator+(const Vector2& other) const
{
	return Vector2(x + other.x, y + other.y);
}

Vector2& Vector2::operator+=(const Vector2& other)
{
	x += other.x;
	y += other.y;
	return *this;
}

Vector2 Vector2::operator-(const Vector2& other) const
{
	return Vector2(x - other.x, y - other.y);
}

Vector2& Vector2::operator-=(const Vector2& other)
{
	x -= other.x;
	y -= other.y;
	return *this;
}

Vector2 Vector2::operator*(float scale) const
{
	return Vector2(x * scale, y * scale);
}

Vector2& Vector2::operator*=(float scale)
{
	x *= scale;
	y *= scale;
	return *this;
}

Vector2 Vector2::operator*(const Vector2& scale) const
{
	return Vector2(x * scale.x, y * scale.y);
}

Vector2& Vector2::operator*=(const Vector2& scale)
{
	x *= scale.x;
	y *= scale.y;
	return *this;
}

bool Vector2::operator==(const Vector2& other) const
{
	return x == other.x && y == other.y;
}

bool Vector2::operator!=(const Vector2& other) const
{
	return !(*this == other);
}

bool Vector2::Equal(const Vector2& left, const Vector2& right)
{
	return left == right;
}

bool Vector2::NotEqual(const Vector2& left, const Vector2& right)
{
	return left != right;
}

float Vector2::Dot(const Vector2& right) const
{
	return x * right.x + y * right.y;
}

float Vector2::Dot(const Vector2& left, const Vector2& right)
{
	return left.x * right.x + left.y * right.y;
}

Vector2 Vector2::Lerp(const Vector2& left, const Vector2& right, float t)
{
	if (t < 0.0f || t > 1.0f)
	{
		//The interpolation param is error.
		assert(false && "The interpolation parameter error.");
		return Vector2();
	}

	float xVal = left.x * (1 - t) + right.x * t;
	float yVal = left.y * (1 - t) + right.y * t;
	return Vector2(xVal, yVal);
}

Vector2 Vector2::Slerp(const Vector2& left, const Vector2& right, float t)
{
	if (t < 0.0f || t > 1.0f)
	{
		//The interpolation param is error.
		assert(false && "The interpolation parameter error.");
		return Vector2();
	}

	//When the value of t is close to 0, 
	//the slerp will yield unexpected results.
	//So when the value of t is close to 0, fall back on lerp.
	if (t < 0.01f)
		return Lerp(left, right, t);

	const Vector2& from = Normalize(left);
	const Vector2& to = Normalize(right);
	float theta = Angle(from, to);

	float sin_1_t_theta = sinf((1 - t) * theta);
	float sin_t_theta = sinf(t * theta);
	float sin_theta = sinf(theta);

	float xVal = from.x * (sin_1_t_theta / sin_theta) + to.x * (sin_t_theta / sin_theta);
	float yVal = from.y * (sin_1_t_theta / sin_theta) + to.y * (sin_t_theta / sin_theta);
	return Vector2(xVal, yVal);
}

Vector2 Vector2::Nlerp(const Vector2& left, const Vector2& right, float t)
{
	return Normalize(Lerp(left, right, t));
}

float Vector2::Length() const
{
	return sqrtf(x * x + y * y);
}

float Vector2::Length(const Vector2& vector)
{
	return sqrtf(vector.x * vector.x + vector.y * vector.y);
}

Vector2 Vector2::Normalize() const
{
	float len = Length();
	if (fabsf(len) < float_epsilon)
	{
		return Vector2();
	}

	float lenInv = 1 / len;
	return Vector2(x * lenInv, y * lenInv);
}

Vector2 Vector2::Normalize(const Vector2& vector)
{
	return vector.Normalize();
}

float Vector2::Angle(const Vector2& left, const Vector2& right)
{
	float lenProduct = Length(left) * Length(right);
	if (lenProduct > float_epsilon)
	{
		float dot = left.x * right.x + left.y * right.y;
		return acosf(dot / lenProduct);
	}
	return 0.0f;
}

Vector2 Vector2::Projection(const Vector2& left, const Vector2& right)
{
	float rightLen = right.Length();
	if (rightLen < float_epsilon)
	{
		//Return zero vector
		return Vector2();
	}
	float scale = left.Dot(right) / rightLen;
	return Vector2{ right.x * scale, right.y * scale };
}

Vector2 Vector2::Rejection(const Vector2& left, const Vector2& right)
{
	Vector2 projection = Projection(left, right);
	return Vector2{ left.x - projection.x, left.y - projection.y };
}

float Vector2::EuclideanDistance(const Vector2& left, const Vector2& right)
{
	return sqrtf((left.x - right.x) * (left.x - right.x) + (left.y - right.y) * (left.y - right.y));
}
}
}

