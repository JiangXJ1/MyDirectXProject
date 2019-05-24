#include "GraphicsClass.h"
#include <algorithm>
#ifndef SAFE_RELEASE
#define SAFE_RELEASE(p) \
  if ((p) != NULL) {            \
    (p)->Release();         \
    (p) = NULL;         \
  }
#endif
bool sortComp(Camera* a, Camera* b) 
{
	return a->GetDepth() < b->GetDepth();
}
void GraphicsClass::ReflushCameraDepth()
{
	sort(vCameras.begin(), vCameras.end(), sortComp);
}
GraphicsClass::GraphicsClass()
	:m_pDevice(nullptr),
	m_pDeviceContext(nullptr),
	m_pRenderTargetView(nullptr),
	m_pDepthStencilView(nullptr),
	m_pDepthStencil(nullptr),
	m_pSwapChain(nullptr),
	width(0),
	height(0)
{
}


GraphicsClass::~GraphicsClass()
{
	for (auto a = vCameras.begin(); a != vCameras.end(); ++a)
	{
		delete *a;
	}
	vCameras.clear();
	SAFE_RELEASE(m_pDevice);
	SAFE_RELEASE(m_pDeviceContext);
	SAFE_RELEASE(m_pRenderTargetView);
	SAFE_RELEASE(m_pDepthStencilView);
	SAFE_RELEASE(m_pDepthStencil);
	SAFE_RELEASE(m_pSwapChain);
}

void GraphicsClass::Render()
{
	for (auto a = vCameras.begin(); a != vCameras.end(); ++a)
	{
		(*a)->Render();
	}
	D3D11_VIEWPORT vp;    //����һ���ӿڵĶ���
	unsigned int n = 1;
	m_pDeviceContext->RSGetViewports(&n, &vp);
	//���Ĳ��������ӿڴ�С��D3D11Ĭ�ϲ��������ӿڣ��˲�������ֶ�����  
	m_pSwapChain->Present(NULL, NULL);
}

void GraphicsClass::ClearColor(Color& backColor)
{
	float* c = (float*)&backColor;
	m_pDeviceContext->ClearRenderTargetView(m_pRenderTargetView, c);
}

void GraphicsClass::ResetSize(int WINDOW_WIDTH, int WINDOW_HEIGHT)
{
	if (WINDOW_WIDTH == width && WINDOW_HEIGHT == height)
		return;
	D3D11_VIEWPORT vp;    //����һ���ӿڵĶ���
	unsigned int n = 1;
	m_pDeviceContext->RSGetViewports(&n, &vp);
	vp.Width = (float)WINDOW_WIDTH;
	vp.Height= (float)WINDOW_HEIGHT;
	m_pDeviceContext->RSSetViewports(n, &vp);
}

