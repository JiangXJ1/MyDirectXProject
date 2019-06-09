#include "Camera.h"
#include "../../Math/mymath.h"
#include "../BaseDef.h"
#include "../../SystemClass.h"
#include "../../GraphicsClass.h"

namespace Engine {
	Camera::Camera(SceneObject* pOwnObj, GraphicsClass* pGraphic, float rect_ratio, int render_depth, char clear_flag)
		: Component(pOwnObj, COMPONENT_CAMERA), 
		m_pGraphic(pGraphic), 
		aspectRatio(rect_ratio), 
		depth(render_depth), 
		clearFlags(clear_flag),
		isOrthogonal(false),
		size(5),
		fieldOfView(40),
		farClipPanel(200),
		nearClipPanel(10)
	{
		ObjectMgr->PushCamera(this);
	}

	Camera::~Camera()
	{
	}

	void Camera::CalcClipMatrix()
	{
		matrixClip.Reset();
		if (!isOrthogonal) 
		{
			auto value = cot(fieldOfView * 0.5f);
			matrixClip[0][0] = value / aspectRatio;
			matrixClip[1][1] = value;
			matrixClip[2][2] = -(farClipPanel + nearClipPanel) / (farClipPanel - nearClipPanel);
			matrixClip[2][3] = -2 * farClipPanel * nearClipPanel / (farClipPanel - nearClipPanel);
			matrixClip[3][2] = -1;
		}
		else
		{
			matrixClip[0][0] = 1 / (aspectRatio * size);
			matrixClip[1][1] = 1 / size;
			matrixClip[2][2] = -2 / (farClipPanel - nearClipPanel);
			matrixClip[2][3] = -(farClipPanel + nearClipPanel) / (farClipPanel - nearClipPanel);
			matrixClip[3][2] = -1;
		}
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
	void Camera::SetSize(float viewSize)
	{
		if (size != viewSize) 
		{
			size = viewSize;
			if (isOrthogonal)
			{
				CalcProjMatrix();
			}
		}
	}
	float Camera::GetSize() const
	{
		return size;
	}
	void Camera::SetFov(float fov)
	{
		if (fieldOfView != fov)
		{
			fieldOfView = fov;
			if (!isOrthogonal)
			{
				CalcProjMatrix();
			}
		}
	}
	float Camera::GetFov() const
	{
		return fieldOfView;
	}
}