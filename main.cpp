
#include"SystemClass.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{


	//��ʼ��������ϵͳ����
	Application->Initialize();
	Application->Run();

	//�ر�systemclass����
	Application->Shutdown();
	delete Application;
	Application = NULL;
	return 0;
}