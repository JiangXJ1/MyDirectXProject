#include "SceneObject.h"
#include "../SystemClass.h"
#include "Components/Component.h"
namespace Engine {
	static Matrix4x4 tmpMatrix;
	SceneObject::SceneObject(SceneObject * pParent)
		:parent(pParent),
		localPosition(0, 0, 0),
		localScale(1, 1, 1),
		localRotation(0, 0, 0, 1),
		worldPosition(0, 0, 0),
		worldScale(1, 1, 1),
		worldRotation(0, 0, 0, 1)
	{
		if (pParent != nullptr)
		{
			localToWorldMatrix = pParent->localToWorldMatrix;
			worldToLocalMatrix = pParent->worldToLocalMatrix;
			localToWorldMatrix.multPointMatrix(localPosition, worldPosition);
			worldScale /= pParent->localScale;
			worldRotation = pParent->worldRotation;
		}
	}

	SceneObject::~SceneObject()
	{

	}

	bool SceneObject::AddChild(SceneObject * child)
	{
		if (IsDestroyed())
			return false;
		for (auto it = children.begin(); it != children.end(); ++it)
		{
			if (*it == child)
				return false;
		}
		children.push_back(child);
		return true;
	}
	bool SceneObject::RemoveChild(SceneObject * child)
	{
		if (IsDestroyed())
			return false;
		for (auto it = children.begin(); it != children.end(); ++it) {
			if (*it == child)
			{
				children.erase(it);
				return true;
			}
		}
		return false;
	}

	void SceneObject::CalcMatrix()
	{
		localToWorldMatrix.Reset();
		if (parent != nullptr)
		{
			localToWorldMatrix = parent->localToWorldMatrix;
		}

		//Ðý×ª¾ØÕó
		tmpMatrix.Reset();
		localRotation.ApplyMatrix(tmpMatrix);
		localToWorldMatrix *= tmpMatrix;

		//Ëõ·Å¾ØÕó
		tmpMatrix.Reset();
		tmpMatrix[0][0] = localScale.x;
		tmpMatrix[1][1] = localScale.y;
		tmpMatrix[2][2] = localScale.z;
		localToWorldMatrix *= tmpMatrix;

		//Æ½ÒÆ¾ØÕó
		tmpMatrix.Reset();
		tmpMatrix[3][0] = localPosition.x;
		tmpMatrix[3][1] = localPosition.y;
		tmpMatrix[3][2] = localPosition.z;
		localToWorldMatrix *= tmpMatrix;

		localToWorldMatrix.Inverse(worldToLocalMatrix);
		for (auto it = children.begin(); it != children.end(); it++)
			(*it)->CalcMatrix();
	}

	void SceneObject::SetParent(SceneObject * newParent)
	{
		if (newParent == parent)
			return;
		if (parent != nullptr) 
		{
			parent->RemoveChild(this);
		}
		newParent->AddChild(this);
		parent = newParent;
		if (parent != nullptr) 
		{
			parent->InverseTranslatPoint(worldPosition, localPosition);
			parent->InverseTranslatRotation(worldRotation, localRotation);
			parent->InverseTranslatScale(worldScale, localScale);
		}
		else 
		{
			localPosition = worldPosition;
			localRotation = worldRotation;
			localScale = worldScale;
			localToWorldMatrix = worldToLocalMatrix;
		}
	}

	SceneObject * SceneObject::GetParent() const
	{
		return parent;
	}

	inline void SceneObject::SetLocalPosition(const Vector3 & pos)
	{
		if (pos == localPosition)
			return;
		localPosition = pos;
		if (parent == nullptr)
			worldPosition = localPosition;
		
	}

	inline Vector3 SceneObject::GetLocalPosition() const
	{
		return localPosition;
	}

	inline void SceneObject::SetWorldPosition(const Vector3 & pos)
	{
		if (worldPosition == pos)
			return;
		worldPosition = pos;
		if (parent != nullptr) 
		{
			parent->InverseTranslatPoint(worldPosition, localPosition);
		}
		else
		{
			localPosition = worldPosition;
		}
		CalcMatrix();
	}

