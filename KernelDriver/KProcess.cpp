#include <ntifs.h>
#include "KProcess.h"
#include <ntstrsafe.h>
#include "../Shared/IOControl.h"
#include "KDynData.h"


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
			WARN_ON(!TaskStruct);

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
    KdBreakPoint();
    

	UNREFERENCED_PARAMETER(inLen);
	ULONG		ReturnLen = 0;
	NTSTATUS	Status = ZwQuerySystemInformation(SystemModuleInformation, NULL, 0, &ReturnLen);

	WARN_ON(!ReturnLen);
	if (!ReturnLen){
		return	Status;
	}

	ReturnLen += 0x1000;

	SYSTEM_MODULE_INFORMATION* Buff = (SYSTEM_MODULE_INFORMATION*)ExAllocatePoolWithTag(PagedPool, ReturnLen, 'domb');

	if (!Buff){
		return	STATUS_RETRY;
	}

	Status = ZwQuerySystemInformation(SystemModuleInformation, Buff, ReturnLen, &ReturnLen);

	if (!CheckNTStatus(Status)){
		outLen = ReturnLen;
		return Status;
	}


	ULONG	ModuleCount = Buff->Count;
	ULONG	ModuleRetCount = 0;

	{
		IOKernelModuleInfo* pInfo = (IOKernelModuleInfo*)pBuffer;
		
		for (size_t i = 0; i < Buff->Count; i++){
			KdPrint(("Base:%p Size:%u Name:%s\n", Buff->Module[i].Base, Buff->Module[i].Size, Buff->Module[i].ImageName));
			if (SIZE_FIT(pInfo, sizeof(IOKernelModuleInfo), pBuffer, outLen)){

				

				pInfo->Base = Buff->Module[i].Base;
				pInfo->Size = Buff->Module[i].Size;
				pInfo->Order = Buff->Module[i].Index;
				memcpy(pInfo->Name, Buff->Module[i].ImageName, sizeof(Buff->Module[i].ImageName));
				ModuleRetCount++;
			}
		}
	}

	ExFreePoolWithTag(Buff, 'domb');
	outLen = ModuleCount * sizeof(IOKernelModuleInfo);

	return	Status;	
}