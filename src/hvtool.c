#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <stdio.h>
#include "hcn.h"
#include "hcs.h"
#include "helper.h"
#include "jsmn.h"

static int jsoneq(const wchar_t* json, jsmntok_t* tok, const wchar_t* s)
{
    if (tok->type == JSMN_STRING && (int)wcslen(s) == tok->end - tok->start &&
        wcsncmp(json + tok->start, s, tok->end - tok->start) == 0)
    {
        return 0;
    }
    return -1;
}

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

/* Enable verbose mode to print whole JSON output */
HRESULT WINAPI GetWslIP(BOOLEAN Verbose)
{
    HRESULT hRes;
    PWSTR Properties = NULL;
    HCN_NETWORK hcnNetwork = NULL;

    GUID wslNetworkId = {
        0xB95D0C5E,
        0x57D4,
        0x412B,
        { 0xB5, 0x71, 0x18, 0xA8, 0x1A, 0x16, 0xE0, 0x05 } };

    hRes = HcnOpenNetwork(&wslNetworkId, &hcnNetwork, NULL);
    hRes = HcnQueryNetworkProperties(hcnNetwork, NULL, &Properties, NULL);
    if (Verbose)
    {
        wprintf(L"%ls\n", Properties);
        goto Cleanup;
    }

    int ret;
    jsmn_parser parser;
    jsmntok_t tok[512];

    jsmn_init(&parser);
    ret = jsmn_parse(&parser, Properties, wcslen(Properties), tok, ARRAYSIZE(tok));
    if (ret < 0) 
    {
        wprintf(L"Failed to parse JSON: %d\n", ret);
        return 1;
    }

    for (int i = 1; i < ret; i++)
    {
        if (jsoneq(Properties, &tok[i], L"GatewayAddress") == 0)
        {
            wprintf(L"%.*s\n", tok[i + 1].end - tok[i + 1].start,
                    Properties + tok[i + 1].start);
            break;
        }
    }

Cleanup:
    if (Properties)
        CoTaskMemFree(Properties);
    if (hcnNetwork)
        HcnCloseNetwork(hcnNetwork);
    return hRes;
}
