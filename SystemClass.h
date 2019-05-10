#pragma once
#ifndef SYSTEM_CLASS_H
#define SYSTEM_CLASS_H
#define WIN32_LEAN_AND_MEAN  //�������Լ���Win32ͷ�ļ��Ĵ�С
#include "GraphicsClass.h"
#include "InputClass.h"
#include <Windows.h>
class SystemClass
{
private:
	LPCWSTR mApplicationName;//Ӧ������
	HINSTANCE mHinstance;//Ӧ��ʵ�����
	HWND hWnd;//Ӧ�ô��ھ��

private:
	InputClass* m_pInput;//������
	GraphicsClass* m_pGraphic;//��Ⱦ��

private:
	//֡����
	bool Frame();

	//��ʼ�����ں���
	void InitializeWindow(int&, int&);

	//�رմ��ں���
	void ShutdownWindow();

public:
	SystemClass();

	SystemClass(const SystemClass& other);

	~SystemClass();

	bool Initialize();

	void Shutdown();

	void Run();

	//��Ϣ��������,��������������ܵ���Ϣ�ܶഫ�ݸ�ȫ�־�̬����WndProc����,����ص�������Щ����
	LRESULT CALLBACK MessageHandler(HWND hWnd, UINT message, WPARAM wParam, LPARAM lPAram);
};
#endif

