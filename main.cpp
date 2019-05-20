
#include"SystemClass.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{


	//初始化和运行系统对象
	Application->Initialize();
	Application->Run();

	//关闭systemclass对象
	Application->Shutdown();
	delete Application;
	Application = NULL;
	return 0;
}