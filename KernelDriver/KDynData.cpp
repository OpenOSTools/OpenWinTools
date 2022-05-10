#include <ntifs.h>
#include <aux_klib.h>
#include "KUtils.h"
#include "../Shared/IOControl.h"
#include "KDynData.h"


static SIZE_T DynData[DATA_MAX];


NTSTATUS KData_Init()
{
	AuxKlibInitialize();

	memset(DynData, 0xFF, sizeof(DynData));

	ULONG	BuffSize = 0;
	AuxKlibQueryModuleInformation(&BuffSize, sizeof(AUX_MODULE_EXTENDED_INFO), NULL);

	BuffSize *= 2;
	AUX_MODULE_EXTENDED_INFO* pModInfo = (AUX_MODULE_EXTENDED_INFO*)ExAllocatePoolWithTag(PagedPool, BuffSize, 'domK');

	if (pModInfo)
	{
		AuxKlibQueryModuleInformation(&BuffSize, sizeof(AUX_MODULE_EXTENDED_INFO), pModInfo);
		KData_Set(Base_NTOS, (SIZE_T)pModInfo->BasicInfo.ImageBase);
		ExFreePoolWithTag(pModInfo, 'domK');
	}


	KData_Set(Offset_PSPCIDTABLE, 0x3c4318);
	KData_Set(Offset_NextPID, 0);


	ULONG64	now = KTime_Get();
	for (SIZE_T i = 0; i < 10000000; i += 4)
	{
		PEPROCESS	TaskStruct = NULL;
		if (NT_SUCCESS(PsLookupProcessByProcessId((HANDLE)i, &TaskStruct)))
		{
			WARN_ON(!TaskStruct);
			ObDereferenceObject(TaskStruct);
		}
	}
	now = KTime_Get() - now;
	KdPrint(("ns:%llu\n", now));


	if (KData_Get(Base_NTOS))
	{
		return	STATUS_SUCCESS;
	}
	
	KdBreakPoint();
	return	STATUS_UNSUCCESSFUL;
	
}

SIZE_T KData_Get(enum DATA_TYPE type)
{
	return	DynData[type];
}

VOID KData_Set(DATA_TYPE Type, SIZE_T Data)
{
	DynData[Type] = Data;
}