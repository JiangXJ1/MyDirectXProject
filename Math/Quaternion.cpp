#include "Quaternion.h"
#include "mymath.h"
#include <cmath>
#include "Vector3.h"
#include "Matrix4x4.h"
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

	void Quaternion::operator=(const Quaternion & q)
	{
		x = q.x;
		y = q.y;
		z = q.z;
		w = q.w;
	}

	Quaternion Quaternion::operator*(const Quaternion & q) const
	{
		//四元数乘法：q1q2=(v1→×v2→+w1v2→+w2v1→,w1w2−v1→⋅v2→)
		float tmpx = y * q.z - z * q.y + w * q.x + q.w * x;
		float tmpy = z * q.x - x * q.z + w * q.y + q.w * y;
		float tmpz = x * q.y - y * q.x + w * q.z + q.w * z;
		float tmpw = q.w * w - (x * q.x + y * q.y + z * q.z);
		auto qr = Quaternion(tmpx, tmpy, tmpz, tmpw);
		//qr.Normalize();
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
		Normalize();
	}

	void Quaternion::ToEulerRadians(Vector3 & v)
	{
		v.x = asin(2 * (w * x - y * z));
		v.y = atan2(2 * (x * z + w * y), 1 - 2 * (x * x + y * y));
		v.z = atan2(2 * (x * y + w * z), 1 - 2 * (x * x + z * z));
	}

	void Quaternion::Conjugate(Quaternion & dst) const
	{
		dst.w = w;
		dst.x = -x;
		dst.y = -y;
		dst.z = -z;
	}

	Quaternion Quaternion::GetConjugate() const
	{
		Quaternion q;
		Conjugate(q);
		return q;
	}

	void Quaternion::Inverse(Quaternion & dst) const
	{
		Conjugate(dst);
		float length = Length();
		length *= length;
		dst.x /= length;
		dst.y /= length;
		dst.z /= length;
		dst.w /= length;
	}

	Quaternion Quaternion::GetInverse() const
	{
		Quaternion q;
		Inverse(q);
		return q;
	}

	float Quaternion::Dot(const Quaternion dst) const
	{
		float length = Length();
		return (x*x + y * y + z * z + w * w) / length;
	}

	void Quaternion::ApplyMatrix(Matrix4x4& matrix) const
	{
		float xx = x * x;
		float yy = y * y;
		float zz = z * z;
		float xy = x * y;
		float wz = w * z;
		float wy = w * y;
		float xz = x * z;
		float yz = y * z;
		float wx = w * x;

		matrix[0][0] = 1 - 2 * (yy + zz);
		matrix[0][1] = 2 * (xy - wz);
		matrix[0][2] = 2 * (wy + xz);
		matrix[0][3] = 0;

		matrix[1][0] = 2 * (xy + wz);
		matrix[1][1] = 1 - 2 * (xx + zz);
		matrix[1][2] = 2 * (yz - wx);
		matrix[1][3] = 0;

		matrix[2][0] = 2 * (xz - wy);//不是 xy - wy
		matrix[2][1] = 2 * (yz + wx);
		matrix[2][2] = 1 - 2 * (xx + yy);
		matrix[2][3] = 0;

		matrix[3][0] = 0;
		matrix[3][1] = 0;
		matrix[3][2] = 0;
		matrix[3][3] = 1;
	}

	void Quaternion::Reset()
	{
		w = 1;
		x = 0;
		y = 0;
		z = 0;
	}

	void Quaternion::ToEulerAngles(Vector3 & v)
	{
		ToEulerRadians(v);
		v.x = Radian2Angle(v.x);
		v.y = Radian2Angle(v.y);
		v.z = Radian2Angle(v.z);
	}
}
