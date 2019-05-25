#include "Transform.h"

namespace Engine {
	Transform::Transform(const SceneObject* pObj)
		:Component(pObj), 
		localPosition{0,0,0}, 
		localScale{1,1,1}, 
		localRotation(0,0,0,1)
	{
	}
	Transform::~Transform()
	{

	}
	void Transform::SetEnable(bool enable)
	{
		
	}
}