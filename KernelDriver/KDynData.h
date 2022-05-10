#pragma once
#include "KUtils.h"

NTSTATUS	KData_Init();
SIZE_T		KData_Get(enum DATA_TYPE);
VOID		KData_Set(enum DATA_TYPE, SIZE_T);

template <typename T>
NTSTATUS	KData_ReadNTOS(enum DATA_TYPE Type, T& Buff)
{
	NTSTATUS	Ret = STATUS_NOT_FOUND;
	SIZE_T		NTOSBase = KData_Get(Base_NTOS);
	SIZE_T		Offset = KData_Get(Type);

	WARN_ON(!NTOSBase);

	__try
	{
		Buff = *(T*)(NTOSBase + Offset);
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		Ret = GetExceptionCode();
		WARN_ON(1);
	}
	return STATUS_SUCCESS;
}

