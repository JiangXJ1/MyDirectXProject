#pragma once
#ifndef _RENDERER_H
#define _RENDERER_H
#include "Component.h"
#include "../SceneObject.h"
namespace Engine 
{
	class Renderer : public Component
	{
	public:
		Renderer(SceneObject* owner);
		~Renderer();

	private:

	};
}

#endif // !_RENDERER_H
