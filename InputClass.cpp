#include "InputClass.h"
#include "SystemClass.h"


InputClass::InputClass()
{
	ZeroMemory(mHasKey, 256 * sizeof(bool));
	ZeroMemory(mCacheKeyState, 256 * sizeof(bool));
	ZeroMemory(mKeyFrame, 256 * sizeof(unsigned int));
}

InputClass::InputClass(const InputClass & other)
{
}


InputClass::~InputClass()
{
}

void InputClass::KeyDown(unsigned int wParam)
{
	mCacheKeyState[wParam] = true;
}

void InputClass::KeyUp(unsigned int wParam)
{
	mCacheKeyState[wParam] = false;
}

bool InputClass::IsKeyDown(unsigned int wParam)
{	
	return mKeyFrame[wParam] > 0 && mHasKey[wParam] && mKeyFrame[wParam] == Application->frame;
}

bool InputClass::IsKeyUp(unsigned int wParam)
{
	return mKeyFrame[wParam] > 0 && !mHasKey[wParam] && mKeyFrame[wParam] == Application->frame;
}

bool InputClass::HasKey(unsigned int wParam)
{
	return mKeyFrame[wParam] > 0 && mHasKey[wParam];
}

void InputClass::Frame()
{
	for (int i = 0; i < 256; ++i) 
	{
		if (mCacheKeyState[i] != mHasKey[i]) 
		{
			mHasKey[i] = mCacheKeyState[i];
			mKeyFrame[i] = Application->frame;
		}
	}
}
