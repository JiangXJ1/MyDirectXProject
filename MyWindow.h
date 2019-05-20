#pragma once
#ifndef _MY_WINDOW_H
#define _MY_WINDOW_H

#include <Windows.h>

class MyWindow
{
public:
	int width, height;
	bool fullscreen;
private:
	LPCWSTR mApplicationName;//Ӧ������
	HINSTANCE mHinstance;//Ӧ��ʵ�����
	HWND hWnd;//Ӧ�ô��ھ��
	long style;

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