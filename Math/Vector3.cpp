#include "Vector3.h"
#include "mymath.h"
#include <cmath>

namespace Math {
	Vector3::Vector3() : x(0), y(0), z(0)
	{
	}

	Vector3::Vector3(float tmpX, float tmpY = 0, float tmpZ = 0) :
		x(tmpX), y(tmpY), z(tmpZ)
	{
	}

	Vector3::Vector3(const Vector3 & v) : x(v.x), y(v.y), z(v.z)
	{

	}


	Vector3::~Vector3()
	{
	}

	Vector3 Vector3::operator+(const Vector3 & v) const
	{
		return Vector3(x + v.x, y + v.y, z + v.z);
	}

	void Vector3::operator+=(const Vector3 & v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
	}

	Vector3 Vector3::operator-(const Vector3 & v) const
	{
		return Vector3(x - v.x, y - v.y, z - v.z);
	}

	void Vector3::operator-=(const Vector3 & v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
	}

	Vector3 Vector3::operator*(const Vector3 & v) const
	{
		return Vector3(x * v.x, y * v.y, z * v.z);
	}

	void Vector3::operator*=(const Vector3 & v)
	{
		x *= v.x;
		y *= v.y;
		z *= v.z;
	}

	bool Vector3::operator==(const Vector3 & v)
	{
		return x == v.x && y == v.y && z == v.z;
	}

	void Vector3::operator=(const Vector3 & v)
	{
		x = v.x;
		y = v.y;
		z = v.z;
	}

	float Vector3::Length()
	{
		return sqrtf(x * x + y * y + z * z);
	}

	void Vector3::Normalize()
	{
		float length = this->Length();
		this->x /= length;
		this->y /= length;
		this->z /= length;
	}

	Vector3 Vector3::Normalized()
	{
		Vector3 v(*this);
		v.Normalize();
		return v;
	}

	float Vector3::Dot(const Vector3 & v) const
	{
		return this->x * v.x + this->y * v.y + this->z * v.z;
	}

	Vector3 Vector3::Cross(const Vector3 & v) const
	{
		float x = this->y * v.z - this->z * v.y;
		float y = this->z * v.x - this->x * v.z;
		float z = this->x * v.z - this->y * v.x;
		return Vector3(x, y, z);
	}
}
