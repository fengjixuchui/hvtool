#ifndef HVTOOL_H
#define HVTOOL_H

HRESULT WINAPI KillContainer(PWSTR VmId);
HRESULT WINAPI ListContainers(void);
HRESULT WINAPI ListEndpoints(void);
HRESULT WINAPI ListNetworks(void);

#endif /* HVTOOL_H */
