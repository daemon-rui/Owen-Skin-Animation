#pragma once


namespace owen
{
namespace math
{

class Vector2
{
	static constexpr float float_epsilon = 0.000001f;
public:
	Vector2();
	Vector2(float _x, float _y);
	Vector2(float* pValue);
	Vector2(const Vector2& other);
	Vector2& operator=(const Vector2& other);
	~Vector2() = default;

	float operator[](unsigned int index) const;
	float& operator[](unsigned int index);

	Vector2 operator+(const Vector2& other) const;
	Vector2& operator+=(const Vector2& other);

	Vector2 operator-(const Vector2& other) const;
	Vector2& operator-=(const Vector2& other);

	Vector2 operator*(float scale) const;
	Vector2& operator*= (float scale);

	Vector2 operator*(const Vector2& scale) const;
	Vector2& operator*=(const Vector2& scale);

	bool operator==(const Vector2& other) const;
	bool operator!=(const Vector2& other) const;

	static bool Equal(const Vector2& left, const Vector2& right);
	static bool NotEqual(const Vector2& left, const Vector2& right);

	float Dot(const Vector2& right) const;
	static float Dot(const Vector2& left, const Vector2& right);

	static Vector2 Lerp(const Vector2& left, const Vector2& right, float t);
	static Vector2 Slerp(const Vector2& left, const Vector2& right, float t);
	static Vector2 Nlerp(const Vector2& left, const Vector2& right, float t);
	float Length() const;
	static float Length(const Vector2& vector);

	Vector2 Normalize() const;

	static Vector2 Normalize(const Vector2& vector);
	static float Angle(const Vector2& left, const Vector2& right);

	static Vector2 Projection(const Vector2& left, const Vector2& right);
	static Vector2 Rejection(const Vector2& left, const Vector2& right);

	static float EuclideanDistance(const Vector2& left, const Vector2& right);

public:
	union
	{
		struct {
			float x;
			float y;
		};
		float fv[2];
	};
};
}
}


