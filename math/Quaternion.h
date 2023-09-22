#pragma once

#include "Vector3.h"
#include "Matrix4X4.h"

namespace owen
{
namespace math
{

class Quaternion
{

public:
	Quaternion();
	Quaternion(float _x, float _y, float _z, float _w);

	Quaternion(const Quaternion& other);
	Quaternion& operator=(const Quaternion& other);

	Quaternion CreateQuaternionByAngleAxis(float angle, const Vector3& axis) const;

	Quaternion FromToRotation(const Vector3& from, const Vector3& to) const;

	Vector3 GetAxis() const;
	float GetAngle() const;

	static Vector3 GetAxis(const Quaternion& quat);
	static float GetAngle(const Quaternion& quat);

	Quaternion operator+(const Quaternion& right) const;
	Quaternion operator-(const Quaternion& right) const;
	Quaternion operator*(float scale) const;
	Quaternion operator-()const;
public:
	union
	{
		struct {
			float x;
			float y;
			float z;
			float w;
		};

		struct
		{
			Vector3 vec3;
			float scalar;
		};
	};
};

}
}


