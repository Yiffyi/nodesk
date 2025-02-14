#include <framework.h>
#include <stdio.h>

#include "NoDesk/strings.h"

int APIENTRY WinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	WCHAR szSelfPath[MAX_PATH];
	while(TRUE) {
		GetModuleFileNameW(NULL, szSelfPath, MAX_PATH);
		DEBUG(L"[AnyDesk] I'm at %s.", szSelfPath);
		Sleep(1000);
	}
}