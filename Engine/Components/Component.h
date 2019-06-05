#pragma once
#ifndef _COMPONENT_H
#define _COMPONENT_H
#include "../SceneObject.h"
#include "../../SystemClass.h"

using namespace std;
namespace Engine {
	class Component
	{
	private:
		unsigned int componentType;
	protected:
		bool destroyed;
		bool enabled;
		SceneObject* m_pOwnObject;
	public:
		Component(SceneObject* pObj, unsigned int type);
		virtual ~Component();
	public:
		inline virtual void OnEnable() = 0;
		inline virtual void OnDisable() = 0;

		inline void SetEnable(bool enable) {
			if (enabled == enable)
				return;
			enabled = enable;
			if (enabled)
				OnEnable();
			else
				OnDisable();
		}

		inline bool IsEnable() {
			return enabled;
		}

		inline virtual void Update() = 0;

		inline virtual void LateUpdate() = 0;

		inline bool IsDestroyed() 
		{
			return destroyed;
		}

		inline void Destroy() 
		{
			SetEnable(false);
			m_pOwnObject->RemoveComponent(this);
			destroyed = true;
		}

		inline unsigned int GetComponentType() 
		{
			return componentType;
		}
	};
}
#endif // !_COMPONENT_H
