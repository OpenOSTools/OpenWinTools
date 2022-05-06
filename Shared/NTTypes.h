#pragma once

#ifndef WIN32
#define MAX_PATH 260
#endif

#ifndef _NTDDK_
typedef struct _UNICODE_STRING {
	USHORT Length;
	USHORT MaximumLength;
	PWCH   Buffer;
} UNICODE_STRING;
typedef UNICODE_STRING* PUNICODE_STRING;
typedef const UNICODE_STRING* PCUNICODE_STRING;
#endif
//from www.geoffchappell.com

typedef struct _SYSTEM_PROCESS_INFORMATION {
	ULONG NextEntryOffset;
	ULONG NumberOfThreads;
	LARGE_INTEGER ReadTransferCount_3_X; //3.10 only	later at 0xA0
	LARGE_INTEGER SpareLi1; //3.50 to 5.2
	LARGE_INTEGER WorkingSetPrivateSize; //6.0 and higher
	LARGE_INTEGER WriteTransferCount_3_X; //3.10 only	later at 0xA8
	LARGE_INTEGER SpareLi2; //3.50 to 6.0
	ULONG HardFaultCount; //6.1 and higher
	ULONG NumberOfThreadsHighWatermark; //6.1 and higher
	LARGE_INTEGER OtherTransferCount_3_X; //3.10 only	later at 0xB0
	LARGE_INTEGER SpareLi3; //3.50 to 6.0
	ULONGLONG CycleTime;//6.1 and higher
	LARGE_INTEGER CreateTime;
	LARGE_INTEGER UserTime;
	LARGE_INTEGER KernelTime;
	UNICODE_STRING ImageName;
	LONG BasePriority;
	PVOID UniqueProcessId;
	PVOID InheritedFromUniqueProcessId;
	ULONG ReadOperationCount_3_X; //3.10 only	later as LARGE_INTEGER at 0x88
	ULONG SpareUl1; //3.50 only
	ULONG HandleCount;//3.51 and higher
	ULONG WriteOperationCount_3_X;//3.10 only	later as LARGE_INTEGER at 0x90
	ULONG SpareUl2;//3.50 to 4.0
	ULONG SessionId; //5.0 and higher
	ULONG OtherOperationCount_3_X; //3.10 only	later as LARGE_INTEGER at 0x98
	ULONG SpareUl3; //3.50 to 5.0
	ULONG_PTR UniqueProcessKey;//5.1 and higher
	ULONG_PTR PeakVirtualSize;
	ULONG_PTR VirtualSize;
	ULONG PageFaultCount;
	ULONG_PTR PeakWorkingSetSize;
	ULONG_PTR WorkingSetSize;
	ULONG_PTR QuotaPeakPagedPoolUsage;
	ULONG_PTR QuotaPagedPoolUsage;
	ULONG_PTR QuotaPeakNonPagedPoolUsage;
	ULONG_PTR QuotaNonPagedPoolUsage;
	ULONG_PTR PagefileUsage;
	ULONG_PTR PeakPagefileUsage;
	ULONG_PTR PrivatePageCount; //all	last member in 3.10 to 4.0
	LARGE_INTEGER ReadOperationCount; //5.0 and higher	earlier as ULONG at 0x4C
	LARGE_INTEGER WriteOperationCount; //5.0 and higher	earlier as ULONG at 0x50
	LARGE_INTEGER OtherOperationCount;//5.0 and higher	earlier as ULONG at 0x54
	LARGE_INTEGER ReadTransferCount;//5.0 and higher	earlier at 0x08
	LARGE_INTEGER WriteTransferCount;//5.0 and higher	earlier at 0x10
	LARGE_INTEGER OtherTransferCount;//5.0 and higher	earlier at 0x18
} SYSTEM_PROCESS_INFORMATION, * PSYSTEM_PROCESS_INFORMATION;

