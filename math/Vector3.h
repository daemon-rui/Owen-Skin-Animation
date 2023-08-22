#pragma once


namespace owen
{
namespace math
{
class Vector3
{
	static constexpr float float_epsilon = 0.000001f;
public:
	Vector3();
	Vector3(float _x, float _y, float _z);
	Vector3(float* pValue);
	Vector3(const Vector3& other);
	Vector3& operator=(const Vector3& other);
	~Vector3() = default;

	float operator[](unsigned int index) const;
	float& operator[](unsigned int index);

	Vector3 operator+(const Vector3& other) const;
	Vector3& operator+=(const Vector3& other);

	Vector3 operator-(const Vector3& other) const;
	Vector3& operator-=(const Vector3& other);

	Vector3 operator*(float scale) const;
	Vector3& operator*= (float scale);

	Vector3 operator*(const Vector3& scale) const;
	Vector3& operator*=(const Vector3& scale);

	float Dot(const Vector3& right) const;
	static float Dot(const Vector3& left, const Vector3& right);

	float Length() const;

	Vector3 Normalize() const;

	static float Angle(const Vector3& left, const Vector3& right);

	static Vector3 Projection(const Vector3& left, const Vector3& right);
	static Vector3 Rejection(const Vector3& left, const Vector3& right);
public:
	union
	{
		struct {
			float x;
			float y;
			float z;
		};
		float fv[3];
	};
};
}
}


