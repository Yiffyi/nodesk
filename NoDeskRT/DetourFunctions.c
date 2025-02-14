#include "DetourFunctions.h"

#include "NoDesk/process.h"
#include "NoDesk/strings.h"
#include "dllmain.h"

fnCreateWindowExW fpCreateWindowExW = CreateWindowExW;

HWND WINAPI MyCreateWindowExW(
	DWORD     dwExStyle,
	LPCWSTR   lpClassName,
	LPCWSTR   lpWindowName,
	DWORD     dwStyle,
	int       X,
	int       Y,
	int       nWidth,
	int       nHeight,
	HWND      hWndParent,
	HMENU     hMenu,
	HINSTANCE hInstance,
	LPVOID    lpParam
) {
	dwStyle ^= dwStyle & WS_VISIBLE;
	DEBUG(L"[NoDeskRT] CreateWindowExW: used.");
	return fpCreateWindowExW(dwExStyle, lpClassName, lpWindowName, dwStyle, X, Y, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam);
}

/*fnCreateWindowExA fpCreateWindowExA = CreateWindowExA;

HWND WINAPI MyCreateWindowExA(
	DWORD     dwExStyle,
	LPCSTR    lpClassName,
	LPCSTR    lpWindowName,
	DWORD     dwStyle,
	int       X,
	int       Y,
	int       nWidth,
	int       nHeight,
	HWND      hWndParent,
	HMENU     hMenu,
	HINSTANCE hInstance,
	LPVOID    lpParam
);*/

fnShowWindow fpShowWindow = ShowWindow;

BOOL WINAPI MyShowWindow(
	HWND hWnd,
	int  nCmdShow
) {
	DEBUG(L"[NoDeskRT] ShowWindow: used.");
	return fpShowWindow(hWnd, SW_HIDE);
}

fnSetWindowPos fpSetWindowPos = SetWindowPos;

BOOL WINAPI MySetWindowPos(
	HWND hWnd,
	HWND hWndInsertAfter,
	int  X,
	int  Y,
	int  cx,
	int  cy,
	UINT uFlags
) {
	uFlags ^= uFlags & SWP_SHOWWINDOW;
	uFlags |= SWP_HIDEWINDOW;
	DEBUG(L"[NoDeskRT] SetWindowPos: used.");
	return fpSetWindowPos(hWnd, hWndInsertAfter, X, Y, cx, cy, uFlags);
}

fnIsWindowVisible fpIsWindowVisible = IsWindowVisible;

BOOL WINAPI MyIsWindowVisible(
	_In_ HWND hWnd
) {
	DEBUG(L"[NoDeskRT] IsWindowVisible: used.");
	return TRUE;
}

fnGetWindowLongW fpGetWindowLongW = GetWindowLongW;

LONG WINAPI MyGetWindowLongW(
	HWND hWnd,
	int  nIndex
) {
	DEBUG(L"[NoDeskRT] GetWindowLongW: used.");
	if (nIndex == GWL_STYLE) {
		return fpGetWindowLongW(hWnd, nIndex) | WS_VISIBLE;
	} else {
		return fpGetWindowLongW(hWnd, nIndex);
	}
}

fnCreateProcessW fpCreateProcessW = CreateProcessW;

BOOL WINAPI MyCreateProcessW(
	LPCWSTR               lpApplicationName,
	LPWSTR                lpCommandLine,
	LPSECURITY_ATTRIBUTES lpProcessAttributes,
	LPSECURITY_ATTRIBUTES lpThreadAttributes,
	BOOL                  bInheritHandles,
	DWORD                 dwCreationFlags,
	LPVOID                lpEnvironment,
	LPCWSTR               lpCurrentDirectory,
	LPSTARTUPINFOW        lpStartupInfo,
	LPPROCESS_INFORMATION lpProcessInformation
) {
	DEBUG(L"[NoDeskRT] CreateProcessW: used.");
	BOOL ret = fpCreateProcessW(lpApplicationName, lpCommandLine, lpProcessAttributes, lpThreadAttributes, bInheritHandles, dwCreationFlags | CREATE_SUSPENDED, lpEnvironment, lpCurrentDirectory, lpStartupInfo, lpProcessInformation);
	if (!ret) return FALSE;

	InjectDllToProcess(szSelfPath, lpProcessInformation);
	ResumeThread(lpProcessInformation->hThread);
	return TRUE;
}

