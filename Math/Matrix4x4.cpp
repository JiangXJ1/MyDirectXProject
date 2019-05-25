#include "Matrix4x4.h"
#include <string.h>
using namespace std;
namespace Math {
	float Matrix4x4::tmpM[4][4] = {
		{1,0,0,0},
		{0,1,0,0},
		{0,0,1,0},
		{1,1,1,1},
	};
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
	void Matrix4x4::operator*=(const Matrix4x4 & rhs)
	{
		memcpy(tmpM, m, 16 * sizeof(float));

		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 4; ++j) {
				m[i][j] = tmpM[i][0] * rhs[0][j] +
					tmpM[i][1] * rhs[1][j] +
					tmpM[i][2] * rhs[2][j] +
					tmpM[i][3] * rhs[3][j];
			}
		}
	}
	void Matrix4x4::multPointMatrix(const Vector3 & src, Vector3 & dst) const
	{
		//�˴���Vector3���� (x,y,z,1)���д���
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
		//����ĩλΪ0
		dst.x = src.x * m[0][0] + src.y * m[1][0] + src.z * m[2][0];
		dst.y = src.x * m[0][1] + src.y * m[1][1] + src.z * m[2][1];
		dst.z = src.x * m[0][2] + src.y * m[1][2] + src.z * m[2][2];
	}

	bool Matrix4x4::Inverse(Matrix4x4& dst) const
	{
		int i, j, k;
		Matrix4x4 t(*this);
		for (i = 0; i < 3; i++) {//�ҵ�������ÿ�еľ������ֵ
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
				return false;
			}
			if (pivot != i)//�������У�ʹ�Խ�λ��ֵΪ�������
			{
				for (j = 0; j < 4; j++) {
					float tmp;
					tmp = t[i][j];
					t[i][j] = t[pivot][j];
					t[pivot][j] = tmp;
					tmp = dst[i][j];
					dst[i][j] = dst[pivot][j];
					dst[pivot][j] = tmp;
				}
			}
			//��������ֵ�趨Ϊ0
			for (j = i + 1; j < 4; j++) {
				float f = t[j][i] / t[i][i];
				for (k = 0; k < 4; k++) {
					t[j][k] -= t[i][k] * f;
					dst[j][k] -= dst[i][k] * f;
				}
			}
		}

		for (i = 3; i >= 0; i--) {
			float f;
			f = t[i][i];
			if (f == 0)
				return false;
			for (j = 0; j < 4; j++) {//���Խ�λ��Ϊ1
				t[i][j] /= f;
				dst[i][j] /= f;
			}
			for (j = 0; j < i; j++) {
				f = t[j][i];
				for (k = 0; k < 4; k++) {
					t[j][k] -= f*t[i][k];
					dst[j][k] -= f* dst[i][k];
				}
			}
		}
		return true;
	}

	void Matrix4x4::Transpose(Matrix4x4& dst) const
	{
		for (int i = 0; i < 4; ++i)
			for (int j = 0; j < 4; ++j)
				dst[i][j] = m[j][i];
	}

}