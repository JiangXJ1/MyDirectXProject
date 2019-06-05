#include "Camera.h"
#include "../BaseDef.h"
#include "../../SystemClass.h"
#include "../../GraphicsClass.h"

namespace Engine {
	Camera::Camera(SceneObject* pOwnObj, GraphicsClass* pGraphic, float rect_ratio, int render_depth, char clear_flag)
		: Component(pOwnObj, COMPONENT_CAMERA), 
		m_pGraphic(pGraphic), 
		aspectRatio(rect_ratio), 
		depth(render_depth), 
		clearFlags(clear_flag)
	{
		ObjectMgr->PushCamera(this);
	}

	Camera::~Camera()
	{
	}

	void Camera::Render()
	{
		if ((clearFlags & CAMERA_CLEAR_FLAG_COLOR) > 0) {
			m_pGraphic->ClearColor(backGround);
		}
	}

	void Camera::SetBackColor(const Color& c)
	{
		backGround.r = c.r;
		backGround.g = c.g;
		backGround.b = c.b;
		backGround.a = c.a;
	}

	void Camera::SetBackColor(const float & r, const float & g, const float & b, const float & a)
	{
		backGround.r = r;
		backGround.g = g;
		backGround.b = b;
		backGround.a = a;
	}

	void Camera::SetClearFlags(char flag)
	{
		clearFlags = flag;
	}
}