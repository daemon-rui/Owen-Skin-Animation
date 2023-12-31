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

	bool operator==(const Vector3& other) const;
	bool operator!=(const Vector3& other) const;

	static bool Equal(const Vector3& left, const Vector3& right);
	static bool NotEqual(const Vector3& left, const Vector3& right);

	float Dot(const Vector3& right) const;
	static float Dot(const Vector3& left, const Vector3& right);

	static Vector3 Cross(const Vector3& left, const Vector3& right);

	static Vector3 Lerp(const Vector3& left, const Vector3& right, float t);
	static Vector3 Slerp(const Vector3& left, const Vector3& right, float t);
	static Vector3 Nlerp(const Vector3& left, const Vector3& right, float t);
	float Length() const;

	Vector3 Normalize() const;

	static Vector3 Normalize(const Vector3& vector);
	static float Angle(const Vector3& left, const Vector3& right);

	static Vector3 Projection(const Vector3& left, const Vector3& right);
	static Vector3 Rejection(const Vector3& left, const Vector3& right);
	static float EuclideanDistance(const Vector3& left, const Vector3& right);
	static bool IsZero(const Vector3& vec3);
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


