#pragma once
#include "framework.h"

BOOL SimpleCreateProcess(LPCWSTR lpApp, LPWSTR lpCmdLine);
BOOL InjectDllToProcess(LPCWSTR pszDllPath, LPPROCESS_INFORMATION lpProcessInformation);
