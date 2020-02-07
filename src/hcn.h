/*
 * Taken from computenetwork.h in Windows SDK
 * Exported DLLs:
 * computenetwork.dll aka. ext-ms-win-hyperv-computenetwork-l1-1-0.dll
 */

#ifndef HCN_H
#define HCN_H

typedef void *HCN_ENDPOINT, **PHCN_ENDPOINT;

HRESULT WINAPI HcnCloseEndpoint(HCN_ENDPOINT Endpoint);
HRESULT WINAPI HcnEnumerateEndpoints(PCWSTR Query, PWSTR* Endpoints, PWSTR* ErrorRecord);
HRESULT WINAPI HcnOpenEndpoint(GUID* Id, PHCN_ENDPOINT Endpoint, PWSTR* ErrorRecord);
HRESULT WINAPI HcnQueryEndpointProperties(HCN_ENDPOINT Endpoint, PCWSTR Query, PWSTR* Properties, PWSTR* ErrorRecord);

typedef void *HCN_NETWORK, **PHCN_NETWORK;

HRESULT WINAPI HcnCloseNetwork(HCN_NETWORK Network);
HRESULT WINAPI HcnEnumerateNetworks(PCWSTR Query, PWSTR* Networks, PWSTR* ErrorRecord);
HRESULT WINAPI HcnOpenNetwork(GUID* Id, PHCN_NETWORK Network, PWSTR* ErrorRecord);
HRESULT WINAPI HcnQueryNetworkProperties(HCN_NETWORK Network, PCWSTR Query, PWSTR* Properties, PWSTR* ErrorRecord);

#endif /* HCN_H */
