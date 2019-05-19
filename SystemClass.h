#pragma once
#ifndef SYSTEM_CLASS_H
#define SYSTEM_CLASS_H
#define WIN32_LEAN_AND_MEAN  //这个宏可以减少Win32头文件的大小
#include <map>
#include <Windows.h>
#include "MyWindow.h"

class SystemClass
{
private:
	MyWindow* mainWindow;
private:
	//帧函数
	bool Frame();

public:
	SystemClass();

	SystemClass(const SystemClass& other);

	~SystemClass();

	bool Initialize();

	void Shutdown();

	void Run();

	MyWindow* CreateMyWindow(int width, int height, bool fullScreen, LPCWSTR name);

	//消息操作函数,这里这个函数接受的消息很多传递给全局静态函数WndProc处理,这个回调函数有些特殊
	LRESULT CALLBACK MessageHandler(HWND hWnd, UINT message, WPARAM wParam, LPARAM lPAram);
};

static SystemClass* Application;
#endif