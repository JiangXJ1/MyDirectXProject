#pragma once
#include "Vector3.h"
namespace Math {
	class Quaternion
	{
		//��������
		public:
			float x, y, z, w;
		//���캯��
		public:
			Quaternion();
			Quaternion(const float x, const float y, const  float z, const  float w);
			Quaternion(const Quaternion& q);
			~Quaternion();
		//����������
		public:
			bool operator==(const Quaternion& q) const;
			void operator=(const Quaternion& q);
			Quaternion operator*(const Quaternion& q) const;
		public:
			float Length() const;
			void Normalize();
			//ͨ���Ƕȹ�����Ԫ��
			void EulerAngle(const Vector3& v);
			//ͨ���Ƕȹ�����Ԫ��
			void EulerAngle(float angleX, float angleY, float angleZ);
			//ͨ�����ȹ�����Ԫ��
			void EulerRadian(float radianX, float radianY, float radianZ);

			//ת��Ϊ�Ƕ�
			void ToEulerAngles(Vector3& v);
			//ת��Ϊ����
			void ToEulerRadians(Vector3& v);
		private:

	};
}