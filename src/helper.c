#include <Windows.h>
#include <stdio.h>

#define FORMAT_FLAGS ( FORMAT_MESSAGE_ALLOCATE_BUFFER |\
                       FORMAT_MESSAGE_FROM_SYSTEM     |\
                       FORMAT_MESSAGE_IGNORE_INSERTS  )

void WINAPI Log(HRESULT Result, PWSTR Function)
{
    if (Result == 0)
        return;

    PWSTR MsgBuffer = NULL;

    FormatMessageW(FORMAT_FLAGS, NULL, Result, 0,
                   (PWSTR)&MsgBuffer, 0, NULL);
    wprintf(L"%ls Error: %ls\n", Function, MsgBuffer);
    LocalFree(MsgBuffer);
}
