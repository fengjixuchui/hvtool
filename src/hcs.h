/*
 * Taken from computecore.h and computedefs.h in Windows SDK
 * Exported DLLs:
 * vmcompute.dll aka. ext-ms-win-hyperv-compute-l1-1-0.dll
 * computecore.dll aka. ext-ms-win-hyperv-compute-l1-2-0.dll
 */

#ifndef HCS_H
#define HCS_H

#define DEFAULT_REQUESTED_ACCESS 0x10000000u

typedef void *HCS_OPERATION, *HCS_SYSTEM;
typedef void (*HCS_OPERATION_COMPLETION)(HCS_OPERATION operation, PVOID context);

void HcsCloseComputeSystem(HCS_SYSTEM computeSystem);
void HcsCloseOperation(HCS_OPERATION operation);
HCS_OPERATION HcsCreateOperation(PVOID context, HCS_OPERATION_COMPLETION callback);

HRESULT HcsEnumerateComputeSystems(PCWSTR query, HCS_OPERATION operation);
HRESULT HcsOpenComputeSystem(PCWSTR id, DWORD requestedAccess, HCS_SYSTEM* computeSystem);
HRESULT HcsTerminateComputeSystem(HCS_SYSTEM computeSystem, HCS_OPERATION operation, PCWSTR options);
HRESULT HcsWaitForOperationResult(HCS_OPERATION operation, DWORD timeoutMs, PWSTR* resultDocument);

#endif /* HCS_H */
