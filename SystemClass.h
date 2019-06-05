#pragma once
#ifndef SYSTEM_CLASS_H
#define SYSTEM_CLASS_H
#define WIN32_LEAN_AND_MEAN  //这个宏可以减少Win32头文件的大小
#include <map>
#include <Windows.h>
#include "MyWindow.h"
#include "InputClass.h"
#include "vector"
#include "ObjectManager.h"

class SystemClass
{
public:
	unsigned int frame;
private:
	MyWindow* mainWindow;
	vector<void*>  wastes;
private:
	//帧函数
	bool Frame();

public:
	SystemClass();

	~SystemClass();

	void Initialize();

	void Shutdown();

	void Run();

	void PushWaste(void* p);

	MyWindow* CreateMyWindow(int width, int height, bool fullScreen, LPCWSTR name);

	//消息操作函数,这里这个函数接受的消息很多传递给全局静态函数WndProc处理,这个回调函数有些特殊
	LRESULT CALLBACK MessageHandler(HWND hWnd, UINT message, WPARAM wParam, LPARAM lPAram);
};

extern SystemClass* Application;
extern InputClass* Input;
extern ObjectManager* ObjectMgr;
#endif