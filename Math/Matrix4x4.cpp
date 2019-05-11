#include "Matrix4x4.h"

namespace Math {
	Matrix4x4::Matrix4x4()
	{
	}

	Matrix4x4::Matrix4x4(const float tmpm[4][4])
	{
		for (int i = 0; i < 4; ++i)
			for (int j = 0; j < 4; ++j)
				m[i][j] = tmpm[i][j];
	}


	Matrix4x4::~Matrix4x4()
	{
	}

	const float* Matrix4x4::operator[](int i) const
	{
		return this->m[i];
	}

	float * Matrix4x4::operator[](int i)
	{
		return m[i];
	}

	Matrix4x4 Matrix4x4::operator*(const Matrix4x4 & rhs) const
	{
		Matrix4x4 mult;
		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 4; ++j) {
				mult[i][j] = m[i][0] * rhs[0][j] +
					m[i][1] * rhs[1][j] +
					m[i][2] * rhs[2][j] +
					m[i][3] * rhs[3][j];
			}
		}
		return mult;
	}
	void Matrix4x4::multPointMatrix(const Vector3 & src, Vector3 & dst) const
	{
		//此处将Vector3当做 (x,y,z,1)进行处理
		dst.x = src.x * m[0][0] + src.y * m[0][1] + src.z * m[0][2] + m[0][3];
		dst.y = src.x * m[1][0] + src.y * m[1][1] + src.z * m[1][2] + m[1][3];
		dst.z = src.x * m[2][0] + src.y * m[2][1] + src.z * m[2][2] + m[2][3];
		float w = src.x * m[3][0] + src.y * m[3][1] + src.z * m[3][2] + m[3][3];
		if (w != 1 && w != 0) {
			dst.x /= w;
			dst.y /= w;
			dst.z /= w;
		}
	}

	void Matrix4x4::multDirectionMatrix(const Vector3 & src, Vector3 & dst) const
	{
		//向量末位为0
		dst.x = src.x * m[0][0] + src.y * m[1][0] + src.z * m[2][0];
		dst.y = src.x * m[0][1] + src.y * m[1][1] + src.z * m[2][1];
		dst.z = src.x * m[0][2] + src.y * m[1][2] + src.z * m[2][2];
	}

	Matrix4x4 Matrix4x4::Inverse() const
	{
		int i, j, k;
		Matrix4x4 s;
		Matrix4x4 t(*this);
		for (i = 0; i < 3; i++) {//找到下三角每列的绝对最大值
			int pivot = i;
			float pivotsize = t[i][i];
			if (pivotsize < 0)pivotsize = -pivotsize;
			for (j = i + 1; j < 4; j++) {
				float tmp = t[j][i];
				if (tmp < 0)tmp = -tmp;
				if (tmp > pivotsize) {
					pivot = j;
					pivotsize = tmp;
				}
			}
			if (pivotsize == 0) {
				return Matrix4x4();
			}
			if (pivot != i)//交换两行，使对角位的值为该列最大
			{
				for (j = 0; j < 4; j++) {
					float tmp;
					tmp = t[i][j];
					t[i][j] = t[pivot][j];
					t[pivot][j] = tmp;
					tmp = s[i][j];
					s[i][j] = s[pivot][j];
					s[pivot][j] = tmp;
				}
			}
			//将下三角值设定为0
			for (j = i + 1; j < 4; j++) {
				float f = t[j][i] / t[i][i];
				for (k = 0; k < 4; k++) {
					t[j][k] -= t[i][k] * f;
					s[j][k] -= s[i][k] * f;
				}
			}
		}

		for (i = 3; i >= 0; i--) {
			float f;
			f = t[i][i];
			if (f == 0)
				return Matrix4x4();
			for (j = 0; j < 4; j++) {//将对角位置为1
				t[i][j] /= f;
				s[i][j] /= f;
			}
			for (j = 0; j < i; j++) {
				f = t[j][i];
				for (k = 0; k < 4; k++) {
					t[j][k] -= f*t[i][k];
					s[j][k] -= f*s[i][k];
				}
			}
		}
		return s;
	}

	Matrix4x4 Matrix4x4::Transpose() const
	{
		Matrix4x4 mat;
		for (int i = 0; i < 4; ++i)
			for (int j = 0; j < 4; ++j)
				mat[i][j] = this->m[j][i];
		return mat;
	}

}