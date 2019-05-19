#pragma once
#ifndef SYSTEM_CLASS_H
#define SYSTEM_CLASS_H
#define WIN32_LEAN_AND_MEAN  //�������Լ���Win32ͷ�ļ��Ĵ�С
#include <map>
#include <Windows.h>
#include "MyWindow.h"

class SystemClass
{
private:
	MyWindow* mainWindow;
private:
	//֡����
	bool Frame();

public:
	SystemClass();

	SystemClass(const SystemClass& other);

	~SystemClass();

	bool Initialize();

	void Shutdown();

	void Run();

	MyWindow* CreateMyWindow(int width, int height, bool fullScreen, LPCWSTR name);

	//��Ϣ��������,��������������ܵ���Ϣ�ܶഫ�ݸ�ȫ�־�̬����WndProc����,����ص�������Щ����
	LRESULT CALLBACK MessageHandler(HWND hWnd, UINT message, WPARAM wParam, LPARAM lPAram);
};

static SystemClass* Application;
#endif