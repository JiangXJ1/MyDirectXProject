#pragma once
#ifndef _TRANSFORM_H
#define _TRANSFORM_H
#include "Component.h"
#include "../../Math/Vector3.h"
#include "../../Math/Matrix4x4.h"
#include "../../Math/Quaternion.h"
using namespace Math;
namespace Engine {
	class Transform : public Component
	{
	private:
		Vector3 localPosition;
		Vector3 localScale;
		Quaternion localRotation;
		Matrix4x4 localToWorldMatrix;
		Matrix4x4 worldToLocalMatrix;
	public:
		Transform(const SceneObject* pObj);
		~Transform();

	public:
		void SetEnable(bool enable);
		inline void Update() {}
		inline void LateUpdate() {}
	};

}
#endif // !_TRANSFORM_H
