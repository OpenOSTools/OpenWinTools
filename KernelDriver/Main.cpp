#include <ntifs.h>
#include "Main.h"
#include "../Shared/IOControl.h"
#include "IOControlHandler.h"


VOID OnUnload(PDRIVER_OBJECT pDrvObj)
{
	UNREFERENCED_PARAMETER(pDrvObj);
	DbgPrint("OnUnload\r\n");
}

NTSTATUS OnInvalidDeviceRequest(PDEVICE_OBJECT pDevObj, IRP* pIRP)
{
	UNREFERENCED_PARAMETER(pDevObj);

	pIRP->IoStatus.Status = STATUS_INVALID_DEVICE_REQUEST;
	pIRP->IoStatus.Information = 0;
	IoCompleteRequest(pIRP, IO_NO_INCREMENT);
	return	STATUS_INVALID_DEVICE_REQUEST;
}

NTSTATUS OnDeviceCreate(PDEVICE_OBJECT pDevObj, IRP* pIRP)
{
	UNREFERENCED_PARAMETER(pDevObj);

	pIRP->IoStatus.Status = STATUS_SUCCESS;
	pIRP->IoStatus.Information = 0;
	IoCompleteRequest(pIRP, IO_NO_INCREMENT);
	return	STATUS_SUCCESS;
}

NTSTATUS OnDeviceClose(PDEVICE_OBJECT pDevObj, IRP* pIRP)
{
	UNREFERENCED_PARAMETER(pDevObj);

	pIRP->IoStatus.Status = STATUS_SUCCESS;
	pIRP->IoStatus.Information = 0;
	IoCompleteRequest(pIRP, IO_NO_INCREMENT);
	return	STATUS_SUCCESS;
}

NTSTATUS OnDeviceCleanup(PDEVICE_OBJECT pDevObj, IRP* pIRP)
{
	UNREFERENCED_PARAMETER(pDevObj);

	pIRP->IoStatus.Status = STATUS_SUCCESS;
	pIRP->IoStatus.Information = 0;
	IoCompleteRequest(pIRP, IO_NO_INCREMENT);
	return	STATUS_SUCCESS;
}

NTSTATUS OnIOControl(PDEVICE_OBJECT pDevObj, IRP* pIRP)
{
	UNREFERENCED_PARAMETER(pDevObj);

	NTSTATUS Status = STATUS_INVALID_DEVICE_REQUEST;
	PIO_STACK_LOCATION	Packet = IoGetCurrentIrpStackLocation(pIRP);

	ULONG ulInputLen = Packet->Parameters.DeviceIoControl.InputBufferLength;
	ULONG ulOutputLen = Packet->Parameters.DeviceIoControl.OutputBufferLength;
	ULONG ulCtlCode = Packet->Parameters.DeviceIoControl.IoControlCode;

	switch (ulCtlCode)
	{
	case IOCTL_EVERYTHING:
		Status = HandleIOControl(ulInputLen, ulOutputLen, pIRP->AssociatedIrp.SystemBuffer);
		break;
	default:
		DbgPrint("Unknown ioctl code:%08x\n", ulCtlCode);
		break;
	}

	pIRP->IoStatus.Status = Status;
	pIRP->IoStatus.Information = NT_SUCCESS(Status) ? ulOutputLen : 0;
	IoCompleteRequest(pIRP, IO_NO_INCREMENT);
	return	Status;
}

NTSTATUS DriverEntry(PDRIVER_OBJECT pDrvObj, PUNICODE_STRING pRegistryPath)
{
	UNREFERENCED_PARAMETER(pRegistryPath);

	
	
	for (size_t n = 0; n < IRP_MJ_MAXIMUM_FUNCTION; n++)
	{
		pDrvObj->MajorFunction[n] = OnInvalidDeviceRequest;
	}
	
	pDrvObj->MajorFunction[IRP_MJ_DEVICE_CONTROL] = OnIOControl;
	pDrvObj->MajorFunction[IRP_MJ_CREATE] = OnDeviceCreate;
	pDrvObj->MajorFunction[IRP_MJ_CLOSE] = OnDeviceClose;
	pDrvObj->MajorFunction[IRP_MJ_CLEANUP] = OnDeviceCleanup;
	pDrvObj->DriverUnload = OnUnload;

	return STATUS_SUCCESS;
}