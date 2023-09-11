#pragma once

#include "Vector3.h"
#include "Vector4.h"

namespace owen
{
namespace math
{
class Matrix4X4
{
public:
	Matrix4X4();
	Matrix4X4(float* fv);
	Matrix4X4(float _00, float _01, float _02, float _03,
		float _10, float _11, float _12, float _13,
		float _20, float _21, float _22, float _23,
		float _30, float _31, float _32, float _33);
	Matrix4X4(const Matrix4X4& other);
	Matrix4X4& operator=(const Matrix4X4& other);
	Matrix4X4(Matrix4X4&&) = default;
	Matrix4X4& operator=(Matrix4X4&&) = default;
	~Matrix4X4() = default;

	bool operator==(const Matrix4X4& other) const;
	bool operator!= (const Matrix4X4& other) const;
	static bool Equal(const Matrix4X4& left, const Matrix4X4& right);
	static bool NotEqual(const Matrix4X4& left, const Matrix4X4& right);

	Matrix4X4 operator+(const Matrix4X4& other) const;
	Matrix4X4& operator+=(const Matrix4X4& other);

	Matrix4X4 operator-(const Matrix4X4& other) const;
	Matrix4X4& operator-=(const Matrix4X4& other);

	Matrix4X4 operator*(float scale) const;
	Matrix4X4& operator*=(float scale);

	Matrix4X4 operator*(const Matrix4X4& other) const;

	Vector4 operator*(const Vector4& vec) const;

	Vector3 TransformVector(const Vector3& vec) const;
	Vector3 TransformPoint(const Vector3& vec) const;

	void Transpose(Matrix4X4& matrix);

	Matrix4X4 Transposed() const;

	float Determinant() const;

	Matrix4X4 Adjugate() const;

	Matrix4X4 Inverse() const;
	void Invert(Matrix4X4& mat4) const;

	static Matrix4X4 LookAt(const Vector3& position, const Vector3& target, const Vector3& up);
public:
	inline float cell(unsigned int row, float x, float y, float z, float w) const
	{
		return x * v[0 * 4 + row]
			+ y * v[1 * 4 + row]
			+ z * v[2 * 4 + row]
			+ w * v[3 * 4 + row];
	}

	inline float minor(int c0, int c1, int c2, int r0, int r1, int r2) const
	{
		float ret =
			v[c0 * 4 + r0] * (v[c1 * 4 + r1] * v[c2 * 4 + r2] - v[c1 * 4 + r2] * v[c2 * 4 + r1]) -
			v[c1 * 4 + r0] * (v[c0 * 4 + r1] * v[c2 * 4 + r2] - v[c0 * 4 + r2] * v[c2 * 4 + r1]) +
			v[c2 * 4 + r0] * (v[c0 * 4 + r1] * v[c1 * 4 + r2] - v[c0 * 4 + r2] * v[c1 * 4 + r1]);
		return ret;
	}

	union
	{
		float v[16];
		struct
		{
			Vector4 right;
			Vector4 up;
			Vector4 forward;
			Vector4 position;
		};

		struct
		{
			float m00; float m01; float m02; float m03;
			float m10; float m11; float m12; float m13;
			float m20; float m21; float m22; float m23;
			float m30; float m31; float m32; float m33;
		};

		//The matrix using column-row notation
		struct
		{
			float c0r0; float c0r1; float c0r2; float c0r3;
			float c1r0; float c1r1; float c1r2; float c1r3;
			float c2r0; float c2r1; float c2r2; float c2r3;
			float c3r0; float c3r1; float c3r2; float c3r3;
		};

		//The matrix using row-column notation
		struct
		{
			float r0c0; float r1c0; float r2c0; float r3c0;
			float r0c1; float r1c1; float r2c1; float r3c1;
			float r0c2; float r1c2; float r2c2; float r3c2;
			float r0c3; float r1c3; float r2c3; float r3c3;
		};
	};
};
}
}


