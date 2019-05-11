#include "SystemClass.h"
#include "Math/Vector3.h"
#include "Math/Quaternion.h"
#include "Math/Matrix4x4.h"
#include "Math/mymath.h"
#include <cmath>
using namespace Math;
static SystemClass* D3DAPP = NULL;

//����SystemClass������ȫ�ֻص�����
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
	{
		PostQuitMessage(0);  //����WM_QUIT��Ϣ����Ϣ���� ���յ�WM_QUIT������Ϣѭ��
		return 0;
	}

	case WM_CLOSE:
	{
		PostQuitMessage(0);
		return 0;
	}

	//��������Ϣ���͵�D3DAPP��MessageHandler����
	default:
		return D3DAPP->MessageHandler(hwnd, message, wParam, lParam);

	}
}

SystemClass::SystemClass()
{
}


SystemClass::SystemClass(const SystemClass& other)
{
}

SystemClass::~SystemClass()
{
}

bool SystemClass::Initialize()
{
	int screenWidth, screenHeight;
	bool result;

	//��ʼ����Ļ���
	screenWidth = 0;
	screenHeight = 0;

	//��ʼ������
	InitializeWindow(screenWidth, screenHeight);

	//�����������
	m_pInput = new InputClass();
	if (!m_pInput)
		return false;

	m_pInput->Initialize();

	//������Ⱦ����
	m_pGraphic = new GraphicsClass();
	if (!m_pGraphic)
		return false;
	result = m_pGraphic->Initialize(screenWidth, screenHeight, hWnd);
	if (!result)
		return false;
	return true;
}

void SystemClass::Shutdown()
{
	if (m_pGraphic)
	{
		m_pGraphic->ShutDown();
		delete m_pGraphic;
		m_pGraphic = NULL;
	}

	if (m_pInput)
	{
		delete m_pInput;
		m_pInput = NULL;
	}

	this->ShutdownWindow();
}

void SystemClass::Run()
{
	MSG msg = { 0 };
	bool done, result;
	done = false;
	//ִ��ѭ���������Դ��ڻ�ϵͳ����Ϣ
	while (!done)
	{
		//����������Ϣ
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				done = true;
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);       //����Ϣ���͵�WindProc()��
		}
		else
		{
			result = Frame();
			if (!result)
			{
				done = true;
			}
		}
	}
}

bool SystemClass::Frame()
{
	if (m_pInput->IsKeyDown(VK_ESCAPE))
	{
		return false;
	}

	if (m_pInput->IsKeyDown(VK_F1)) {
		Quaternion q;
		q.EulerAngle(45, 15, 100);
		q.Normalize();
		Vector3 v1;
		q.ToEulerAngles(v1);
		int n = 0;
	}

	bool r = m_pGraphic->Frame();
	if (!r)
		return false;

	return true;
}

LRESULT CALLBACK SystemClass::MessageHandler(HWND hWnd, UINT message, WPARAM wParam, LPARAM lPAram)
{
	switch (message)
	{
	case WM_KEYDOWN:
	{
		m_pInput->KeyDown(wParam);
		return 0;
	}
	case  WM_KEYUP:
	{
		m_pInput->KeyUp(wParam);
		return 0;
	}
	default:
		return DefWindowProc(hWnd, message, wParam, lPAram); //Ϊȫ�־�̬����
	}
}

void SystemClass::InitializeWindow(int& screenWidth, int& screenHeight)
{
	WNDCLASSEX wc;
	DEVMODE dmScrrenSettings;
	int posX, posY;

	//��ȡһ�������ָ����������ָ��
	D3DAPP = this;

	//��ȡӦ��ʵ�����
	mHinstance = GetModuleHandle(NULL);

	//����Ӧ��һ������
	mApplicationName = L"Engine";

	//�趨Ҫ�������������	
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = mHinstance;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hIconSm = wc.hIcon;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = mApplicationName;
	wc.cbSize = sizeof(WNDCLASSEX);

	//ע�������
	RegisterClassEx(&wc);

	//��ȡ��Ļ�ֱ��ʵĿ�Ⱥ͸߶�
	screenWidth = GetSystemMetrics(SM_CXSCREEN);
	screenHeight = GetSystemMetrics(SM_CYSCREEN);

	//ȡ�����Ƿ�Ϊȫ��Ļ
	if (FULL_SCREEN)
	{
		//���Ϊȫ��Ļ,���趨��ĻΪ�û��������󻯲���Ϊ32bit
		memset(&dmScrrenSettings, 0, sizeof(dmScrrenSettings));
		dmScrrenSettings.dmSize = sizeof(dmScrrenSettings);
		dmScrrenSettings.dmPelsWidth = (unsigned long)screenWidth;
		dmScrrenSettings.dmPelsHeight = (unsigned long)screenHeight;
		dmScrrenSettings.dmBitsPerPel = 32;
		dmScrrenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		//�ı���ʾ�趨,����Ϊȫ��Ļ
		ChangeDisplaySettings(&dmScrrenSettings, CDS_FULLSCREEN);

		//�趨�������Ͻǵ�λ��
		posX = posY = 0;
	}
	else
	{
		//������ڻ�,�趨Ϊ800*600�ֱ���
		screenWidth = 800;
		screenHeight = 600;

		//����λ����Ļ��΢�����Ϸ�
		posX = (GetSystemMetrics(SM_CXSCREEN) - screenWidth) / 2 - 200;
		posY = (GetSystemMetrics(SM_CYSCREEN) - screenHeight) / 2 - 100;

	}

	//��������,���һ�ȡ���ڵľ��
	hWnd = CreateWindowEx(WS_EX_APPWINDOW, mApplicationName, mApplicationName,
		WS_OVERLAPPEDWINDOW,
		posX, posY, screenWidth, screenHeight, NULL, NULL, mHinstance, NULL);

	//��������ʾ����Ļ֮��,���趨�ô���Ϊ��Ҫ���е�
	ShowWindow(hWnd, SW_SHOW);
	SetForegroundWindow(hWnd);
	SetFocus(hWnd);

	//���������
	//ShowCursor(false);
}

void SystemClass::ShutdownWindow()
{
	//��ʾ�����
	//ShowCursor(true);

	//����뿪ȫ��Ļģʽ,�ָ���ʾ�趨
	if (FULL_SCREEN)
	{
		ChangeDisplaySettings(NULL, 0);
	}

	//�Ƴ�(�ƻ�)����
	DestroyWindow(hWnd);
	hWnd = NULL;

	//�Ƴ�����ʵ��
	UnregisterClass(mApplicationName, mHinstance);
	mHinstance = NULL;

	//�ÿ�Ӧ�������
	D3DAPP = NULL;

}
