#include "Quaternion.h"
#include <memory>
#include <assert.h>
#include <math.h>

namespace owen
{
namespace math
{
Quaternion::Quaternion()
	:x(0.0f)
	, y(0.0f)
	, z(0.0f)
	, w(1.0f)
{
}

Quaternion::Quaternion(float _x, float _y, float _z, float _w)
	:x(_x)
	, y(_y)
	, z(_z)
	, w(_w)
{
}

Quaternion::Quaternion(const Quaternion& other)
	:x(other.x)
	, y(other.y)
	, z(other.z)
	, w(other.w)
{
}

Quaternion& Quaternion::operator=(const Quaternion& other)
{
	if (this != &other)
	{
		x = other.x;
		y = other.y;
		z = other.z;
		w = other.w;
	}

	return *this;
}

//Attention the angle need to be radian
Quaternion Quaternion::CreateQuaternionByAngleAxis(float angle, const Vector3& axis) const
{
	Vector3 nor = Vector3::Normalize(axis);
	float s = sinf(angle * 0.5f);
	return Quaternion(nor.x * s, nor.y * s, nor.z * s, cosf(angle * 0.5f));
}

Vector3 Quaternion::GetAxis() const
{
	return Vector3::Normalize(Vector3(x, y, z));
}

float Quaternion::GetAngle() const
{
	//w = cosf(angle/2)
	return 2.0f * acosf(w);
}

Vector3 Quaternion::GetAxis(const Quaternion& quat)
{
	return quat.GetAxis();
}

float Quaternion::GetAngle(const Quaternion& quat)
{
	return quat.GetAngle();
}

Quaternion Quaternion::operator+(const Quaternion& right) const
{
	return Quaternion(
		x + right.x,
		y + right.y,
		z + right.z,
		w + right.w
	);
}

Quaternion Quaternion::operator-(const Quaternion& right) const
{
	return Quaternion(
		x - right.x,
		y - right.y,
		z - right.z,
		w - right.w
	);
}

Quaternion Quaternion::operator*(float scale) const
{
	return Quaternion(
		x * scale,
		y * scale,
		z * scale,
		w * scale
	);
}

Quaternion Quaternion::operator-() const
{
	return Quaternion(
		-x,
		-y,
		-z,
		-w
	);
}


Quaternion Quaternion::FromToRotation(const Vector3& from, const Vector3& to) const
{
	Vector3 p0 = Vector3::Normalize(from);
	Vector3 p1 = Vector3::Normalize(to);

	if (Vector3::IsZero(p0 + p1))
	{
		Vector3 mostOrthogonal = Vector3(1, 0, 0);

		if (abs(p0.y) < abs(p0.x))
		{
			mostOrthogonal = Vector3(0, 1, 0);
		}

		if (abs(p0.z) < abs(p0.y) && abs(p0.z) < abs(p0.x))
		{
			mostOrthogonal = Vector3(0, 0, 1);
		}

		Vector3 axis = Vector3::Normalize(Vector3::Cross(p0, mostOrthogonal));
		return Quaternion(axis.x, axis.y, axis.z, 0);
	}

	Vector3 half = Vector3::Normalize(p0 + p1);
	Vector3 axis = Vector3::Cross(p0, half);

	return Quaternion(
		axis.x,
		axis.y,
		axis.z,
		Vector3::Dot(p0, half));
}

}
}

