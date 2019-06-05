#include "ObjectManager.h"
#include "Engine/SceneObject.h"
#include "Engine/Components/Component.h"
#include "Engine/Components/Renderer.h"
#include "Engine/Components/Camera.h"

ObjectManager::ObjectManager()
{
}


ObjectManager::~ObjectManager()
{
}

SceneObject& ObjectManager::CreateSceneObject(SceneObject * parent)
{
	SceneObject* pr = new SceneObject(parent);
	return *pr;
}

void ObjectManager::PushComponent(Component * component)
{
	components.push_back(component);
}

void ObjectManager::PushCamera(Camera * camera)
{
	cameras.push_back(camera);
}

void ObjectManager::PushRenderer(Renderer * render)
{
	renders.push_back(render);
}

