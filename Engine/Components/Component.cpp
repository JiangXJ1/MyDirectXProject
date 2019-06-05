#include "Component.h"
namespace Engine{

	Component::Component(SceneObject * pObj, unsigned int type)
		: m_pOwnObject( pObj ), enabled(true), destroyed(false), componentType(type)
	{
	}

	Component::~Component()
	{
		m_pOwnObject = nullptr;
	}
}