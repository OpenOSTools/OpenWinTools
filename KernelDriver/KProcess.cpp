#include <ntifs.h>
#include "KProcess.h"
#include <ntstrsafe.h>
#include "../Shared/IOControl.h"
#include "KDynData.h"
#include "KClass.h"


ULONG GetNextPID()
{
	SIZE_T	CIDTable = 0;
	KData_ReadNTOS<SIZE_T>(Offset_PSPCIDTABLE, CIDTable);

	SIZE_T	NextPIDOffset = KData_Get(Offset_NextPID);
	
	ULONG NextPID = 0;
	SIZE_T ReadLen = 0;
	KMem_Read((void*)(CIDTable + NextPIDOffset), sizeof(NextPID), &NextPID, ReadLen);

	return	NextPID;
}

NTSTATUS HandleEnumProcess(ULONG& inLen, ULONG& outLen, PVOID pBuffer)
{
	UNREFERENCED_PARAMETER(inLen);
	UNREFERENCED_PARAMETER(outLen);
	UNREFERENCED_PARAMETER(pBuffer);
	IOProcessInfo* PsInfo = (IOProcessInfo*)pBuffer; 
	ULONG		MaxPID = GetNextPID() + 0x1000;
	ULONG		PsCount = 0;
	ULONG		ReturnedCount = 0;
	PEPROCESS	TaskStruct = NULL;

	for (ULONG i = 0; i < MaxPID; i += 4){
		if (NT_SUCCESS(PsLookupProcessByProcessId((HANDLE)i, &TaskStruct))){
			KASSRT(TaskStruct != NULL);

			if (SIZE_FIT(PsInfo, sizeof(IOProcessInfo), pBuffer, outLen)){
				PsInfo->PID			= PsGetProcessId(TaskStruct);
				PsInfo->ProcessObj	= TaskStruct;
				PsInfo->ParentPID	= PsGetProcessInheritedFromUniqueProcessId(TaskStruct);
				RtlStringCbCopyNA(PsInfo->PsName, sizeof(PsInfo->PsName), (char*)PsGetProcessImageFileName(TaskStruct), 16);

				
/*
				KAPC_STATE	ApcState;
				KeStackAttachProcess(TaskStruct, &ApcState);
				
				IO_COUNTERS IOCounter;
				ULONG		BuffLen = sizeof(IOCounter);
				NTSTATUS Ret = NtQueryInformationProcess(NtCurrentProcess(), ProcessIoCounters, &IOCounter, BuffLen, &BuffLen);


				KeUnstackDetachProcess(&ApcState);*/
				
				ReturnedCount++;
			}

			ObDereferenceObject(TaskStruct);
			PsInfo++;
			PsCount++;
		}
	}

	outLen = PsCount * sizeof(IOProcessInfo);
	return PsCount == ReturnedCount ? STATUS_SUCCESS : STATUS_BUFFER_TOO_SMALL;
}

typedef PVOID(NTAPI* _HalMap)(PHYSICAL_ADDRESS Pa, SIZE_T Len, int type);

