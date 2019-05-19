#include "SystemClass.h"
#include "Math/Vector3.h"
#include "Math/Quaternion.h"
#include "Math/Matrix4x4.h"
#include "Math/mymath.h"
#include <cmath>
using namespace Math;

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

	//获取一个额外的指向这个对象的指针
	if (Application == NULL)
		Application = this;
	else
		return false;
	mainWindow = CreateMyWindow(1280, 720, false, L"主窗口");
	mainWindow->Show();
	return true;
}

void SystemClass::Shutdown()
{

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

MyWindow * SystemClass::CreateMyWindow(int width, int height, bool fullScreen, LPCWSTR name)
{
	auto window = new MyWindow(width, height, fullScreen, name);
	return window;
}

bool SystemClass::Frame()
{
	if (mainWindow != nullptr) 
	{
		if (!mainWindow->IsShowing()) {
			delete mainWindow;
			mainWindow = nullptr;
			return false;
		}
		else
		{
			mainWindow->Frame(); 
		}
	}
	return true;
}

LRESULT CALLBACK SystemClass::MessageHandler(HWND hWnd, UINT message, WPARAM wParam, LPARAM lPAram)
{
	return DefWindowProc(hWnd, message, wParam, lPAram); //为全局静态函数
}
