#ifndef HCN_H
#define HCN_H

typedef void *HCN_ENDPOINT, **PHCN_ENDPOINT;

HRESULT HcnCloseEndpoint(HCN_ENDPOINT Endpoint);
HRESULT HcnEnumerateEndpoints(PCWSTR Query, PWSTR* Endpoints, PWSTR* ErrorRecord);
HRESULT HcnOpenEndpoint(GUID* Id, PHCN_ENDPOINT Endpoint, PWSTR* ErrorRecord);
HRESULT HcnQueryEndpointProperties(HCN_ENDPOINT Endpoint, PCWSTR Query, PWSTR* Properties, PWSTR* ErrorRecord);

typedef void *HCN_NETWORK, **PHCN_NETWORK;

HRESULT HcnCloseNetwork(HCN_NETWORK Network);
HRESULT HcnEnumerateNetworks(PCWSTR Query, PWSTR* Networks, PWSTR* ErrorRecord);
HRESULT HcnOpenNetwork(GUID* Id, PHCN_NETWORK Network, PWSTR* ErrorRecord);
HRESULT HcnQueryNetworkProperties(HCN_NETWORK Network, PCWSTR Query, PWSTR* Properties, PWSTR* ErrorRecord);

#endif /* HCN_H */
