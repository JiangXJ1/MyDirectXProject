#include "Renderer.h"
#include "../BaseDef.h"
#include "../../SystemClass.h"
namespace Engine
{

	Renderer::Renderer(SceneObject * owner)
		: Component(owner, COMPONENT_RENDERER)
	{
		ObjectMgr->PushRenderer(this);
	}

	Renderer::~Renderer()
	{
	}
}