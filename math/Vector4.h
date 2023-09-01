#pragma once


namespace owen
{
namespace math
{
class Vector3;
static constexpr float float_epsilon = 0.000001f;
class Vector4
{

public:
	Vector4();
	Vector4(float _x, float _y, float _z, float _w);
	Vector4(float* pValue);
	Vector4(const Vector3& vec3);
	Vector4(const Vector4& other);
	Vector4& operator=(const Vector4& other);
	~Vector4() = default;

	float operator[](unsigned int index) const;
	float& operator[](unsigned int index);

	Vector4 operator+(const Vector4& other) const;
	Vector4& operator+=(const Vector4& other);

	Vector4 operator-(const Vector4& other) const;
	Vector4& operator-=(const Vector4& other);

	Vector4 operator*(float scale) const;
	Vector4& operator*= (float scale);

	Vector4 operator*(const Vector4& scale) const;
	Vector4& operator*=(const Vector4& scale);

	Vector4 operator*(const Vector3& scale) const;
	Vector4& operator*=(const Vector3& scale);

	bool operator==(const Vector4& other) const;
	bool operator!=(const Vector4& other) const;

	static bool Equal(const Vector4& left, const Vector4& right);
	static bool NotEqual(const Vector4& left, const Vector4& right);

	float Dot(Vector4& other) const;
	static float Dot(const Vector4& left, const Vector4& right);

	static Vector4 Lerp(const Vector4& left, const Vector4& right, float t);
	static Vector4 Nlerp(const Vector4& left, const Vector4& right, float t);
	float Length() const;

	Vector4 Normalize() const;

	static Vector4 Normalize(const Vector4& vector);

	static float EuclideanDistance(const Vector4& left, const Vector4& right);

public:
	union
	{
		struct {
			float x;
			float y;
			float z;
			float w;
		};
		float fv[4];
	};
};
}
}


