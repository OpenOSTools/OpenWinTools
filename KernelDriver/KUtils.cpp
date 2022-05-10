#include <ntifs.h>
#include "KUtils.h"

BOOLEAN CheckNTStatus(NTSTATUS Status)
{
	BOOLEAN Ret = NT_SUCCESS(Status);

	if (!Ret)
	{
		KdBreakPoint();
	}
	return	Ret;
}

ULONG64 KTime_Get()
{
	LARGE_INTEGER CurTime, Freq;
	CurTime = KeQueryPerformanceCounter(&Freq);
	return (ULONG64)((CurTime.QuadPart * 1000 * 1000 * 1000) / Freq.QuadPart);
}

NTSTATUS KMem_Read(void* Src, SIZE_T Len, void* Dst, SIZE_T& Copied)
{
	NTSTATUS Ret = STATUS_SUCCESS;
	__try
	{
		MM_COPY_ADDRESS SrcAddr;
		SrcAddr.VirtualAddress = (void*)Src;
		Ret = MmCopyMemory(Dst, SrcAddr, Len, MM_COPY_MEMORY_VIRTUAL, &Copied);
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		Ret = GetExceptionCode();
		WARN_ON(1);
	}
	
	return	Ret;
}
