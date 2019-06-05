#pragma once
#ifndef _OBJECT_MANAGER_H
#define _OBJECT_MANAGER_H
#include <vector>
namespace Engine {
	class SceneObject;
	class Camera;
	class Renderer;
	class Component;
}
using namespace std;
using namespace Engine;
class ObjectManager
{
public:
	vector<SceneObject *> sceneobjects;
	vector<Camera*> cameras;
	vector<Renderer*> renders;
	vector<Component*> components;
public:
	ObjectManager();
	~ObjectManager();
public:
	SceneObject& ObjectManager::CreateSceneObject(SceneObject * parent);
	void PushComponent(Component* component);
	void PushCamera(Camera* camera);
	void PushRenderer(Renderer* render);
};

#endif // !_OBJECT_MANAGER_H

