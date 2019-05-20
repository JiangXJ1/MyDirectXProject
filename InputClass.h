#pragma once

#ifndef _INPUT_CLASS_H
#define _INPUT_CLASS_H

class InputClass
{

private:
	bool mCacheKeyState[256];
	bool mHasKey[256];
	unsigned int mKeyFrame[256];
public:
	InputClass();
	InputClass(const InputClass& other);
	~InputClass();
public:
	void KeyDown(unsigned int wParam);
	void KeyUp(unsigned int wParam);
	bool IsKeyDown(unsigned int wParam);
	bool IsKeyUp(unsigned int wParam);
	bool HasKey(unsigned int wParam);
	void Frame();
};
#endif

