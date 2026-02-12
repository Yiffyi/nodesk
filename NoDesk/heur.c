#include "framework.h"

#include "NoDesk/strings.h"

static BOOL heur_sleep()
{
    LARGE_INTEGER freq, t0, t1;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&t0);
    Sleep(100);
    QueryPerformanceCounter(&t1);
    if ((double)(t1.QuadPart - t0.QuadPart) / freq.QuadPart * 1000.0 < 50.0)
    {
        DEBUG(L"[NoDeskRT] Heuristic sleep check failed.");
        return FALSE;
    }

    return TRUE;
}

void determine()
{
    if (!heur_sleep())
    {
        ExitProcess(ERROR_ACCESS_DENIED);
    }

    Sleep(10000);
}