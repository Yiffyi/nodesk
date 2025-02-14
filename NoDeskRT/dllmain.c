#include "dllmain.h"

#include <Minhook.h>

#include "NoDesk/strings.h"
#include "DetourFunctions.h"

WCHAR szSelfPath[MAX_PATH];
WCHAR szExePath[MAX_PATH];

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    if (ul_reason_for_call == DLL_THREAD_ATTACH || ul_reason_for_call == DLL_THREAD_DETACH) return TRUE;

    if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
        DEBUG(L"[NoDeskRT] I'm in.");
        GetModuleFileNameW(hModule, szSelfPath, MAX_PATH);
        GetModuleFileNameW(NULL, szExePath, MAX_PATH);

        if (wcscmp(PathFindFileNameW(szExePath), L"dwm.exe") != 0) {
            DEBUG(szExePath);
            FreeLibraryAndExitThread(hModule, ERROR_ACCESS_DENIED);
            return FALSE;
        }

        if (MH_Initialize() != MH_OK)
        {
            DEBUG(L"[NoDeskRT] could not initialize MinHook");
            return FALSE;
        }

        // if (MH_CreateHook(&CreateProcessW, &MyCreateProcessW, 
        //     (LPVOID*)(&fpCreateProcessW)) != MH_OK)
        // {
        //     DEBUG(L"[NoDeskRT] could not create hook for CreateProcessW");
        //     return FALSE;
        // }

        // if (MH_CreateHook(&CreateProcessAsUserW, &MyCreateProcessAsUserW, 
        //     (LPVOID*)(&fpCreateProcessAsUserW)) != MH_OK)
        // {
        //     DEBUG(L"[NoDeskRT] could not create hook for CreateProcessAsUserW");
        //     return FALSE;
        // }

        // if (MH_CreateHook(&CreateProcessWithTokenW, &MyCreateProcessWithTokenW, 
        //     (LPVOID*)(&fpCreateProcessWithTokenW)) != MH_OK)
        // {
        //     return FALSE;
        // }

        if (GetModuleHandleW(L"kernelbase.dll") != NULL) {
            if (MH_CreateHookApi(L"kernelbase.dll", "CreateProcessInternalW", &MyCreateProcessInternalW,
                (LPVOID*)(&fpCreateProcessInternalW)) != MH_OK)
            {
                DEBUG(L"[NoDeskRT] could not create hook for CreateProcessInternalW");
                return FALSE;
            }

        } else {
            if (MH_CreateHookApi(L"kernel32.dll", "CreateProcessInternalW", &MyCreateProcessInternalW,
                (LPVOID*)(&fpCreateProcessInternalW)) != MH_OK)
            {
                DEBUG(L"[NoDeskRT] could not create hook for CreateProcessInternalW");
                return FALSE;
            }
        }


        if (MH_CreateHook(&CreateWindowExW, &MyCreateWindowExW, 
            (LPVOID*)(&fpCreateWindowExW)) != MH_OK)
        {
            return FALSE;
        }

        if (MH_CreateHook(&ShowWindow, &MyShowWindow, 
            (LPVOID*)(&fpShowWindow)) != MH_OK)
        {
            return FALSE;
        }

        if (MH_CreateHook(&SetWindowPos, &MySetWindowPos, 
            (LPVOID*)(&fpSetWindowPos)) != MH_OK)
        {
            return FALSE;
        }

        if (MH_CreateHook(&IsWindowVisible, MyIsWindowVisible, (LPVOID*)(&fpIsWindowVisible)) != MH_OK) {
            return FALSE;
        }

        if (MH_CreateHook(&GetWindowLongW, MyGetWindowLongW, (LPVOID*)(&fpGetWindowLongW)) != MH_OK) {
            return FALSE;
        }

        if (MH_CreateHook(&Shell_NotifyIconW, &MyShell_NotifyIconW, 
            (LPVOID*)(&fpShell_NotifyIconW)) != MH_OK)
        {
            return FALSE;
        }

        if (MH_EnableHook(MH_ALL_HOOKS) != MH_OK)
        {
            return FALSE;
        }
    }

    if (ul_reason_for_call == DLL_PROCESS_DETACH) {
        DEBUG(L"[NoDeskRT] I'm out.");
        if (MH_DisableHook(MH_ALL_HOOKS) != MH_OK)
        {
            return FALSE;
        }

        // Uninitialize MinHook.
        if (MH_Uninitialize() != MH_OK)
        {
            return FALSE;
        }
    }

    return TRUE;
}

