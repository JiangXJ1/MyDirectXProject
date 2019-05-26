#pragma once
#include "Vector3.h"
namespace Math {
	class Quaternion
	{
		//变量定义
		public:
			float x, y, z, w;
		//构造函数
		public:
			Quaternion();
			Quaternion(const float x, const float y, const  float z, const  float w);
			Quaternion(const Quaternion& q);
			~Quaternion();
		//操作符函数
		public:
			bool operator==(const Quaternion& q) const;
			void operator=(const Quaternion& q);
			Quaternion operator*(const Quaternion& q) const;
		public:
			float Length() const;
			void Normalize();
			//通过角度构造四元数
			void EulerAngle(const Vector3& v);
			//通过角度构造四元数
			void EulerAngle(float angleX, float angleY, float angleZ);
			//通过弧度构造四元数
			void EulerRadian(float radianX, float radianY, float radianZ);

			//转换为角度
			void ToEulerAngles(Vector3& v);
			//转换为弧度
			void ToEulerRadians(Vector3& v);
		private:

	};
}