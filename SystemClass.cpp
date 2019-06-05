#include "SystemClass.h"
#include "Math/Vector3.h"
#include "Math/Quaternion.h"
#include "Math/Matrix4x4.h"
#include "Math/mymath.h"
#include <cmath>
using namespace Math;
using namespace Engine;

SystemClass* Application = new SystemClass;
InputClass* Input = new InputClass;
ObjectManager* ObjectMgr = new ObjectManager;

SystemClass::SystemClass() : mainWindow{ nullptr }, frame{0}
{
}

SystemClass::~SystemClass()
{
}

void SystemClass::Initialize()
{
	frame = 0;
	mainWindow = CreateMyWindow(600, 400, false, L"������");
	mainWindow->Show();
}

void SystemClass::Shutdown()
{

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

void SystemClass::PushWaste(void * p)
{
	wastes.push_back(p);
}

MyWindow * SystemClass::CreateMyWindow(int width, int height, bool fullScreen, LPCWSTR name)
{
	auto window = new MyWindow(width, height, fullScreen, name);
	return window;
}

bool SystemClass::Frame()
{
	for (auto it = wastes.begin(); it != wastes.end(); ++it) {
		delete (*it);
	}
	wastes.clear();
	frame++;
	if (mainWindow != nullptr) 
	{
		if (!mainWindow->IsShowing()) {
			delete mainWindow;
			mainWindow = nullptr;
			return false;
		}
		else
		{
			Input->Frame();
			mainWindow->Frame(); 
		}
	}
	return true;
}

LRESULT CALLBACK SystemClass::MessageHandler(HWND hWnd, UINT message, WPARAM wParam, LPARAM lPAram)
{
	return DefWindowProc(hWnd, message, wParam, lPAram); //Ϊȫ�־�̬����
}