	inline Vector3 SceneObject::GetWorldPosition() const
	{
		return worldPosition;
	}

	inline void SceneObject::SetLocalRotation(const Quaternion & rot)
	{
		if (localRotation == rot)
			return;
		localRotation = rot;
		CalcMatrix();
	}

	inline Quaternion SceneObject::GetLocalRotation() const
	{
		return localRotation;
	}

	inline void SceneObject::SetWorldRotation(const Quaternion & rot)
	{
		if (rot == worldRotation)
			return;
		worldRotation = rot;
		if (parent != nullptr) 
		{
			parent->InverseTranslatRotation(rot, localRotation);
		}
		else
		{
			localRotation = worldRotation;
		}
		CalcMatrix();

	}

	inline Quaternion SceneObject::GetWorldRotation() const
	{
		return worldRotation;
	}

	inline void SceneObject::SetLocalScale(const Vector3 & scale)
	{
		if (scale == localScale)
			return;
		localScale = scale;
		CalcMatrix();
	}

	inline Vector3 SceneObject::GetLocalScale() const
	{
		return localScale;
	}

	inline void SceneObject::SetWorldScale(const Vector3 & scale)
	{
		if (scale == worldScale)
			return;
		worldScale = scale;
		if (parent != nullptr)
		{
			parent->InverseTranslatScale(scale, localScale);
		}
		else
		{
			localScale = worldScale;
		}
		CalcMatrix();
	}

	inline Vector3 SceneObject::GetWorldScale() const
	{
		return worldScale;
	}

	void SceneObject::TranslatRotation(const Quaternion & src, Quaternion & dst)
	{
		Quaternion q = worldRotation * src;
		dst = q;
	}

	void SceneObject::InverseTranslatRotation(const Quaternion & src, Quaternion & dst)
	{
		src.Inverse(dst);
		Quaternion q = worldRotation * dst;
		dst = q;
	}

	void SceneObject::TranslatPoint(const Vector3 & src, Vector3 & dst)
	{
		localToWorldMatrix.multPointMatrix(src, dst);
	}

	void SceneObject::InverseTranslatPoint(const Vector3 & src, Vector3 & dst)
	{
		worldToLocalMatrix.multPointMatrix(src, dst);
	}

	void SceneObject::TranslatScale(const Vector3 & src, Vector3 & dst)
	{
		dst.x = worldScale.x * src.x;
		dst.y = worldScale.y * src.y;
		dst.z = worldScale.z * src.z;
	}
	
	void SceneObject::InverseTranslatScale(const Vector3 & src, Vector3 & dst)
	{
		dst.x = src.x / worldScale.x;
		dst.y = src.y / worldScale.y;
		dst.z = src.z / worldScale.z;
	}

	bool SceneObject::AddComponent(Component * pComponent)
	{
		if (IsDestroyed())
			return false;
		if (pComponent != nullptr)
		{
			components.push_back(pComponent);
			return true;
		}
		return false;
	}

	bool SceneObject::RemoveComponent(Component * pComponent)
	{
		if (IsDestroyed())
			return false;
		for (auto it = components.begin(); it != components.end(); it++)
		{
			if (*it == pComponent)
			{
				components.erase(it);
				return true;
			}
		}
		return false;
	}
	void SceneObject::Destroy()
	{
		if (parent != nullptr)
		{
			parent->RemoveChild(this);
		}
		auto it = children.begin();
		while (it != children.end())
		{
			(*it)->Destroy();
			it = children.begin();
		}
		auto itC = components.begin();
		while (itC != components.end())
		{
			(*itC)->Destroy();
			itC = components.begin();
		}
		destroyed = true;
	}

	bool SceneObject::IsDestroyed()
	{
		return destroyed;
	}

	Component* SceneObject::GetComponent(unsigned int component_type)
	{
		for (auto it = components.begin(); it != components.end(); ++it)
		{
			if (component_type == (*it)->GetComponentType())
				return *it;
		}
		return nullptr;
	}
}