#pragma once
#include "framework.h"

EXTERN_C_BEGIN

BOOL SimpleCreateProcess(LPCWSTR lpApp, LPWSTR lpCmdLine);
BOOL InjectDllToProcess(LPCWSTR pszDllPath, LPPROCESS_INFORMATION lpProcessInformation);

EXTERN_C_END
