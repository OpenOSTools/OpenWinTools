#include <ntifs.h>
#include "../Shared/IOControl.h"
#include "IOControlHandler.h"
#include "KProcess.h"
#include "KUtils.h"

typedef	NTSTATUS(*_IOHandler)(ULONG& inLen, ULONG& outLen, PVOID pBuffer);
static _IOHandler IOCallback[IOCodeMAX];

NTSTATUS InvalidIOControl(ULONG& ulInputLen, ULONG& ulOutputLen, PVOID pBuffer)
{
	UNREFERENCED_PARAMETER(ulInputLen);
	UNREFERENCED_PARAMETER(ulOutputLen);
	UNREFERENCED_PARAMETER(pBuffer);
	return	STATUS_INVALID_DEVICE_REQUEST;
}

VOID IOControlInit()
{
	for (size_t i = 0; i < IOCodeMAX; i++)
	{
		IOCallback[i] = InvalidIOControl;
	}
	IOCallback[IOEnumProcess] = HandleEnumProcess;
}

NTSTATUS HandleIOControl(ULONG& ulInputLen, ULONG& ulOutputLen, PVOID pBuffer)
{
	NTSTATUS Status = STATUS_INVALID_DEVICE_REQUEST;
	IOCTL_BUFF* IOBuff = (IOCTL_BUFF*)pBuffer;
	ULONG		IOCode = IOBuff->dwCtlCode;

	if (IOCode < IOCodeMAX)
	{
		WARN_ON(!IOCallback[IOCode]);
		Status = IOCallback[IOCode](ulInputLen, ulOutputLen, pBuffer);
	}

	return Status;
}