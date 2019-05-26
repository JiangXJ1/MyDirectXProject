#include "Transform.h"

namespace Engine {
	Transform::Transform(const SceneObject* pObj)
		:Component(pObj), 
		localPosition{0,0,0}, 
		localScale{1,1,1}, 
		localRotation(0,0,0,1),
		matrixChanged(false),
		parent(NULL)
	{
	}
	Transform::~Transform()
	{

	}
	void Transform::SetMatrixChanged(bool changed)
	{
		if (changed == matrixChanged)
			return;
		matrixChanged = changed;
		if (changed) 
		{
			for (auto a = children.begin(); a != children.end(); ++a)
			{
				(*a)->SetMatrixChanged(true);
			}
		}
	}
	bool Transform::AddChild(Transform * child)
	{
		auto it = find(children.begin(), children.end(), child);
		if (it == children.end()) 
		{
			children.push_back(child);
			return true;
		}
		return false;
	}
	bool Transform::RemoveChild(Transform * child)
	{
		auto it = find(children.begin(), children.end(), child);
		if (it != children.end())
		{
			children.erase(it);
			return true;
		}
		return false;
	}
	void Transform::SetLocalPosition(const Vector3 & pos)
	{
		localPosition = pos;
	}
	inline const Vector3 & Transform::GetLocalPosition()
	{
		return localPosition;
	}
	void Transform::SetParent(Transform * newParent)
	{
		if (newParent == parent)
			return;
		if (parent != nullptr)
			parent->RemoveChild(this);
		newParent->AddChild(this);
		parent = newParent;
		SetMatrixChanged(true);
	}
	Transform * Transform::GetParent() const
	{
		return parent;
	}
}