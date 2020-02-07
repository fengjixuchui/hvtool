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

void WINAPI HcsCloseComputeSystem(HCS_SYSTEM computeSystem);
void WINAPI HcsCloseOperation(HCS_OPERATION operation);
HCS_OPERATION WINAPI HcsCreateOperation(PVOID context, HCS_OPERATION_COMPLETION callback);

HRESULT WINAPI HcsEnumerateComputeSystems(PCWSTR query, HCS_OPERATION operation);
HRESULT WINAPI HcsOpenComputeSystem(PCWSTR id, DWORD requestedAccess, HCS_SYSTEM* computeSystem);
HRESULT WINAPI HcsPauseComputeSystem(HCS_SYSTEM computeSystem, HCS_OPERATION operation, PCWSTR options);
HRESULT WINAPI HcsResumeComputeSystem(HCS_SYSTEM computeSystem, HCS_OPERATION operation, PCWSTR options);
HRESULT WINAPI HcsShutDownComputeSystem(HCS_SYSTEM computeSystem, HCS_OPERATION operation, PCWSTR options);
HRESULT WINAPI HcsTerminateComputeSystem(HCS_SYSTEM computeSystem, HCS_OPERATION operation, PCWSTR options);
HRESULT WINAPI HcsWaitForOperationResult(HCS_OPERATION operation, DWORD timeoutMs, PWSTR* resultDocument);

#endif /* HCS_H */
