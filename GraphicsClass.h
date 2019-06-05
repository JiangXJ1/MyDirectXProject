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
	//˽���ֶ�
private:
	vector<Camera*> vCameras;
	float width, height;
	//�����ӿ�
	ID3D11Device *m_pDevice;                    //DX�豸�ӿڣ��������ɸ��ָ����Ķ���
	ID3D11DeviceContext *m_pDeviceContext;      //DX�豸������,���������豸��Ⱦָ��

	//��ͼ����
	ID3D11RenderTargetView *m_pRenderTargetView;//DX��ȾĿ����ͼ��������˼
	ID3D11DepthStencilView *m_pDepthStencilView;//DX���ģ�建����ͼ
	ID3D11Texture2D        *m_pDepthStencil;    //���ģ�建��

	//ͼ�νӿ�
	IDXGISwapChain *m_pSwapChain;               //DXͼ�νӿڣ�������
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

