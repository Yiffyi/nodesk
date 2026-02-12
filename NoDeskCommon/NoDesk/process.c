#include "process.h"
#include "strings.h"

BOOL SimpleCreateProcess(LPCWSTR lpApp, LPWSTR lpCmdLine)
{
	STARTUPINFOW si = { 0 };
	PROCESS_INFORMATION pi = { 0 };
	si.cb = sizeof(si);
	si.dwFlags = STARTF_USESHOWWINDOW;
	si.wShowWindow = SW_NORMAL;

	BOOL ret = CreateProcessW(lpApp, lpCmdLine, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
	return ret;
}

// static BOOL inject_remote_thread(HANDLE hProcess, LPVOID pParam)
// {
// 	HANDLE hThread = CreateRemoteThread(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)LoadLibraryW, pParam, CREATE_SUSPENDED, NULL);
	
// 	if (hThread)
// 	{
// 		ResumeThread(hThread);
// 		WaitForSingleObject(hThread, INFINITE);
// 		CloseHandle(hThread);
// 		return TRUE;
// 	}
// 	else {
// 		DEBUG(L"[NoDesk]: CreateRemoteThread failed with %lu", GetLastError());
// 		TerminateProcess(hProcess, 0);
// 		return FALSE;
// 	}
// }

static BOOL inject_apc(HANDLE hProcess, HANDLE hThread, LPVOID pParam)
{
	if (QueueUserAPC((PAPCFUNC)LoadLibraryW, hThread, (ULONG_PTR)pParam))
	{
		return TRUE;
	}
	else
	{
		DEBUG(L"[NoDesk]: QueueUserAPC failed with %lu", GetLastError());
		TerminateProcess(hProcess, 0);
		return FALSE;
	}
}

BOOL InjectDllToProcess(LPCWSTR pszDllPath, LPPROCESS_INFORMATION lpProcessInformation) {
	LPVOID Param = VirtualAllocEx(lpProcessInformation->hProcess, NULL, MAX_PATH, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	if (!Param) {
		return FALSE;
	}

	WriteProcessMemory(lpProcessInformation->hProcess, Param, (LPVOID)pszDllPath, wcslenb(pszDllPath), NULL);

	// return inject_remote_thread(lpProcessInformation->hProcess, Param);
	return inject_apc(lpProcessInformation->hProcess, lpProcessInformation->hThread, Param);

	// return FALSE;
}
