#pragma once
#include <ntifs.h>

#define __FILENAME__ (strrchr("\\"__FILE__, '\\') + 1)

extern DRIVER_OBJECT* g_DrvObj;

#define KLogPrint(FMT, ...) DbgPrint("[KLog]"FMT"\n", __VA_ARGS__)

#ifdef  DBG
#define KDLogPrint(FMT, ...) DbgPrint("[KLog]"FMT"\n", __VA_ARGS__)
#else
#define KDLogPrint(FMT, ...)
#endif

#ifdef DBG

/*
 * Print file/func/line, then break to debugger(if kernel debug enabled);
*/
#define BreakPoint()  (KDLogPrint("KDBreak at %s:%s:%d", __FILENAME__, __FUNCTION__, __LINE__), (KD_DEBUGGER_ENABLED) ? DbgBreakPoint() : 0)
#else
#define BreakPoint()  0
#endif

/*
 * In debug build:
 *      If the value of param (X) equal false, print file/function/lines, then try break to debugger;
 * in release build:
 *      do nothing;
 */
#define KASSRT(X)  {if (!(X)) { KDLogPrint("KASSRT:( "#X" ) at %s:%s:%d", __FILENAME__, __FUNCTION__, __LINE__); BreakPoint();}}

/*
 * If the value of param (X) equal true, print file name/function name/lines, then try break to debugger; 
 * Works in both debug and release build;
 *
 * Do not use it in closesource or commercial products,
 * because it will "leak" source file name, function name, and even variable name,
 * hackers, crackers, or reversers will be happy to see these names.
 */
#define WARN_ON(X) {if ((X)) { KLogPrint("WARN_ON:( "#X" ) at %s:%s:%d", __FILENAME__, __FUNCTION__, __LINE__); BreakPoint();}}

/*
  In release build:
        'if(OK(X))' is totally same as 'if(X)';
  In debug build:
        the final effect is same as 'if(X)', but it will try break to debugger when
        macro param equal false.
 */
#define OK(X) ((X) ? TRUE : (BreakPoint(),FALSE))

/*
 * Same as NT_SUCCESS(),
 * except in debug build, it will try break to debugger when status test failed.
 */
#define STATUS_OK(X) (NT_SUCCESS(X) ? TRUE : (BreakPoint(), FALSE))


#define SIZE_FIT(A,B,C,D) (((SIZE_T)A + (SIZE_T)B) <= ((SIZE_T)C + (SIZE_T)D) && ((SIZE_T)A + (SIZE_T)B) >= (SIZE_T)C)

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


ULONG64 KTime_Get();

NTSTATUS KMem_Read(void* Src, SIZE_T Len, void* Dst, SIZE_T & Copied);
NTSTATUS KUtil_RWPhyMem(void* Src, SIZE_T Len, void* Dst, SIZE_T& Size, BOOLEAN bWrite);
NTSTATUS KUtil_RWMsrSafe(ULONG MSRIndex, ULONG64& Data, BOOLEAN bWrite);