_HalMap hm = (_HalMap)0xfffff801d8875660;
_KdpCopyMemoryChunks KDCopy = (_KdpCopyMemoryChunks)0xfffff801d873764c;
CHAR test[0x1000];
NTSTATUS HandleEnumKernelModule(ULONG& inLen, ULONG& outLen, PVOID pBuffer)
{
    
/*
    PHYSICAL_ADDRESS    PA;
    KdBreakPoint();
    size_t end = 1024 * 1024 * 1024;
    for (size_t i = (SIZE_T)0; i < end; i += 0x1000)
    {
       
        PA.QuadPart = i;
        SIZE_T r = 0;
        MM_COPY_ADDRESS addr;
        addr.VirtualAddress = (PVOID)i;
            //NT_SUCCESS(KDCopy((ULONG64)PA.QuadPart, test, 0x1000, 8, 0, &r))
        //NT_SUCCESS(MmCopyMemory(test, addr, 0x1000, MM_COPY_MEMORY_PHYSICAL, &r))
        if (NT_SUCCESS(KDCopy((ULONG64)PA.QuadPart, test, 0x1000, 8, MMDBG_COPY_PHYSICAL, &r)))
        {
            //KdPrint(("%p %d\n", PA.QuadPart,r));
        }
        else
        {
            KdPrint(("%p %d\n", PA.QuadPart, r));
            //KdBreakPoint();
        }
    }
    KdBreakPoint();*/
    

	UNREFERENCED_PARAMETER(inLen);
	ULONG		ReturnLen = 0;
    NTSTATUS	Status;


    do 
    {
        Status = ZwQuerySystemInformation(SystemModuleInformation, NULL, 0, &ReturnLen);

        CKBuffer<SYSTEM_MODULE_INFORMATION> Buff(ReturnLen + PAGE_SIZE);

        if (!OK(Buff)) {
            Status = STATUS_NO_MEMORY;
            break;
        }

        Status = ZwQuerySystemInformation(SystemModuleInformation, Buff, Buff.Size(), &ReturnLen);

        if (!STATUS_OK(Status)) {
            outLen = ReturnLen + PAGE_SIZE;
            break;
        }

        ULONG	ModuleCount = Buff->Count;
        IOKernelModuleInfo* pInfo = (IOKernelModuleInfo*)pBuffer;

        if (outLen < ModuleCount * sizeof(IOKernelModuleInfo))
        {
            outLen = (ModuleCount + 0x100) * sizeof(IOKernelModuleInfo);
            Status = STATUS_BUFFER_TOO_SMALL;
            break;
        }


        for (size_t i = 0; i < Buff->Count; i++) {
            
            KDLogPrint("Base:%p Size:%u Name:%s order:%u\n",
                Buff->Module[i].Base, Buff->Module[i].Size, Buff->Module[i].ImageName, Buff->Module[i].Index);

            pInfo->Base = Buff->Module[i].Base;
            pInfo->Size = Buff->Module[i].Size;
            pInfo->Order = Buff->Module[i].Index;

            memcpy(pInfo->Name, Buff->Module[i].ImageName, sizeof(Buff->Module[i].ImageName));

            pInfo++;            
        }

        outLen = ModuleCount * sizeof(IOKernelModuleInfo);

    } while (FALSE);

	return	Status;	
}

NTSTATUS HandlePIO(ULONG& inLen, ULONG& outLen, PVOID pBuffer)
{
    UNREFERENCED_PARAMETER(inLen);

    IOCTL_BUFF* IOCtl = (IOCTL_BUFF*)pBuffer;
    IOPORTInfo* PIO = &IOCtl->PIO;

    if (PIO->IOLength > outLen && PIO->IOType)
    {
        outLen = PIO->IOLength;
        return  STATUS_BUFFER_TOO_SMALL;
    }

    NTSTATUS Status = STATUS_SUCCESS;

    if (PIO->IOType)
    {
        switch (PIO->IOLength)
        {
        case 1:
            READ_PORT_BUFFER_UCHAR((PUCHAR)PIO->IOPort, (PUCHAR)pBuffer, 1);
            break;

        case 2:
            READ_PORT_BUFFER_USHORT((PUSHORT)PIO->IOPort, (PUSHORT)pBuffer, 1);
            break;
        
        case 4:
            READ_PORT_BUFFER_ULONG((PULONG)PIO->IOPort, (PULONG)pBuffer, 1);
            break;

        default:
            Status = STATUS_INVALID_BUFFER_SIZE;
            break;
        }
    }
    else
    {
        switch (PIO->IOLength)
        {
        case 1:
            WRITE_PORT_UCHAR((PUCHAR)PIO->IOPort, (UCHAR)PIO->WriteData);
            break;

        case 2:
            WRITE_PORT_USHORT((PUSHORT)PIO->IOPort, (USHORT)PIO->WriteData);
            break;

        case 4:
            WRITE_PORT_ULONG((PULONG)PIO->IOPort, (ULONG)PIO->WriteData);
            break;

        default:
            Status = STATUS_INVALID_BUFFER_SIZE;
            break;
        }
    }
    return  Status;
}