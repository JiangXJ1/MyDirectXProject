#pragma once
#ifndef GRAPHICS_CLASS_H
#define GRAPHICS_CLASS_H
#include <Windows.h>

//ȫ�ֱ���
const bool FULL_SCREEN = false;
const bool VSYNC_ENABLE = true;
const float SCREEN_DEPTH = 1000.0f;  //�ӽ���Զ����
const float SCREEN_NEAR = 0.1f;  //�ӽ��������

class GraphicsClass
{
private:
	bool Render();
public:
	GraphicsClass();
	GraphicsClass(const GraphicsClass& other);
	~GraphicsClass();
public:
	bool Initialize(int ScreenWidth, int ScreenHeight, HWND hwnd);
	void ShutDown();
	bool Frame();
};
#endif

