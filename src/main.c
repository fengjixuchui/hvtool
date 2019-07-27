#include <Windows.h>
#include <stdio.h>
#include "hvtool.h"

int WINAPI main(void)
{
    int wargc;
    PWSTR* wargv = CommandLineToArgvW(GetCommandLineW(), &wargc);

    if (wargc < 2)
    {
        wprintf(L"No option provided.\n");
        return 1;
    }

    if (wargc == 2)
    {
        if (!wcscmp(wargv[1], L"list"))
            ListContainers();
    }

    if (wargc == 3)
    {
        if (!wcscmp(wargv[1], L"kill"))
            KillContainer(wargv[2]);
    }

    return 0;
}
