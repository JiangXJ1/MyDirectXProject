#pragma once
#ifndef _CAMERA_H
#define _CAMERA_H
#include "../Color.h"
#include "Component.h"
#include "../BaseDef.h"
#include "../../Math/Vector3.h"
#include "../../Math/Matrix4x4.h"
#include "../../Math/Quaternion.h"
class GraphicsClass;

using namespace Math;
namespace Engine {
	class Camera:public Component
	{
	private:
		char clearFlags = 0;
		int depth = 0;//相机深度
		float aspectRatio;//视口宽高比
		GraphicsClass* m_pGraphic;
		Color backGround;//背景颜色
		Matrix4x4 matrixProj;
	public:
		Camera(SceneObject* pOwnObj, GraphicsClass* pGraphic, float ratio, int depth, char clearFlag);
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
		inline virtual void OnEnable() {}
		inline virtual void OnDisable() {}

		inline virtual void Update() {}

		inline virtual void LateUpdate() {}
	};

}
#endif // !_CAMERA_H
