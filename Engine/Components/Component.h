#pragma once
#ifndef _COMPONENT_H
#define _COMPONENT_H
#include "../SceneObject.h"
using namespace std;
namespace Engine {
	class Component
	{
	protected:
		bool enabled;
	public:
		const SceneObject* m_pOwnObject;
	public:
		Component(const SceneObject* pObj);
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
	};
}
#endif // !_COMPONENT_H
