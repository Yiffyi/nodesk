#pragma once
#include "framework.h"

EXTERN_C_BEGIN

size_t wcslenb(LPCWSTR wstr);
void DebugPrintf(LPCWSTR loc, LPCWSTR format, ...);

#define _STRINGIFY_DETAIL(x) #x
#define STRINGIFY(x) _STRINGIFY_DETAIL(x)
#define LINE_STRING STRINGIFY(__LINE__)
#define DEBUG(...) DebugPrintf(L"(" __FILE_NAME__ ":" LINE_STRING "): ",  __VA_ARGS__)
EXTERN_C_END