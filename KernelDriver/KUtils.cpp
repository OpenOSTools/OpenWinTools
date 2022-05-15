#include <ntifs.h>
#include <intrin.h>
#include "KUtils.h"
#include "KClass.h"

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

NTSTATUS KUtil_RWPhyMem(void* Src, SIZE_T Len, void* Dst, SIZE_T& Size, BOOLEAN bWrite)
{
    if (Len == 0)
    {
        return  STATUS_INVALID_PARAMETER_3;
    }

    NTSTATUS           Status;
    UNICODE_STRING     ObjName;
    OBJECT_ATTRIBUTES  ObjAttr;
    PHYSICAL_ADDRESS   SectionOffset;
    CKHandle           hSection;

    RtlInitUnicodeString(&ObjName, L"\\Device\\PhysicalMemory");

    InitializeObjectAttributes(&ObjAttr, &ObjName, OBJ_CASE_INSENSITIVE, NULL, NULL);

    Status = ZwOpenSection(&hSection, SECTION_ALL_ACCESS, &ObjAttr);

    if (!STATUS_OK(Status) || !OK(hSection))
    {
        return  Status;
    }

    CKRefObj    SectionObj(hSection, SECTION_ALL_ACCESS);

    if (!OK(SectionObj.Valid()))
    {
        return SectionObj.Status();
    }

    PHYSICAL_ADDRESS   Begin;
    PHYSICAL_ADDRESS   End;
    ULONG              AddrSpaceType;

    Begin.QuadPart = (bWrite ? (LONGLONG)Dst : (LONGLONG)Src);
    End.QuadPart = Begin.QuadPart + Size;
    
    if (!OK(HalTranslateBusAddress(Internal, 0, Begin, &AddrSpaceType, &Begin))
            || 
        !OK(HalTranslateBusAddress(Internal, 0, End, &AddrSpaceType, &End)))
    {
        return  STATUS_CONFLICTING_ADDRESSES;
    }

    SIZE_T MapSize = 0;

    MapSize = (SIZE_T)End.QuadPart - (SIZE_T)Begin.QuadPart;

    SectionOffset = Begin;

    SIZE_T MapBase = NULL;

    Status = ZwMapViewOfSection(hSection, NtCurrentProcess(), 
                (PVOID*)&MapBase, 0L, 
                MapSize, 
                &SectionOffset, &MapSize, 
                ViewShare, 0, PAGE_READWRITE | PAGE_NOCACHE);

    if (Status == STATUS_CONFLICTING_ADDRESSES)
    {
        BreakPoint();
        Status = ZwMapViewOfSection(hSection, NtCurrentProcess(),
            (PVOID*)&MapBase, 0L,
            MapSize,
            &SectionOffset, &MapSize,
            ViewShare, 0, PAGE_READWRITE | PAGE_NOCACHE);
    }

    if (!STATUS_OK(Status) || !OK(MapBase) || !OK(MapSize)) 
    {
        return  Status;
    }

    MapBase += (Begin.QuadPart - SectionOffset.QuadPart);
    
    __try
    {
        if (bWrite)
        {
            memcpy((void*)MapBase, Src, Size);
        }
        else
        {
            memcpy(Dst, (void*)MapBase, Size);
        }
    }__except(EXCEPTION_EXECUTE_HANDLER)
    {
        Status = GetExceptionCode();
        BreakPoint();
    }
    
    KASSRT(NT_SUCCESS(ZwUnmapViewOfSection(NtCurrentProcess(), (void*)MapBase)));

    return	Status;
}

NTSTATUS KUtil_RWMsrSafe(ULONG MSRIndex, ULONG64& Data, BOOLEAN bWrite)
{
    NTSTATUS ST = STATUS_SUCCESS;
    __try
    {
        if (bWrite)
        {
            __writemsr(MSRIndex, Data);
        }
        else
        {
            Data = __readmsr(MSRIndex);
        }

    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        ST = GetExceptionCode();
        BreakPoint();
    }

    return  ST;
}