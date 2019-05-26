#include "MyWindow.h"
#include "SystemClass.h"
using namespace std;

static map<HWND, MyWindow*>* allWindow;
//接受SystemClass类对象的全局回调函数
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (allWindow != nullptr) 
	{
		
		auto pWindow = (*allWindow)[hwnd];
		if (pWindow != nullptr) {
			return pWindow->MessageHandler(hwnd, message, wParam, lParam);
		}
	}
	return Application->MessageHandler(hwnd, message, wParam, lParam);
}

void MyWindow::ReflushWindowSize()
{
	HWND    hDesk;
	RECT    rc;
	hDesk = GetDesktopWindow();
	GetWindowRect(hDesk, &rc);
	if (fullscreen) 
	{
		SetWindowLong(hWnd, GWL_STYLE, WS_BORDER);
		SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, rc.right, rc.bottom, SWP_SHOWWINDOW | SWP_NOZORDER);
	}
	else
	{
		SetWindowLong(hWnd, GWL_STYLE, style);
		SetWindowPos(hWnd, HWND_TOPMOST, posX, posY, width, height, SWP_SHOWWINDOW | SWP_NOZORDER);
	}
}

MyWindow::MyWindow(LPCWSTR name) 
	: mApplicationName{name}, 
	width {1280}, 
	height{720}, 
	fullscreen{false},
	m_pGraphic{nullptr}
{
	RECT    rc;
	HWND hDesk = GetDesktopWindow();
	GetWindowRect(hDesk, &rc);


	posX = (rc.right - rc.left - width) / 2;
	posY = (rc.bottom - rc.top - height) / 2;
}

MyWindow::MyWindow(int w, int h, bool full, LPCWSTR name) 
	: mApplicationName{ name }, 
	width{ w }, 
	height{ h }, 
	fullscreen{ full },
	m_pGraphic{ nullptr }
{
	RECT    rc;
	HWND hDesk = GetDesktopWindow();
	GetWindowRect(hDesk, &rc);


	posX = (rc.right - rc.left - width) / 2;
	posY = (rc.bottom - rc.top - height) / 2;
}


MyWindow::~MyWindow()
{
	Hide();
}

void MyWindow::Show()
{
	if(allWindow == nullptr)
		allWindow = new map<HWND, MyWindow*>;
	WNDCLASSEX wc;

	//获取应用实例句柄
	mHinstance = GetModuleHandle(NULL);

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
	//创建窗口,并且获取窗口的句柄
	hWnd = CreateWindowEx(WS_EX_APPWINDOW, mApplicationName, mApplicationName,
		WS_OVERLAPPEDWINDOW,
		posX, posY, width, height, NULL, NULL, mHinstance, NULL);
	style = GetWindowLong(hWnd, GWL_STYLE);
	//将窗口显示于屏幕之上,并设定该窗口为主要集中点
	ShowWindow(hWnd, SW_SHOW);
	SetForegroundWindow(hWnd);
	SetFocus(hWnd);
	(*allWindow)[hWnd] = this;
	//隐藏鼠标光标
	//ShowCursor(false);
	if(fullscreen)
		ReflushWindowSize();
	if (m_pGraphic == nullptr) 
	{
		m_pGraphic = new GraphicsClass;
		m_pGraphic->Initialize(hWnd, width, height);
	}
}

void MyWindow::Hide()
{
	if (m_pGraphic != nullptr)
	{
		delete m_pGraphic;
		m_pGraphic = nullptr;
	}
	if (hWnd != NULL) 
	{
		allWindow->erase(hWnd);
		//移除(破坏)窗口
		DestroyWindow(hWnd);
		hWnd = NULL;
	}

	if (mHinstance != NULL) 
	{
		//移除程序实例
		UnregisterClass(mApplicationName, mHinstance);
		mHinstance = NULL;
	}
}

void MyWindow::Frame()
{
	RECT rc;
	GetWindowRect(hWnd, &rc);
	int w = rc.right - rc.left;
	int h = rc.bottom - rc.top;
	if (m_pGraphic != nullptr)
		m_pGraphic->ResetSize(w, h);
	if (hWnd != NULL && !fullscreen)
	{
		if (posX != rc.left || posY != rc.top) {
			posX = rc.left;
			posY = rc.top;
		}
		if (w != width || h != height) 
		{
			width = w;
			height = h;
		}
	}
	if (Input != nullptr) {
		if (Input->IsKeyUp(VK_SPACE)) {
			this->SetFullScreen(!this->fullscreen);
		}
		if (Input->IsKeyUp(VK_F1)) {
			auto camera = this->m_pGraphic->CreateCamera(0, CameraClearFlags::ClearWithColor);
			camera->SetBackColor(1, 0, 0, 1);
		}
		if (Input->IsKeyUp(VK_F2)) {
			auto camera = this->m_pGraphic->CreateCamera(-1, CameraClearFlags::ClearWithColor);
			camera->SetBackColor(0, 0, 1, 0.5);
		}
		if (Input->IsKeyUp(VK_F3)) {
			float aaa[4][4] = {
				{1, 0, 0, 10},
				{0, 1, 0, 10},
				{0, 0, 1, 2},
				{0, 0, 0, 1}
			};
			Matrix4x4 m1(aaa);
			Vector3 v1(0, 0, 1);
			Vector3 v2(0, 0, 0);
			m1.multPointMatrix(v1, v2);
			Vector3 v3 = v2;
			v3 = v2;
			Matrix4x4 m2;
			Matrix4x4 m3;
			auto r = m1.Inverse(m2);
			m2.Transpose(m3);

			m2.multPointMatrix(v2, v3);
			int a = 0;
			m3.multPointMatrix(v2, v3);
			int n = 0;
		}
	}
	if (m_pGraphic != nullptr) {
		m_pGraphic->Render();
	}
}

bool MyWindow::IsShowing()
{
	return hWnd != NULL;
}

void MyWindow::SetFullScreen(const bool fullScreen)
{
	if (fullScreen == this->fullscreen)
		return;
	this->fullscreen = fullScreen;
	this->ReflushWindowSize();
}

void MyWindow::SetWindowSize(const int w, const int h)
{
	if (width == w && height == h)
		return;
	width = w;
	height = h;
	if (!fullscreen)
		ReflushWindowSize();
}

LRESULT MyWindow::MessageHandler(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
	{
		Hide();
		return 0;
	}

	case WM_CLOSE:
	{
		Hide();
		return 0;
	}

	case WM_KILLFOCUS:
	{
		int n = 0;
		break;
	}
	case WM_KEYDOWN:
	{
		Input->KeyDown((unsigned int)wParam);
		return 0;
	}
	case  WM_KEYUP:
	{
		Input->KeyUp((unsigned int)wParam);
		return 0;
	}
	}
	return Application->MessageHandler(hwnd, message, wParam, lParam);
}
