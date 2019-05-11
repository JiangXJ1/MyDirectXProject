#include "SystemClass.h"
#include "Math/Vector3.h"
#include "Math/Quaternion.h"
#include "Math/Matrix4x4.h"
#include "Math/mymath.h"
#include <cmath>
using namespace Math;
static SystemClass* D3DAPP = NULL;

//接受SystemClass类对象的全局回调函数
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
	{
		PostQuitMessage(0);  //发送WM_QUIT消息到消息队列 接收到WM_QUIT跳出消息循环
		return 0;
	}

	case WM_CLOSE:
	{
		PostQuitMessage(0);
		return 0;
	}

	//将其它消息传送到D3DAPP的MessageHandler函数
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

	//初始化屏幕宽高
	screenWidth = 0;
	screenHeight = 0;

	//初始化窗口
	InitializeWindow(screenWidth, screenHeight);

	//创建输入对象
	m_pInput = new InputClass();
	if (!m_pInput)
		return false;

	m_pInput->Initialize();

	//创建渲染对象
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
	//执行循环接受来自窗口或系统的消息
	while (!done)
	{
		//操作窗口消息
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				done = true;
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);       //把消息发送到WindProc()中
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
		return DefWindowProc(hWnd, message, wParam, lPAram); //为全局静态函数
	}
}

void SystemClass::InitializeWindow(int& screenWidth, int& screenHeight)
{
	WNDCLASSEX wc;
	DEVMODE dmScrrenSettings;
	int posX, posY;

	//获取一个额外的指向这个对象的指针
	D3DAPP = this;

	//获取应用实例句柄
	mHinstance = GetModuleHandle(NULL);

	//给予应用一个名字
	mApplicationName = L"Engine";

	//设定要创建的类的属性	
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

	//注册这个类
	RegisterClassEx(&wc);

	//获取屏幕分辨率的宽度和高度
	screenWidth = GetSystemMetrics(SM_CXSCREEN);
	screenHeight = GetSystemMetrics(SM_CYSCREEN);

	//取决于是否为全屏幕
	if (FULL_SCREEN)
	{
		//如果为全屏幕,则设定屏幕为用户桌面的最大化并且为32bit
		memset(&dmScrrenSettings, 0, sizeof(dmScrrenSettings));
		dmScrrenSettings.dmSize = sizeof(dmScrrenSettings);
		dmScrrenSettings.dmPelsWidth = (unsigned long)screenWidth;
		dmScrrenSettings.dmPelsHeight = (unsigned long)screenHeight;
		dmScrrenSettings.dmBitsPerPel = 32;
		dmScrrenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		//改变显示设定,设置为全屏幕
		ChangeDisplaySettings(&dmScrrenSettings, CDS_FULLSCREEN);

		//设定窗口左上角的位置
		posX = posY = 0;
	}
	else
	{
		//如果窗口化,设定为800*600分辨率
		screenWidth = 800;
		screenHeight = 600;

		//窗口位于屏幕稍微的左上方
		posX = (GetSystemMetrics(SM_CXSCREEN) - screenWidth) / 2 - 200;
		posY = (GetSystemMetrics(SM_CYSCREEN) - screenHeight) / 2 - 100;

	}

	//创建窗口,并且获取窗口的句柄
	hWnd = CreateWindowEx(WS_EX_APPWINDOW, mApplicationName, mApplicationName,
		WS_OVERLAPPEDWINDOW,
		posX, posY, screenWidth, screenHeight, NULL, NULL, mHinstance, NULL);

	//将窗口显示于屏幕之上,并设定该窗口为主要集中点
	ShowWindow(hWnd, SW_SHOW);
	SetForegroundWindow(hWnd);
	SetFocus(hWnd);

	//隐藏鼠标光标
	//ShowCursor(false);
}

void SystemClass::ShutdownWindow()
{
	//显示鼠标光标
	//ShowCursor(true);

	//如果离开全屏幕模式,恢复显示设定
	if (FULL_SCREEN)
	{
		ChangeDisplaySettings(NULL, 0);
	}

	//移除(破坏)窗口
	DestroyWindow(hWnd);
	hWnd = NULL;

	//移除程序实例
	UnregisterClass(mApplicationName, mHinstance);
	mHinstance = NULL;

	//置空应用类对象
	D3DAPP = NULL;

}
