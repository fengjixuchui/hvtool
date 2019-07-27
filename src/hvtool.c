#include <Windows.h>
#include <stdio.h>
#include "hcs.h"
#include "helper.h"

HRESULT WINAPI KillContainer(PWSTR VmId)
{
    HRESULT hRes;
    PWSTR result = NULL;
    HCS_OPERATION operation = NULL;
    HCS_SYSTEM computeSystem = NULL;

    operation = HcsCreateOperation(NULL, NULL);
    hRes = HcsOpenComputeSystem(VmId, DEFAULT_REQUESTED_ACCESS, &computeSystem);
    if (!hRes)
    {
        HcsTerminateComputeSystem(computeSystem, operation, NULL);
        hRes = HcsWaitForOperationResult(operation, INFINITE, &result);
    }
    else
        Log(hRes, L"HcsTerminateComputeSystem");

    if (result)
        CoTaskMemFree(result);
    if (operation)
        HcsCloseOperation(operation);
    if (computeSystem)
        HcsCloseComputeSystem(computeSystem);
    return hRes;
}

HRESULT WINAPI ListContainers(void)
{
    HRESULT hRes;
    HCS_OPERATION operation = NULL;
    PWSTR result = NULL;

    operation = HcsCreateOperation(NULL, NULL);
    hRes = HcsEnumerateComputeSystems(NULL, operation);
    hRes = HcsWaitForOperationResult(operation, INFINITE, &result);

    if (!hRes)
        wprintf(L"%ls\n", result);

    if (result)
        CoTaskMemFree(result);
    if (operation)
        HcsCloseOperation(operation);
    return hRes;
}
