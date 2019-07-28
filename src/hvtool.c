#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <stdio.h>
#include "hcn.h"
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
        Log(hRes, L"HcsOpenComputeSystem");

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

HRESULT WINAPI ListEndpoints(void)
{
    HRESULT hRes;
    PWSTR Endpoints = NULL, Properties = NULL;
    wchar_t IdString[MAX_PATH];
    GUID Id;
    HCN_ENDPOINT hcnEndpoint = NULL;

    hRes = HcnEnumerateEndpoints(NULL, &Endpoints, NULL);
    wprintf(L"%ls\n", Endpoints);

    wprintf(L"Enter any one GUID (with braces): ");
    memset(IdString, 0, sizeof IdString);
    wscanf(L"%ls", IdString);
    hRes = CLSIDFromString(IdString, &Id);
    Log(hRes, L"CLSIDFromString");

    if (!hRes)
    {
        hRes = HcnOpenEndpoint(&Id, &hcnEndpoint, NULL);
        hRes = HcnQueryEndpointProperties(hcnEndpoint, NULL, &Properties, NULL);
        wprintf(L"%ls\n", Properties);
    }

    if (Properties)
        CoTaskMemFree(Properties);
    if (hcnEndpoint)
        HcnCloseEndpoint(hcnEndpoint);
    return hRes;
}

HRESULT WINAPI ListNetworks(void)
{
    HRESULT hRes;
    PWSTR Networks = NULL, Properties = NULL;
    wchar_t IdString[MAX_PATH];
    GUID Id;
    HCN_NETWORK hcnNetwork = NULL;

    hRes = HcnEnumerateNetworks(NULL, &Networks, NULL);
    wprintf(L"%ls\n", Networks);

    wprintf(L"Enter any one GUID (with braces): ");
    memset(IdString, 0, sizeof IdString);
    wscanf(L"%ls", IdString);
    hRes = CLSIDFromString(IdString, &Id);
    Log(hRes, L"CLSIDFromString");

    if (!hRes)
    {
        hRes = HcnOpenNetwork(&Id, &hcnNetwork, NULL);
        hRes = HcnQueryNetworkProperties(hcnNetwork, NULL, &Properties, NULL);
        wprintf(L"%ls\n", Properties);
    }

    if (Properties)
        CoTaskMemFree(Properties);
    if (hcnNetwork)
        HcnCloseNetwork(hcnNetwork);
    return hRes;
}
