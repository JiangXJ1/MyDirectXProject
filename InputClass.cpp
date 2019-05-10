#include "InputClass.h"



InputClass::InputClass()
{
}

InputClass::InputClass(const InputClass & other)
{
}


InputClass::~InputClass()
{
}

void InputClass::Initialize()
{
	for (int i = 0; i < 256; ++i)
		mKey[i] = false;
}

void InputClass::KeyDown(unsigned int wParam)
{
	mKey[wParam] = true;
}

void InputClass::KeyUp(unsigned int wParam)
{
	mKey[wParam] = false;
}

bool InputClass::IsKeyDown(unsigned int wParam)
{	
	return mKey[wParam];
}
