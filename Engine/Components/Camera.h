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
		//是否是正交相机
		bool isOrthogonal;
		//正交相机尺寸
		float size;
		//相机广角
		float fieldOfView;
		//远裁剪面
		float farClipPanel;
		//近裁剪面
		float nearClipPanel;
		Matrix4x4 matrixClip;
	public:
		Camera(SceneObject* pOwnObj, GraphicsClass* pGraphic, float ratio, int depth, char clearFlag);
		~Camera();
	private:
		void CalcClipMatrix();
	public:
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


		void SetSize(float viewSize);
		float GetSize() const;
		void SetFov(float fov);
		float GetFov() const;

	};

}
#endif // !_CAMERA_H
