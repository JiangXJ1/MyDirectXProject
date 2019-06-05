#ifndef __VECTOR3__
#define __VECTOR3__
#pragma once

namespace Math {
	class Vector3
	{
	public:
		float x, y, z;
	public:
		Vector3();
		Vector3(float, float, float);
		Vector3(const Vector3& v);
		~Vector3();

#pragma region 操作符函数
	public:
		Vector3 operator+(const Vector3& v) const;
		void operator+=(const Vector3& v);
		Vector3 operator-(const Vector3& v) const;
		void operator-=(const Vector3& v);
		Vector3 operator*(const Vector3& v) const;
		void operator*=(const Vector3& v);
		void operator/=(const Vector3& v);
		bool operator==(const Vector3& v) const;
		void operator=(const Vector3& v);
#pragma endregion

#pragma region 公共函数
	public:
		float Length();
		void Normalize();
		Vector3 Normalized();
		float Dot(const Vector3& v) const;
		Vector3 Cross(const Vector3& v) const;
#pragma endregion

	};
}

#endif