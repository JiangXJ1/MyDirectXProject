#include "Component.h"
namespace Engine{

	Component::Component(const SceneObject * pObj)
		: m_pOwnObject( pObj ), enabled(true)
	{
	}

	Component::~Component()
	{
		m_pOwnObject = nullptr;
	}
}