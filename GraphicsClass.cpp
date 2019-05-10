#include "GraphicsClass.h"



GraphicsClass::GraphicsClass()
{
}


GraphicsClass::GraphicsClass(const GraphicsClass& other)
{

}

GraphicsClass::~GraphicsClass()
{
}

bool GraphicsClass::Initialize(int ScreenWidth, int ScreenHeight, HWND hwnd) {
	return true;
}

void GraphicsClass::ShutDown()
{

}

bool GraphicsClass::Frame()
{
	return true;
}

bool GraphicsClass::Render()
{
	return false;
}