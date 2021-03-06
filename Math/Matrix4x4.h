#include "Vector3.h"
#pragma once
#ifndef _MATRIX4X4_
#define _MATRIX4X4_
namespace Math {
	class Matrix4x4
	{
	private:
		static float tmpM[4][4];
	public:
		float m[4][4] = { { 1, 0, 0, 0 },{ 0, 1, 0, 0 },{ 0, 0, 1, 0 },{ 0, 0, 0, 1 } };
	public:
		Matrix4x4();
		Matrix4x4(const float[4][4]);
		~Matrix4x4();

#pragma region 操作符函数
	public:
		//取出矩阵的行
		const float* operator[](int i) const;
		float* operator[](int i);
		Matrix4x4 operator* (const Matrix4x4& rhs) const;
		void operator*= (const Matrix4x4& rhs);
		void operator= (const Matrix4x4& rhs);

#pragma endregion

#pragma region 外部调用函数
	public:
		void multPointMatrix(const Vector3 &src, Vector3 &dst) const;
		void multDirectionMatrix(const Vector3 &src, Vector3 &dst) const;
		//求逆矩阵
		bool Inverse(Matrix4x4& dst) const;
		Matrix4x4 GetInverse() const;
		//求转置矩阵
		void Transpose(Matrix4x4& dst) const;
		Matrix4x4 GetTranspose() const;
		//转换为单位矩阵
		void Reset();
#pragma endregion

	};
}
#endif