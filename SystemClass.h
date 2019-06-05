#pragma once
#ifndef SYSTEM_CLASS_H
#define SYSTEM_CLASS_H
#define WIN32_LEAN_AND_MEAN  //�������Լ���Win32ͷ�ļ��Ĵ�С
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
	//֡����
	bool Frame();

public:
	SystemClass();

	~SystemClass();

	void Initialize();

	void Shutdown();

	void Run();

	void PushWaste(void* p);

	MyWindow* CreateMyWindow(int width, int height, bool fullScreen, LPCWSTR name);

	//��Ϣ��������,��������������ܵ���Ϣ�ܶഫ�ݸ�ȫ�־�̬����WndProc����,����ص�������Щ����
	LRESULT CALLBACK MessageHandler(HWND hWnd, UINT message, WPARAM wParam, LPARAM lPAram);
};

extern SystemClass* Application;
extern InputClass* Input;
extern ObjectManager* ObjectMgr;
#endif