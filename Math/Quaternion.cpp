#include "Quaternion.h"
#include "mymath.h"
#include <cmath>

namespace Math {
	Quaternion::Quaternion() : x{ 0 }, y{ 0 }, z{ 0 }, w{ 1 }
	{
	}

	Quaternion::Quaternion(const float tmpx, const float tmpy, const float tmpz, const float tmpw)
		: x{ tmpx }, y{ tmpy }, z{ tmpz }, w{ tmpw }
	{
	}

	Quaternion::Quaternion(const Quaternion & q)
		: x{ q.x }, y{ q.y }, z{ q.z }, w{ q.w }
	{
	}

	Quaternion::~Quaternion()
	{
	}

	bool Quaternion::operator==(const Quaternion & q)  const
	{
		return x == q.x && y == q.y && z == q.z && w == q.w;
	}

	Quaternion Quaternion::operator*(const Quaternion & q) const
	{
		//四元数乘法：q1q2=(v1→×v2→+w1v2→+w2v1→,w1w2−v1→⋅v2→)
		float tmpx = y * q.z - z * q.y + w * q.x + q.w * x;
		float tmpy = z * q.x - x * q.z + w * q.y + q.w * y;
		float tmpz = x * q.z - y * q.x + w * q.z + q.w * z;
		float tmpw = q.w * w + x * q.x + y * q.y + z * q.z;
		auto qr = Quaternion(tmpx, tmpy, tmpz, tmpw);
		qr.Normalize();
		return qr;
	}

	float Quaternion::Length() const
	{
		return sqrtf(x * x + y * y + z * z + w * w);
	}

	void Quaternion::Normalize()
	{
		float length = Length();
		x /= length;
		y /= length;
		z /= length;
		w /= length;
	}

	void Quaternion::EulerAngle(const Vector3 & v)
	{
		EulerAngle(v.x, v.y, v.z);
	}

	void Quaternion::EulerAngle(float angleX, float angleY, float angleZ)
	{
		EulerRadian(Angle2Radian(angleX), Angle2Radian(angleY), Angle2Radian(angleZ));
	}

	void Quaternion::EulerRadian(float radianX, float radianY, float radianZ)
	{
		float sinX = sin(radianX / 2);
		float sinY = sin(radianY / 2);
		float sinZ = sin(radianZ / 2);
		float cosX = cos(radianX / 2);
		float cosY = cos(radianY / 2);
		float cosZ = cos(radianZ / 2);
		x = sinX * cosY * cosZ + cosX * sinY * sinZ;
		y = cosX * sinY * cosZ - sinX * cosY * sinZ;
		z = cosX * cosY * sinZ - sinX * sinY * cosZ;
		w = cosX * cosY * cosZ + sinX * sinY * sinZ;
	}

	void Quaternion::ToEulerRadians(Vector3 & v)
	{
		v.x = asin(2 * (w * x - y * z));
		v.y = atan2(2 * (x * z + w * y), 1 - 2 * (x * x + y * y));
		v.z = atan2(2 * (x * y + w * z), 1 - 2 * (x * x + z * z));
	}

	void Quaternion::ToEulerAngles(Vector3 & v)
	{
		ToEulerRadians(v);
		v.x = Radian2Angle(v.x);
		v.y = Radian2Angle(v.y);
		v.z = Radian2Angle(v.z);
	}
}
