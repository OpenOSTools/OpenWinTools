#include "NTTypes.h"

#ifndef _IOCONTROL_
#define _IOCONTROL_

#define IOCTL_EVERYTHING			CTL_CODE(FILE_DEVICE_UNKNOWN, 0x1000, METHOD_BUFFERED, FILE_ANY_ACCESS)


enum IOCODE
{
	IOCodeMin = 0,
	IOEnumProcess,
	IOEnumThread,
	IOEnumHandle,
	IOEnumTCP,
	IOEnumWindows,
	IOEnumMsgHook,
	IOReadMemory,
	IOWriteMemory,
	IOReadPort,
	IOReadMSR,
	IOWriteMSR,
	IOReadPhyMem,
	IOWritePhyMem,

	IOCodeMAX
};



struct IOCTL_BUFF
{
	IOCODE	dwCtlCode;
	unsigned char	data[1];
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
	unsigned __int64	PID;
	unsigned __int64	ParentPID;
	WCHAR				ProcessName[MAX_PATH];

	PROC_PERF_COUNTER	PerfCounter;
	
};


struct IOThreadInfo
{
	unsigned __int64 PID;
	unsigned __int64 TID;
	unsigned __int64 EntryPoint;
	unsigned int	 SuspendCount;
	unsigned int	 CreationTime;
};


#endif // _IOCONTROL_
