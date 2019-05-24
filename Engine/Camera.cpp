#include "Camera.h"
#include "../GraphicsClass.h"

namespace Engine {
	Camera::Camera(GraphicsClass* pGraphic, float rect_ratio, int render_depth, char clear_flag)
		: m_pGraphic(pGraphic), aspectRatio(rect_ratio), depth(render_depth), clearFlags(clear_flag)
	{
	}

	Camera::~Camera()
	{
	}

	void Camera::Render()
	{
		if ((clearFlags & CameraClearFlags::ClearWithColor) > 0) {
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