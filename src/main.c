#include <Windows.h>
#include <stdio.h>
#include "hvtool.h"
#include "helper.h"

int WINAPI main(void)
{
    int wargc;
    PWSTR* wargv = CommandLineToArgvW(GetCommandLineW(), &wargc);

    if (wargc < 2)
    {
        wprintf(L"Try '%s help' for more information.\n", wargv[0]);
        return 1;
    }

    if (wargc == 2)
    {
        if (!wcscmp(wargv[1], L"endp"))
            ListEndpoints();

        if (!wcscmp(wargv[1], L"help"))
            Usage(wargv[0]);

        if (!wcscmp(wargv[1], L"list"))
            ListContainers();

        if (!wcscmp(wargv[1], L"net"))
            ListNetworks();

        if (!wcscmp(wargv[1], L"wsl"))
            GetWslIP(FALSE);
    }

    if (wargc == 3)
    {
        if (!wcscmp(wargv[1], L"kill"))
            KillContainer(wargv[2]);
    }

    return 0;
}
