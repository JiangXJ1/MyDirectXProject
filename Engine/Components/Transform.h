#pragma once
#ifndef _TRANSFORM_H
#define _TRANSFORM_H
#include "Component.h"
#include "../../Math/Vector3.h"
#include "../../Math/Matrix4x4.h"
#include "../../Math/Quaternion.h"
#include <vector>
using namespace std;
using namespace Math;
namespace Engine {
	class Transform : public Component
	{
	private:
		bool matrixChanged;
		Vector3 localPosition;
		Vector3 localScale;
		Quaternion localRotation;
		Matrix4x4 localToWorldMatrix;
		Matrix4x4 worldToLocalMatrix;
		vector<Transform*> children;
		Transform* parent;
	public:
		Transform(const SceneObject* pObj);
		~Transform();

	private:
		void SetMatrixChanged(bool changed);
		bool AddChild(Transform* child);
		bool RemoveChild(Transform* child);

	public:
		inline void Update() {}
		inline void LateUpdate() {}
		inline void SetLocalPosition(const Vector3& pos);
		inline const Vector3& GetLocalPosition();
		void SetParent(Transform* newParent);
		Transform* GetParent() const;
	};

}
#endif // !_TRANSFORM_H
