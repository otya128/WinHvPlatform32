#include "Load64bitDll.h"
#pragma comment(lib, "Load64bitDll.lib")
#define WHV_PARTITION_HANDLE WHV_PARTITION_HANDLE32 /* hack! */
#include <WinHvPlatformDefs.h>
#undef WHV_PARTITION_HANDLE
typedef UINT64 WHV_PARTITION_HANDLE;
#include <WinHvPlatform.h>

UINT64 pWHvGetCapability;
UINT64 pWHvCreatePartition; //impl
UINT64 pWHvSetupPartition; //impl
UINT64 pWHvDeletePartition;
UINT64 pWHvGetPartitionProperty;
UINT64 pWHvSetPartitionProperty; //impl
UINT64 pWHvMapGpaRange; //impl
UINT64 pWHvUnmapGpaRange; //impl
UINT64 pWHvTranslateGva;
UINT64 pWHvCreateVirtualProcessor; //impl
UINT64 pWHvDeleteVirtualProcessor;
UINT64 pWHvRunVirtualProcessor; //impl
UINT64 pWHvCancelRunVirtualProcessor;
UINT64 pWHvGetVirtualProcessorRegisters; //impl
UINT64 pWHvSetVirtualProcessorRegisters; //impl
UINT64 pWHvGetVirtualProcessorInterruptControllerState;
UINT64 pWHvSetVirtualProcessorInterruptControllerState;
UINT64 pWHvRequestInterrupt;
UINT64 pWHvGetVirtualProcessorXsaveState;
UINT64 pWHvSetVirtualProcessorXsaveState;
UINT64 pWHvQueryGpaRangeDirtyBitmap;
UINT64 pWHvGetPartitionCounters;
UINT64 pWHvGetVirtualProcessorCounters;

EXTERN_C_START

