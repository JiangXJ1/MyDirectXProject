#pragma once
#ifndef _MY_WINDOW_H
#define _MY_WINDOW_H

#include <Windows.h>
#include "GraphicsClass.h"

class MyWindow
{
public:
	int posX, posY;
	int width, height;
	bool fullscreen;
private:
	LPCWSTR mApplicationName;//应用名称
	HINSTANCE mHinstance;//应用实例句柄
	HWND hWnd;//应用窗口句柄
	long style;
	GraphicsClass* m_pGraphic;

private:
	void ReflushWindowSize();
public:
	MyWindow(LPCWSTR name = NULL);
	MyWindow(int w, int h, bool full, LPCWSTR name = NULL);
	~MyWindow();
	void Show();
	void Hide();
	void Frame();
	bool IsShowing();
	void SetFullScreen(const bool fullScreen);
	void SetWindowSize(const int w, const int h);
	LRESULT MessageHandler(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
};
#endif