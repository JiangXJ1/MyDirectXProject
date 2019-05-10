#pragma once
#ifndef SYSTEM_CLASS_H
#define SYSTEM_CLASS_H
#define WIN32_LEAN_AND_MEAN  //这个宏可以减少Win32头文件的大小
#include "GraphicsClass.h"
#include "InputClass.h"
#include <Windows.h>
class SystemClass
{
private:
	LPCWSTR mApplicationName;//应用名称
	HINSTANCE mHinstance;//应用实例句柄
	HWND hWnd;//应用窗口句柄

private:
	InputClass* m_pInput;//输入类
	GraphicsClass* m_pGraphic;//渲染类

private:
	//帧函数
	bool Frame();

	//初始化窗口函数
	void InitializeWindow(int&, int&);

	//关闭窗口函数
	void ShutdownWindow();

public:
	SystemClass();

	SystemClass(const SystemClass& other);

	~SystemClass();

	bool Initialize();

	void Shutdown();

	void Run();

	//消息操作函数,这里这个函数接受的消息很多传递给全局静态函数WndProc处理,这个回调函数有些特殊
	LRESULT CALLBACK MessageHandler(HWND hWnd, UINT message, WPARAM wParam, LPARAM lPAram);
};
#endif

