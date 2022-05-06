#include <ntifs.h>
#include "KProcess.h"

NTSTATUS HandleEnumProcess(ULONG& inLen, ULONG& outLen, PVOID pBuffer)
{
	UNREFERENCED_PARAMETER(inLen);
	UNREFERENCED_PARAMETER(outLen);
	UNREFERENCED_PARAMETER(pBuffer);
	return STATUS_SUCCESS;
}
