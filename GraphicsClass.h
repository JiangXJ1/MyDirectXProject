#pragma once
#ifndef GRAPHICS_CLASS_H
#define GRAPHICS_CLASS_H
#include <Windows.h>
#include <d3d11.h>
#include <vector>
#include "Engine/Color.h"
#include "Engine/BaseDef.h"
using namespace std;
using namespace Engine;

namespace Engine 
{
	class SceneObject;
	class Camera;
}

class GraphicsClass
{
	//私有字段
private:
	vector<Camera*> vCameras;
	float width, height;
	//基础接口
	ID3D11Device *m_pDevice;                    //DX设备接口，用于生成各种各样的对象
	ID3D11DeviceContext *m_pDeviceContext;      //DX设备上下文,用于生成设备渲染指令

	//视图区域
	ID3D11RenderTargetView *m_pRenderTargetView;//DX渲染目标视图，字面意思
	ID3D11DepthStencilView *m_pDepthStencilView;//DX深度模板缓存视图
	ID3D11Texture2D        *m_pDepthStencil;    //深度模板缓存

	//图形接口
	IDXGISwapChain *m_pSwapChain;               //DX图形接口，交换链
private:
	void ReflushCameraDepth();
public:
	GraphicsClass();
	~GraphicsClass();
public:
	void Render();
	void ClearColor(Color& backColor);
	void ResetSize(int WINDOW_WIDTH, int WINDOW_HEIGHT);
	HRESULT Initialize(HWND hwnd, int WINDOW_WIDTH, int WINDOW_HEIGHT);
	Camera* CreateCamera(SceneObject* pObj, int depth, char clearFlag);
	bool RemoveCamera(Camera* camera);
};
#endif

