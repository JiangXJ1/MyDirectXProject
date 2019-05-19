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
		SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, rc.right, rc.bottom,SWP_SHOWWINDOW);
	}
	else
	{
		SetWindowLong(hWnd, GWL_STYLE, style);
		int posX = (rc.right - rc.left - width) / 2;
		int posY = (rc.bottom - rc.top - height) / 2;
		SetWindowPos(hWnd, HWND_TOPMOST, posX, posY, width, height, SWP_SHOWWINDOW);
	}
}

MyWindow::MyWindow(LPCWSTR name) : mApplicationName{name}, width {1280}, height{720}, fullscreen{false}
{

}

MyWindow::MyWindow(int w, int h, bool full, LPCWSTR name) : mApplicationName{ name }, width{ w }, height{ h }, fullscreen{ full }
{
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
	RECT    rc;
	HWND hDesk = GetDesktopWindow();
	GetWindowRect(hDesk, &rc);


	int posX = (rc.right - rc.left - width) / 2;
	int posY = (rc.bottom - rc.top - height) / 2;
	//创建窗口,并且获取窗口的句柄
	hWnd = CreateWindowEx(WS_EX_APPWINDOW, mApplicationName, mApplicationName,
		WS_OVERLAPPEDWINDOW,
		posX, posY, width, height, NULL, NULL, mHinstance, NULL);
	style = GetWindowLong(hWnd, GWL_STYLE);
	//将窗口显示于屏幕之上,并设定该窗口为主要集中点
	ShowWindow(hWnd, SW_SHOW);
	SetForegroundWindow(hWnd);
	SetFocus(hWnd);
	m_pInput = new InputClass();
	m_pInput->Initialize();
	(*allWindow)[hWnd] = this;
	//隐藏鼠标光标
	//ShowCursor(false);
	ReflushWindowSize();
}

void MyWindow::Hide()
{
	if (m_pInput != NULL) 
	{
		m_pInput->Clear();
		delete m_pInput;
		m_pInput = NULL;
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
	if (m_pInput->IsKeyDown(VK_F1)) {
		this->SetFullScreen(false);
	}
	if (m_pInput->IsKeyDown(VK_F2)) {
		this->SetFullScreen(true);
	}
	if (m_pInput->IsKeyDown(VK_F3)) {
		this->SetWindowSize(800, 600);
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
	if (m_pInput != nullptr) 
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
		}
	}
	return Application->MessageHandler(hwnd, message, wParam, lParam);
}