HRESULT GraphicsClass::Initialize(HWND hwnd, int WINDOW_WIDTH, int WINDOW_HEIGHT)
{   
	width = (float)WINDOW_WIDTH;
	height = (float)WINDOW_HEIGHT;
	//����������
	DXGI_SWAP_CHAIN_DESC scDesc;
	::ZeroMemory(&scDesc, sizeof(scDesc));
	scDesc.OutputWindow = hwnd;     //�����������
	scDesc.BufferCount = 1;//��������
	scDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;//������̨�����ʽ
	scDesc.BufferDesc.Width = WINDOW_WIDTH; //������̨����ֱ��ʿ��
	scDesc.BufferDesc.Height = WINDOW_HEIGHT;//������̨����ֱ��ʸ߶�
	scDesc.BufferDesc.RefreshRate.Denominator = 1;//ˢ��Ƶ�ʵķ�ĸ
	scDesc.BufferDesc.RefreshRate.Numerator = 60;//ˢ��Ƶ�ʵķ��ӣ����������ÿ��ˢ��6��
	scDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	scDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	scDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scDesc.Flags = 0;
	scDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	scDesc.SampleDesc.Count = 1;    //���ﲻʹ�ö��ز��������������Ϊ1
	scDesc.SampleDesc.Quality = 0;  //��ʹ�ö��ز�������Ϊ0
	scDesc.Windowed = true;         //����Ϊ����ģʽ

	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_0,     //D3D11.0 ��֧�ֵĹ�������
		D3D_FEATURE_LEVEL_10_1,     //D3D10.1 ��֧�ֵĹ�������
		D3D_FEATURE_LEVEL_10_0      //D3D10.0 ��֧�ֵĹ�������
	};
	UINT numFeature = ARRAYSIZE(featureLevels);

	HRESULT te;
	//�����豸���豸�����ģ�������
	if (FAILED(te = D3D11CreateDeviceAndSwapChain(
		NULL,
		D3D_DRIVER_TYPE_HARDWARE, NULL, 0,
		featureLevels, numFeature,
		D3D11_SDK_VERSION, &scDesc,
		&m_pSwapChain, &m_pDevice, NULL, &m_pDeviceContext)))
	{
		MessageBox(NULL, L"Create Device and Swapchain Error", L"Error", NULL);
		return E_FAIL;
	}

	//��ȡ��̨������
	ID3D11Texture2D *pBack = NULL;
	if (FAILED(m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&pBack))) {
		MessageBox(NULL, L"GetBuffer Error", L"Error", NULL);
		return E_FAIL;
	}

	//������ȾĿ����ͼ
	HRESULT hr;
	hr = m_pDevice->CreateRenderTargetView(pBack, NULL, &m_pRenderTargetView);

	SAFE_RELEASE(pBack)
	if (FAILED(hr))
	{
		MessageBox(NULL, L"Create Render Target View Error", L"Error", NULL);
		return E_FAIL;
	}

	//�������ģ�建��
	D3D11_TEXTURE2D_DESC dsDesc;
	ZeroMemory(&dsDesc, sizeof(dsDesc));
	dsDesc.ArraySize = 1;
	dsDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	dsDesc.CPUAccessFlags = 0;
	dsDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	dsDesc.Height = WINDOW_HEIGHT;
	dsDesc.Width = WINDOW_WIDTH;
	dsDesc.MipLevels = 1;
	dsDesc.MiscFlags = 0;
	dsDesc.SampleDesc.Count = 1;
	dsDesc.SampleDesc.Quality = 0;
	dsDesc.Usage = D3D11_USAGE_DEFAULT;

	if (FAILED(m_pDevice->CreateTexture2D(&dsDesc, NULL, &m_pDepthStencil)))
	{
		MessageBox(NULL, L"Create Depth Stencil Buffer Error", L"Error", NULL);
		return E_FAIL;
	}

	if (FAILED(m_pDevice->CreateDepthStencilView(m_pDepthStencil, 0, &m_pDepthStencilView)))
	{
		MessageBox(NULL, L"Create Depth Stencil Buffer View Error", L"Error", NULL);
		return E_FAIL;
	}

	m_pDeviceContext->OMSetRenderTargets(1, &m_pRenderTargetView, m_pDepthStencilView);

	//���Ĳ��������ӿڴ�С��D3D11Ĭ�ϲ��������ӿڣ��˲�������ֶ�����  
	D3D11_VIEWPORT vp;    //����һ���ӿڵĶ���
	vp.TopLeftX = 0;      //�ӿ����Ͻǵĺ�����
	vp.TopLeftY = 0;      //�ӿ����Ͻǵ�������
	vp.Width = (FLOAT)WINDOW_WIDTH;     //�ӿڵĿ�
	vp.Height = (FLOAT)WINDOW_HEIGHT;   //�ӿڵĸ�
	vp.MinDepth = 0.0f;   //���ֵ�����ޣ�**�������ֵ��[0, 1]��������ֵ��0
	vp.MaxDepth = 1.0f;   //���ֵ�����ޣ�����ֵ��1

	m_pDeviceContext->RSSetViewports(1, &vp);

	return S_OK;
}

Camera * GraphicsClass::CreateCamera(int depth, char clearFlag)
{
	float ratio = width / height;
	Camera* camera = new Camera(this, ratio, depth, clearFlag);
	vCameras.push_back(camera);
	ReflushCameraDepth();
	return camera;
}

bool GraphicsClass::RemoveCamera(Camera * camera)
{
	for (auto a = vCameras.begin(); a != vCameras.end(); ++a)
	{
		auto c = *a;
		if (c == camera) 
		{
			vCameras.erase(a);
			delete camera;
			ReflushCameraDepth();
			return true;
		}
	}
	return false;
}
