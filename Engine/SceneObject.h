#pragma once
#ifndef _SCENEOBJECT_H
#define _SCENEOBJECT_H
#include "../Math/Vector3.h"
#include "../Math/Matrix4x4.h"
#include "../Math/Quaternion.h"
#include <vector>
using namespace std;
using namespace Math;
namespace Engine {
	class Component;
	class SceneObject
	{
	private:
		Vector3 localPosition;
		Vector3 localScale;
		Quaternion localRotation;
		Matrix4x4 localToWorldMatrix;


		Vector3 worldPosition;
		Vector3 worldScale;
		Quaternion worldRotation;
		Matrix4x4 worldToLocalMatrix;

		vector<SceneObject*> children;
		SceneObject* parent;
		vector<Component*> components;
		bool destroyed = false;
	public:
		SceneObject(SceneObject* pParent = NULL);
		~SceneObject();

	private:
		bool AddChild(SceneObject* child);
		bool RemoveChild(SceneObject* child);
		void CalcMatrix();
	public:
		void SetParent(SceneObject* newParent);
		SceneObject* GetParent() const;
		inline void SetLocalPosition(const Vector3& pos);
		inline Vector3 GetLocalPosition() const;
		inline void SetWorldPosition(const Vector3& pos);
		inline Vector3 GetWorldPosition() const;
		inline void SetLocalRotation(const Quaternion& rot);
		inline Quaternion GetLocalRotation() const;
		inline void SetWorldRotation(const Quaternion& rot);
		inline Quaternion GetWorldRotation() const;
		inline void SetLocalScale(const Vector3& scale);
		inline Vector3 GetLocalScale() const;
		inline void SetWorldScale(const Vector3& scale);
		inline Vector3 GetWorldScale() const;
		void TranslatRotation(const Quaternion& src, Quaternion& dst);
		void InverseTranslatRotation(const Quaternion& src, Quaternion& dst);
		void TranslatPoint(const Vector3& src, Vector3& dst);
		void InverseTranslatPoint(const Vector3& src, Vector3& dst);
		void TranslatScale(const Vector3& src, Vector3& dst);
		void InverseTranslatScale(const Vector3& src, Vector3& dst);
		bool SceneObject::AddComponent(Component * pComponent);
		bool RemoveComponent(Component * pComponent);
		void Destroy();
		bool IsDestroyed();
		Component* GetComponent(unsigned int component_type);
	};
}

#endif // !_SCENEOBJECT_H
