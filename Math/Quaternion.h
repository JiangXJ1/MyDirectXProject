#pragma once
namespace Math {

	class Vector3;
	class Matrix4x4;

	class Quaternion
	{
		//变量定义
		public:
			float w, x, y, z;
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

			//计算共轭四元数
			void Conjugate(Quaternion& dst) const;
			Quaternion GetConjugate() const;

			//计算共轭四元数的逆
			void Inverse(Quaternion& dst) const;
			Quaternion GetInverse() const;

			//计算四元数的点成
			float Dot(const Quaternion dst) const;

			void ApplyMatrix(Matrix4x4& matrix) const;

			void Reset();

	};
}