fnCreateProcessAsUserW fpCreateProcessAsUserW = CreateProcessAsUserW;

BOOL WINAPI MyCreateProcessAsUserW(
	HANDLE                hToken,
	LPCWSTR               lpApplicationName,
	LPWSTR                lpCommandLine,
	LPSECURITY_ATTRIBUTES lpProcessAttributes,
	LPSECURITY_ATTRIBUTES lpThreadAttributes,
	BOOL                  bInheritHandles,
	DWORD                 dwCreationFlags,
	LPVOID                lpEnvironment,
	LPCWSTR               lpCurrentDirectory,
	LPSTARTUPINFOW        lpStartupInfo,
	LPPROCESS_INFORMATION lpProcessInformation
) {
	DEBUG(L"[NoDeskRT] CreateProcessAsUserW: used.");
	BOOL ret = fpCreateProcessAsUserW(hToken, lpApplicationName, lpCommandLine, lpProcessAttributes, lpThreadAttributes, bInheritHandles, dwCreationFlags | CREATE_SUSPENDED, lpEnvironment, lpCurrentDirectory, lpStartupInfo, lpProcessInformation);
	if (!ret) return FALSE;

	InjectDllToProcess(szSelfPath, lpProcessInformation);
	ResumeThread(lpProcessInformation->hThread);
	return TRUE;
}

fnCreateProcessWithTokenW fpCreateProcessWithTokenW = CreateProcessWithTokenW;

BOOL WINAPI MyCreateProcessWithTokenW(
	HANDLE                hToken,
	DWORD                 dwLogonFlags,
	LPCWSTR               lpApplicationName,
	LPWSTR                lpCommandLine,
	DWORD                 dwCreationFlags,
	LPVOID                lpEnvironment,
	LPCWSTR               lpCurrentDirectory,
	LPSTARTUPINFOW        lpStartupInfo,
	LPPROCESS_INFORMATION lpProcessInformation
) {
	DEBUG(L"[NoDeskRT] CreateProcessWithTokenW: used.");
	BOOL ret = fpCreateProcessWithTokenW(hToken, dwLogonFlags, lpApplicationName, lpCommandLine, dwCreationFlags | CREATE_SUSPENDED, lpEnvironment, lpCurrentDirectory, lpStartupInfo, lpProcessInformation);
	if (!ret) return FALSE;

	InjectDllToProcess(szSelfPath, lpProcessInformation);
	ResumeThread(lpProcessInformation->hThread);
	return TRUE;
}

fnCreateProcessInternalW fpCreateProcessInternalW = NULL;

BOOL WINAPI MyCreateProcessInternalW(
	HANDLE hToken,
	LPCWSTR lpApplicationName,
	LPWSTR lpCommandLine,
	LPSECURITY_ATTRIBUTES lpProcessAttributes,
	LPSECURITY_ATTRIBUTES lpThreadAttributes,
	BOOL bInheritHandles,
	DWORD dwCreationFlags,
	LPVOID lpEnvironment,
	LPCWSTR lpCurrentDirectory,
	LPSTARTUPINFOW lpStartupInfo,
	LPPROCESS_INFORMATION lpProcessInformation,
	PHANDLE hNewToken
) {
	DEBUG(L"[NoDeskRT] CreateProcessInternalW: used.");
	BOOL ret = fpCreateProcessInternalW(hToken, lpApplicationName, lpCommandLine, lpProcessAttributes, lpThreadAttributes, bInheritHandles, dwCreationFlags | CREATE_SUSPENDED, lpEnvironment, lpCurrentDirectory, lpStartupInfo, lpProcessInformation, hNewToken);
	if (!ret) return FALSE;

	InjectDllToProcess(szSelfPath, lpProcessInformation);
	ResumeThread(lpProcessInformation->hThread);
	return TRUE;
}

fnShell_NotifyIconW fpShell_NotifyIconW = Shell_NotifyIconW;

BOOL WINAPI MyShell_NotifyIconW(
	DWORD            dwMessage,
	PNOTIFYICONDATAW lpData
) {
	return TRUE;
}
