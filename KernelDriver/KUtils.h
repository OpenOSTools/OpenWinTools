#pragma once
#include <ntifs.h>



#ifdef DBG
#define SUCCESS(Status) CheckNTStatus((Status))
#else
#define SUCCESS(Status) (NT_SUCCESS(Status))
#endif // DBG



#define WARN_ON(X) if ((X)) {KdBreakPoint();}
#define SIZE_FIT(A,B,C,D) (((SIZE_T)A + (SIZE_T)B) <= ((SIZE_T)C + (SIZE_T)D))

typedef enum _SYSTEM_INFORMATION_CLASS {
	SystemBasicInformation = 0,
	SystemPerformanceInformation = 2,
	SystemTimeOfDayInformation = 3,
	SystemProcessInformation = 5,
	SystemProcessorPerformanceInformation = 8,
	SystemModuleInformation = 11,
	SystemInterruptInformation = 23,
	SystemExceptionInformation = 33,
	SystemRegistryQuotaInformation = 37,
	SystemLookasideInformation = 45
} SYSTEM_INFORMATION_CLASS;

typedef struct _SYSTEM_MODULE_INFORMATION_ENTRY
{
	PVOID Section;
	PVOID MappedBase;
	PVOID Base;
	ULONG Size;
	ULONG Flags;
	USHORT Index;
	USHORT NameLength;
	USHORT LoadCount;
	USHORT ModuleNameOffset;
	char ImageName[256];
} SYSTEM_MODULE_INFORMATION_ENTRY, * PSYSTEM_MODULE_INFORMATION_ENTRY;

typedef struct _SYSTEM_MODULE_INFORMATION
{
	ULONG Count;
	SYSTEM_MODULE_INFORMATION_ENTRY Module[1];
} SYSTEM_MODULE_INFORMATION, * PSYSTEM_MODULE_INFORMATION;

extern "C"
{
#define MMDBG_COPY_WRITE            0x00000001
#define MMDBG_COPY_PHYSICAL         0x00000002
#define MMDBG_COPY_UNSAFE           0x00000004
#define MMDBG_COPY_CACHED           0x00000008
#define MMDBG_COPY_UNCACHED         0x00000010
#define MMDBG_COPY_WRITE_COMBINED   0x00000020

#define MMDBG_COPY_MAX_SIZE 8

    
    typedef NTSTATUS
    (*_KdpCopyMemoryChunks)(
        ULONG64 Address,
        PVOID Buffer,
        ULONG TotalSize,
        ULONG ChunkSize,
        ULONG Flags,
        SIZE_T* ActualSize OPTIONAL
        );

	NTSYSCALLAPI
	NTSTATUS
		NTAPI
		ZwQuerySystemInformation(
			SYSTEM_INFORMATION_CLASS SystemInformationClass,
			PVOID SystemInformation,
			ULONG SystemInformationLength,
			ULONG* ReturnLength);

	NTSYSCALLAPI
		NTSTATUS
		NTAPI
		NtQueryInformationProcess(
			__in HANDLE ProcessHandle,
			__in PROCESSINFOCLASS ProcessInformationClass,
			__out_bcount(ProcessInformationLength) PVOID ProcessInformation,
			__in ULONG ProcessInformationLength,
			__out_opt PULONG ReturnLength
		);

	NTKERNELAPI
		CHAR*
		PsGetProcessImageFileName(
			__in PEPROCESS Process
		);

	NTKERNELAPI
		HANDLE
		PsGetProcessInheritedFromUniqueProcessId(
			__in PEPROCESS Process
		);
}


BOOLEAN CheckNTStatus(NTSTATUS Status);

ULONG64 KTime_Get();

NTSTATUS KMem_Read(void* Src, SIZE_T Len, void* Dst, SIZE_T & Copied);
