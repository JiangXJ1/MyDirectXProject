#pragma once
#ifndef _CAMERA_H
#define _CAMERA_H
#include "Color.h"
#include "../Math/Vector3.h"
#include "../Math/Matrix4x4.h"
#include "../Math/Quaternion.h"
class GraphicsClass;

using namespace Math;
namespace Engine {
	enum CameraClearFlags
	{
		DontClear = 0,
		ClearWithColor = 1,
		ClearWithDepth = 2,
		ClearWithColorAndDepth = 3
	};
	class Camera
	{
	private:
		char clearFlags = 0;
		int depth = 0;//相机深度
		float aspectRatio;//视口宽高比
		GraphicsClass* m_pGraphic;
		Color backGround;//背景颜色
		Matrix4x4 matProj;
		Matrix4x4 matView;
	public:
		Camera(GraphicsClass* pGraphic, float ratio, int depth = 0, char clearFlag = CameraClearFlags::ClearWithColorAndDepth);
		~Camera();
		void Render();
		void SetBackColor(const Color& c);
		void SetBackColor(const float& r, const float& g, const float& b, const float& a);
		void SetClearFlags(char flag);

		inline void SetDepth(int d) 
		{
			depth = d;
		}
		inline int GetDepth() 
		{
			return depth;
		}
	};

}
#endif // !_CAMERA_H
