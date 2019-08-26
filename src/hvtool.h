#ifndef HVTOOL_H
#define HVTOOL_H

HRESULT WINAPI KillContainer(PWSTR VmId);
HRESULT WINAPI ListContainers(void);
HRESULT WINAPI ListEndpoints(void);
HRESULT WINAPI ListNetworks(void);
HRESULT WINAPI GetWslIP(BOOLEAN Verbose);

#endif /* HVTOOL_H */
