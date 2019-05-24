#pragma once
#ifndef _TRANSFORM_H
#define _TRANSFORM_H
#include "../Math/Vector3.h"
#include "../Math/Matrix4x4.h"
#include "../Math/Quaternion.h"
using namespace Math;
namespace Engine {
	class Transform
	{
	private:
		Vector3 localPosition;
		Vector3 localScale;
		Quaternion localRotation;
		Matrix4x4 localToWorldMatrix;
	public:
		Transform();
		~Transform();

	private:

	};

}
#endif // !_TRANSFORM_H