void load()
{
    auto hmod = LoadLibraryExW64(L"WinHvPlatform.dll", NULL, LOAD_LIBRARY_SEARCH_SYSTEM32);
    pWHvGetCapability = GetProcAddress64(hmod, "WHvGetCapability");
    pWHvCreatePartition = GetProcAddress64(hmod, "WHvCreatePartition");
    pWHvSetupPartition = GetProcAddress64(hmod, "WHvSetupPartition");
    pWHvDeletePartition = GetProcAddress64(hmod, "WHvDeletePartition");
    pWHvGetPartitionProperty = GetProcAddress64(hmod, "WHvGetPartitionProperty");
    pWHvSetPartitionProperty = GetProcAddress64(hmod, "WHvSetPartitionProperty");
    pWHvMapGpaRange = GetProcAddress64(hmod, "WHvMapGpaRange");
    pWHvUnmapGpaRange = GetProcAddress64(hmod, "WHvUnmapGpaRange");
    pWHvTranslateGva = GetProcAddress64(hmod, "WHvTranslateGva");
    pWHvCreateVirtualProcessor = GetProcAddress64(hmod, "WHvCreateVirtualProcessor");
    pWHvDeleteVirtualProcessor = GetProcAddress64(hmod, "WHvDeleteVirtualProcessor");
    pWHvRunVirtualProcessor = GetProcAddress64(hmod, "WHvRunVirtualProcessor");
    pWHvCancelRunVirtualProcessor = GetProcAddress64(hmod, "WHvCancelRunVirtualProcessor");
    pWHvGetVirtualProcessorRegisters = GetProcAddress64(hmod, "WHvGetVirtualProcessorRegisters");
    pWHvSetVirtualProcessorRegisters = GetProcAddress64(hmod, "WHvSetVirtualProcessorRegisters");
    pWHvGetVirtualProcessorInterruptControllerState = GetProcAddress64(hmod, "WHvGetVirtualProcessorInterruptControllerState");
    pWHvSetVirtualProcessorInterruptControllerState = GetProcAddress64(hmod, "WHvSetVirtualProcessorInterruptControllerState");
    pWHvRequestInterrupt = GetProcAddress64(hmod, "WHvRequestInterrupt");
    pWHvGetVirtualProcessorXsaveState = GetProcAddress64(hmod, "WHvGetVirtualProcessorXsaveState");
    pWHvSetVirtualProcessorXsaveState = GetProcAddress64(hmod, "WHvSetVirtualProcessorXsaveState");
    pWHvQueryGpaRangeDirtyBitmap = GetProcAddress64(hmod, "WHvQueryGpaRangeDirtyBitmap");
    pWHvGetPartitionCounters = GetProcAddress64(hmod, "WHvGetPartitionCounters");
    pWHvGetVirtualProcessorCounters = GetProcAddress64(hmod, "WHvGetVirtualProcessorCounters");
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        load();
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
        break;
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

HRESULT WINAPI WHvCreatePartition(
    _Out_ WHV_PARTITION_HANDLE* Partition
)
{
    return Call64<HRESULT>(pWHvCreatePartition, Partition);
}

HRESULT WINAPI WHvSetupPartition(WHV_PARTITION_HANDLE Partition)
{
    return Call64<HRESULT>(pWHvSetupPartition, Partition);
}

HRESULT WINAPI WHvMapGpaRange(
    _In_ WHV_PARTITION_HANDLE Partition,
    _In_ VOID* SourceAddress,
    _In_ WHV_GUEST_PHYSICAL_ADDRESS GuestAddress,
    _In_ UINT64 SizeInBytes,
    _In_ WHV_MAP_GPA_RANGE_FLAGS Flags
)
{
    return Call64<HRESULT>(pWHvMapGpaRange, Partition, SourceAddress, GuestAddress, SizeInBytes, Flags);
}

HRESULT WINAPI WHvUnmapGpaRange(
    _In_ WHV_PARTITION_HANDLE Partition,
    _In_ WHV_GUEST_PHYSICAL_ADDRESS GuestAddress,
    _In_ UINT64 SizeInBytes
)
{
    return Call64<HRESULT>(pWHvUnmapGpaRange, Partition, GuestAddress, SizeInBytes);
}
HRESULT
WINAPI
WHvCreateVirtualProcessor(
    _In_ WHV_PARTITION_HANDLE Partition,
    _In_ UINT32 VpIndex,
    _In_ UINT32 Flags
)
{
    return Call64<HRESULT>(pWHvCreateVirtualProcessor, Partition, VpIndex, Flags);
}

HRESULT
WINAPI
WHvGetVirtualProcessorRegisters(
    _In_ WHV_PARTITION_HANDLE Partition,
    _In_ UINT32 VpIndex,
    _In_reads_(RegisterCount) const WHV_REGISTER_NAME* RegisterNames,
    _In_ UINT32 RegisterCount,
    _Out_writes_(RegisterCount) WHV_REGISTER_VALUE* RegisterValues
)
{
    return Call64<HRESULT>(pWHvGetVirtualProcessorRegisters, Partition, VpIndex, RegisterNames, RegisterCount, RegisterValues);
}

HRESULT
WINAPI
WHvSetVirtualProcessorRegisters(
    _In_ WHV_PARTITION_HANDLE Partition,
    _In_ UINT32 VpIndex,
    _In_reads_(RegisterCount) const WHV_REGISTER_NAME* RegisterNames,
    _In_ UINT32 RegisterCount,
    _In_reads_(RegisterCount) const WHV_REGISTER_VALUE* RegisterValues
)
{
    return Call64<HRESULT>(pWHvSetVirtualProcessorRegisters, Partition, VpIndex, RegisterNames, RegisterCount, RegisterValues);
}
HRESULT
WINAPI
WHvSetPartitionProperty(
    _In_ WHV_PARTITION_HANDLE Partition,
    _In_ WHV_PARTITION_PROPERTY_CODE PropertyCode,
    _In_reads_bytes_(PropertyBufferSizeInBytes) const VOID* PropertyBuffer,
    _In_ UINT32 PropertyBufferSizeInBytes
)
{
    return Call64<HRESULT>(pWHvSetPartitionProperty, Partition, PropertyCode, PropertyBuffer, PropertyBufferSizeInBytes);
}
HRESULT
WINAPI
WHvRunVirtualProcessor(
    _In_ WHV_PARTITION_HANDLE Partition,
    _In_ UINT32 VpIndex,
    _Out_writes_bytes_(ExitContextSizeInBytes) VOID* ExitContext,
    _In_ UINT32 ExitContextSizeInBytes
)
{
    return Call64<HRESULT>(pWHvRunVirtualProcessor, Partition, VpIndex, ExitContext, ExitContextSizeInBytes);
}

EXTERN_C_END
