#ifndef _IOCONTROL_
#define _IOCONTROL_

#include "NTTypes.h"

#define IOCTL_EVERYTHING			CTL_CODE(FILE_DEVICE_UNKNOWN, 0x1000, METHOD_BUFFERED, FILE_ANY_ACCESS)

enum IOCODE
{
	IOCodeMin = 0,
	IOInitOffset,
	IOEnumProcess,
    IOEnumKMod,
    IOEnumUMod,
	IOEnumThread,
	IOEnumHandle,
	IOEnumTCP,
	IOEnumWindows,
	IOEnumMsgHook,
	IORWMemory,
	IORWPort,
	IORWMSR,
    IORWPhyMem,

	IOCodeMAX
};

struct IOPORTInfo
{
    int     IOType;
    ULONG   IOLength;
    ULONG   IOPort;
    ULONG   WriteData;
};

struct IOCTL_BUFF
{
	IOCODE	dwCtlCode;
    union
    {
        IOPORTInfo PIO;

    };
    
};

struct PROC_PERF_COUNTER 
{
	LARGE_INTEGER CPUTime;
	LARGE_INTEGER IOWriteBytes;
	LARGE_INTEGER IOReadBytes;
	LARGE_INTEGER IOReadCounts;
	LARGE_INTEGER IOWriteCounts;
	LARGE_INTEGER IOOtherBytes;
	LARGE_INTEGER IOOtherCount;
	LARGE_INTEGER ThreadCount;
	LARGE_INTEGER HandleCount;
	LARGE_INTEGER PageFaultCount;
};

struct IOProcessInfo
{
	HANDLE	PID;
	HANDLE	ParentPID;
	PVOID	ProcessObj;
	char	PsName[17];
	PROC_PERF_COUNTER	PerfCounter;
};

struct IOKernelModuleInfo
{
	PVOID Base;
	ULONG Size;
	ULONG Order;

	WCHAR	Name[MAX_PATH];
};

struct IOThreadInfo
{
	unsigned __int64 PID;
	unsigned __int64 TID;
	unsigned __int64 EntryPoint;
	unsigned int	 SuspendCount;
	unsigned int	 CreationTime;
};

enum DATA_TYPE
{
	Base_NTOS,
	Offset_PSPCIDTABLE,
	Offset_NextPID,
	DATA_MAX
};


#endif // _IOCONTROL_