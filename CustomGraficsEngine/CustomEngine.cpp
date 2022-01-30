#include "CustomEngine.h"
#include <Windows.h>

#include "CE_Core.h"
/// <summary>
/// Ist die "Main" für Desktopanwendungen
/// </summary>
/// <param name="hInstance"></param>
/// <param name="hPrevInstance"></param>
/// <param name="lpCmdLine"></param>
/// <param name="nShowCmd"></param>
/// <returns></returns>
int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nShowCmd) 
{
	if (CORE->Init(hInstance, hPrevInstance, lpCmdLine, nShowCmd) == 0) {
		CORE->Run();
		CORE->Finish();
	}
	return 0;
}