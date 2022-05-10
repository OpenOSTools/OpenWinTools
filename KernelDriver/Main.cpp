#include <ntifs.h>
#include "Main.h"
#include "../Shared/IOControl.h"
#include "IOControlHandler.h"
#include "KDynData.h"
#include "KProcess.h"

PDEVICE_OBJECT	IODevObj;
VOID OnUnload(PDRIVER_OBJECT pDrvObj)
{
	UNREFERENCED_PARAMETER(pDrvObj);
	UNICODE_STRING	SymName;
	RtlInitUnicodeString(&SymName, L"\\DosDevices\\OpenWinTools");
	IoDeleteSymbolicLink(&SymName);

	IoDeleteDevice(IODevObj);
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

NTSTATUS InitIODevice(PDRIVER_OBJECT pDrvObj)
{
	NTSTATUS		Status;
	UNICODE_STRING	DeviceName;
	RtlInitUnicodeString(&DeviceName, L"\\Device\\OpenWinTools");
	Status = IoCreateDevice(pDrvObj, 0, &DeviceName, FILE_DEVICE_UNKNOWN, 0, FALSE, &IODevObj);

	if (!SUCCESS(Status)){
		return Status;
	}

	UNICODE_STRING	SymName;
	RtlInitUnicodeString(&SymName, L"\\DosDevices\\OpenWinTools");
	IoDeleteSymbolicLink(&SymName);
	Status = IoCreateSymbolicLink(&SymName, &DeviceName);

	if (!SUCCESS(Status)){
		IoDeleteDevice(IODevObj);
	}
	IODevObj->Flags &= ~DO_DEVICE_INITIALIZING;
	return	Status;
}

VOID InitDispatch(PDRIVER_OBJECT DrvObj)
{
	for (size_t n = 0; n < IRP_MJ_MAXIMUM_FUNCTION; n++){
		DrvObj->MajorFunction[n] = OnInvalidDeviceRequest;
	}

	DrvObj->MajorFunction[IRP_MJ_DEVICE_CONTROL] = OnIOControl;
	DrvObj->MajorFunction[IRP_MJ_CREATE] = OnDeviceCreate;
	DrvObj->MajorFunction[IRP_MJ_CLOSE] = OnDeviceClose;
	DrvObj->MajorFunction[IRP_MJ_CLEANUP] = OnDeviceCleanup;
	DrvObj->DriverUnload = OnUnload;
}

NTSTATUS DriverEntry(PDRIVER_OBJECT DrvObj, PUNICODE_STRING RegistryPath)
{
	UNREFERENCED_PARAMETER(RegistryPath);
	UNREFERENCED_PARAMETER(DrvObj);
	ULONG n = 0;
	
	HandleEnumKernelModule(n, n, NULL);

	return	STATUS_UNSATISFIED_DEPENDENCIES;

/*
	
	InitDispatch(DrvObj);
	IOControlInit();

	NTSTATUS Status = KData_Init();

	if (!SUCCESS(Status)){
		return	Status;
	}

	Status = InitIODevice(DrvObj);

	if (!SUCCESS(Status)){
		return	Status;
	}

	return STATUS_SUCCESS;*/
}