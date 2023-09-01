#pragma warning (disable:26495)
#include "Matrix4X4.h"
#include <memory>
#include <assert.h>
#include <math.h>

namespace owen
{
namespace math
{
Matrix4X4::Matrix4X4()
	:m00(1), m01(0), m02(0), m03(0),
	m10(0), m11(1), m12(0), m13(0),
	m20(0), m21(0), m22(1), m23(0),
	m30(0), m31(0), m32(0), m33(1)
{
}

Matrix4X4::Matrix4X4(float* fv)
	: m00(fv[0]), m01(fv[1]), m02(fv[2]), m03(fv[3]),
	m10(fv[4]), m11(fv[5]), m12(fv[6]), m13(fv[7]),
	m20(fv[8]), m21(fv[9]), m22(fv[10]), m23(fv[11]),
	m30(fv[12]), m31(fv[13]), m32(fv[14]), m33(fv[15])
{
}

Matrix4X4::Matrix4X4(float _00, float _01, float _02, float _03,
	float _10, float _11, float _12, float _13,
	float _20, float _21, float _22, float _23,
	float _30, float _31, float _32, float _33)
	:m00(_00), m01(_01), m02(_02), m03(_03),
	m10(_10), m11(_11), m12(_12), m13(_13),
	m20(_20), m21(_21), m22(_22), m23(_23),
	m30(_30), m31(_31), m32(_32), m33(_33)
{
}

Matrix4X4::Matrix4X4(const Matrix4X4& other)
	: m00(other.m00), m01(other.m01), m02(other.m02), m03(other.m03),
	m10(other.m10), m11(other.m11), m12(other.m12), m13(other.m13),
	m20(other.m20), m21(other.m21), m22(other.m22), m23(other.m23),
	m30(other.m30), m31(other.m31), m32(other.m32), m33(other.m33)
{
}

Matrix4X4& Matrix4X4::operator=(const Matrix4X4& other)
{
	if (this == &other)
	{
		return *this;
	}

	memcpy(v, other.v, 16 * sizeof(float));
	return *this;
}

bool Matrix4X4::operator==(const Matrix4X4& other) const
{
	for (int i = 0; i < 16; ++i)
	{
		if (fabsf(v[i] - other.v[i]) > float_epsilon)
		{
			return false;
		}
	}
	return true;
}

bool Matrix4X4::operator!=(const Matrix4X4& other) const
{
	return !(*this == other);
}

bool Matrix4X4::Equal(const Matrix4X4& left, const Matrix4X4& right)
{
	return left == right;
}

bool Matrix4X4::NotEqual(const Matrix4X4& left, const Matrix4X4& right)
{
	return left != right;
}

Matrix4X4 Matrix4X4::operator+(const Matrix4X4& other) const
{
	float fv[16]{ 0 };
	fv[0] = m00 + other.m00; fv[1] = m01 + other.m01; fv[2] = m02 + other.m02; fv[3] = m03 + other.m03;
	fv[4] = m10 + other.m10; fv[5] = m11 + other.m11; fv[6] = m12 + other.m12; fv[7] = m13 + other.m13;
	fv[8] = m20 + other.m20; fv[9] = m21 + other.m21; fv[10] = m22 + other.m22; fv[11] = m23 + other.m23;
	fv[12] = m30 + other.m30; fv[13] = m31 + other.m31; fv[14] = m32 + other.m32; fv[15] = m33 + other.m33;
	return Matrix4X4(fv);
}

Matrix4X4& Matrix4X4::operator+=(const Matrix4X4& other)
{
	m00 += other.m00; m01 += other.m01; m02 += other.m02; m03 += other.m03;
	m10 += other.m10; m11 += other.m11; m12 += other.m12; m13 += other.m13;
	m20 += other.m20; m21 += other.m21; m22 += other.m22; m23 += other.m23;
	m30 += other.m30; m31 += other.m31; m32 += other.m32; m33 += other.m33;
	return *this;
}

Matrix4X4 Matrix4X4::operator-(const Matrix4X4& other) const
{
	float fv[16]{ 0 };
	fv[0] = m00 - other.m00; fv[1] = m01 - other.m01; fv[2] = m02 - other.m02; fv[3] = m03 - other.m03;
	fv[4] = m10 - other.m10; fv[5] = m11 - other.m11; fv[6] = m12 - other.m12; fv[7] = m13 - other.m13;
	fv[8] = m20 - other.m20; fv[9] = m21 - other.m21; fv[10] = m22 - other.m22; fv[11] = m23 - other.m23;
	fv[12] = m30 - other.m30; fv[13] = m31 - other.m31; fv[14] = m32 - other.m32; fv[15] = m33 - other.m33;
	return Matrix4X4(fv);
}

Matrix4X4& Matrix4X4::operator-=(const Matrix4X4& other)
{
	m00 -= other.m00; m01 -= other.m01; m02 -= other.m02; m03 -= other.m03;
	m10 -= other.m10; m11 -= other.m11; m12 -= other.m12; m13 -= other.m13;
	m20 -= other.m20; m21 -= other.m21; m22 -= other.m22; m23 -= other.m23;
	m30 -= other.m30; m31 -= other.m31; m32 -= other.m32; m33 -= other.m33;
	return *this;
}

Matrix4X4 Matrix4X4::operator*(float scale) const
{
	float fv[16]{ 0 };
	fv[0] = m00 * scale; fv[1] = m01 * scale; fv[2] = m02 * scale; fv[3] = m03 * scale;
	fv[4] = m10 * scale; fv[5] = m11 * scale; fv[6] = m12 * scale; fv[7] = m13 * scale;
	fv[8] = m20 * scale; fv[9] = m21 * scale; fv[10] = m22 * scale; fv[11] = m23 * scale;
	fv[12] = m30 * scale; fv[13] = m31 * scale; fv[14] = m32 * scale; fv[15] = m33 * scale;
	return Matrix4X4(fv);
}

Matrix4X4& Matrix4X4::operator*=(float scale)
{
	m00 *= scale; m01 *= scale; m02 *= scale; m03 *= scale;
	m10 *= scale; m11 *= scale; m12 *= scale; m13 *= scale;
	m20 *= scale; m21 *= scale; m22 *= scale; m23 *= scale;
	m30 *= scale; m31 *= scale; m32 *= scale; m33 *= scale;
	return *this;
}

Matrix4X4 Matrix4X4::operator*(const Matrix4X4& other) const
{
	auto op = [this, &other](uint16_t row, uint16_t col) {
		return v[0 * 4 + row] * other.v[col * 4 + 0]
			+ v[1 * 4 + row] * other.v[col * 4 + 1]
			+ v[2 * 4 + row] * other.v[col * 4 + 2]
			+ v[3 * 4 + row] * other.v[col * 4 + 3];
	};

	return Matrix4X4(
		op(0, 0), op(1, 0), op(2, 0), op(3, 0),
		op(0, 1), op(1, 1), op(2, 1), op(3, 1),
		op(0, 2), op(1, 2), op(2, 2), op(3, 2),
		op(0, 3), op(1, 3), op(2, 3), op(3, 3)
	);
}

Vector4 Matrix4X4::operator*(const Vector4& vec) const
{
	return Vector4(
		cell(0, vec.x, vec.y, vec.z, vec.w),
		cell(1, vec.x, vec.y, vec.z, vec.w),
		cell(2, vec.x, vec.y, vec.z, vec.w),
		cell(3, vec.x, vec.y, vec.z, vec.w)
	);
}

Vector3 Matrix4X4::TransformVector(const Vector3& vec) const
{
	return Vector3(
		cell(0, vec.x, vec.y, vec.z, 0.0f),
		cell(1, vec.x, vec.y, vec.z, 0.0f),
		cell(2, vec.x, vec.y, vec.z, 0.0f)
	);
}

Vector3 Matrix4X4::TransformPoint(const Vector3& vec) const
{
	return Vector3(
		cell(0, vec.x, vec.y, vec.z, 1.0f),
		cell(1, vec.x, vec.y, vec.z, 1.0f),
		cell(2, vec.x, vec.y, vec.z, 1.0f)
	);
}

void Matrix4X4::Transpose(Matrix4X4& matrix)
{
	//m00 m01 m02 m03
	//m10 m11 m12 m13
	//m20 m21 m22 m23
	//m30 m31 m32 m33
	std::swap(matrix.m10, matrix.m01);
	std::swap(matrix.m20, matrix.m02);
	std::swap(matrix.m30, matrix.m03);
	std::swap(matrix.m21, matrix.m12);
	std::swap(matrix.m31, matrix.m13);
	std::swap(matrix.m32, matrix.m23);
}

Matrix4X4 Matrix4X4::Transposed() const
{
	return Matrix4X4(
		m00, m10, m20, m30,
		m01, m11, m21, m31,
		m02, m12, m22, m32,
		m03, m13, m23, m33
	);
}

float Matrix4X4::Determinant() const
{
	/*
	return m00 * m11 * m22 * m33 - m00 * m11 * m23 * m32 + m00 * m12 * m23 * m31 - m00 * m12 * m21 * m33
		+ m00 * m13 * m21 * m32 - m00 * m13 * m22 * m31 - m01 * m12 * m23 * m30 + m01 * m12 * m20 * m33
		- m01 * m13 * m20 * m32 + m01 * m13 * m22 * m30 - m01 * m10 * m22 * m33 + m01 * m10 * m23 * m32
		+ m02 * m13 * m20 * m31 - m02 * m13 * m21 * m30 + m02 * m10 * m21 * m33 - m02 * m10 * m23 * m31
		+ m02 * m11 * m23 * m30 - m02 * m11 * m20 * m33 - m03 * m10 * m21 * m32 + m03 * m10 * m22 * m31
		- m03 * m11 * m22 * m30 + m03 * m11 * m20 * m32 - m03 * m12 * m20 * m31 + m03 * m12 * m21 * m30;
		*/

	return  v[0] * minor(1, 2, 3, 1, 2, 3) -
		v[4] * minor(0, 2, 3, 1, 2, 3) +
		v[8] * minor(0, 1, 3, 1, 2, 3) -
		v[12] * minor(0, 1, 2, 1, 2, 3);
}

Matrix4X4 Matrix4X4::Adjugate() const
{
	Matrix4X4 cofMat4;

	cofMat4.v[0] = minor(1, 2, 3, 1, 2, 3);
	cofMat4.v[1] = -minor(1, 2, 3, 0, 2, 3);
	cofMat4.v[2] = minor(1, 2, 3, 0, 1, 3);
	cofMat4.v[3] = -minor(1, 2, 3, 0, 1, 2);
	cofMat4.v[4] = -minor(0, 2, 3, 1, 2, 3);
	cofMat4.v[5] = minor(0, 2, 3, 0, 2, 3);
	cofMat4.v[6] = -minor(0, 2, 3, 0, 1, 3);
	cofMat4.v[7] = minor(0, 2, 3, 0, 1, 2);
	cofMat4.v[8] = minor(0, 1, 3, 1, 2, 3);
	cofMat4.v[9] = -minor(0, 1, 3, 0, 2, 3);
	cofMat4.v[10] = minor(0, 1, 3, 0, 1, 3);
	cofMat4.v[11] = -minor(0, 1, 3, 0, 1, 2);
	cofMat4.v[12] = -minor(0, 1, 2, 1, 2, 3);
	cofMat4.v[13] = minor(0, 1, 2, 0, 2, 3);
	cofMat4.v[14] = -minor(0, 1, 2, 0, 1, 3);
	cofMat4.v[15] = minor(0, 1, 2, 0, 1, 2);

	return cofMat4.Transposed();
}

Matrix4X4 Matrix4X4::Inverse() const
{
	float det = Determinant();

	if (fabsf(det) < float_epsilon)
	{
		return Matrix4X4();
	}

	Matrix4X4 adjugate = Adjugate();

	return adjugate * (1.0f / det);
}

void Matrix4X4::Invert(Matrix4X4& mat4) const
{
	float det = Determinant();

	if (fabsf(det) < float_epsilon)
	{
		mat4 = Matrix4X4();
		return;
	}

	Matrix4X4 adjugate = Adjugate();
	mat4 = adjugate * (1.0f / det);
}


}
}
