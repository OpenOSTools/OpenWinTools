#include "stdafx.h"
#include "Main.h"
#include "../Shared/IOControl.h"
#include "IOControlHandler.h"
#include "KDynData.h"
#include "KProcess.h"
#include "KClass.h"

DRIVER_OBJECT* g_DrvObj;

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
        KLogPrint("Unknown ioctl code:%08x\n", ulCtlCode);
        BreakPoint();
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

	if (!STATUS_OK(Status)){
		return Status;
	}

	UNICODE_STRING	SymName;
	RtlInitUnicodeString(&SymName, L"\\DosDevices\\OpenWinTools");
	IoDeleteSymbolicLink(&SymName);
	Status = IoCreateSymbolicLink(&SymName, &DeviceName);

	if (!STATUS_OK(Status)){
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
    BreakPoint();
    g_DrvObj = DrvObj;

	ULONG n = 0x40000;
    CKBuffer<IOKernelModuleInfo>    Buff(n);
    
    HandleEnumKernelModule(n, n, Buff);
    
    
    {
        CKAttachProcess PsContext(PsInitialSystemProcess);

        MEMORY_BASIC_INFORMATION    MemoryInfo;
        SIZE_T  RetLen;
        NTSTATUS Status;

        SIZE_T  BaseAddr = 0;

        while (NT_SUCCESS(ZwQueryVirtualMemory(NtCurrentProcess(),
            (PVOID)BaseAddr, MemoryBasicInformation,
            &MemoryInfo, sizeof(MemoryInfo), &RetLen)))
        {
#define MemoryMappedFilenameInformation 2

            CKBuffer<UNICODE_STRING>    Buffer(0x1000);
            SIZE_T Tmp;
            if (NT_SUCCESS(ZwQueryVirtualMemory(NtCurrentProcess(),
                MemoryInfo.AllocationBase,
                (MEMORY_INFORMATION_CLASS)MemoryMappedFilenameInformation,
                Buffer, Buffer.Size(),
                &Tmp)))
            {
                KDLogPrint("%wZ Base:%p Size:%u", Buffer.Ptr(), MemoryInfo.AllocationBase, MemoryInfo.RegionSize);
            }

            BaseAddr += MemoryInfo.RegionSize;
        }
    }
    




    IOCTL_BUFF io;
    io.PIO.IOType = 0;
    io.PIO.IOLength = 1;
    io.PIO.IOPort = 0x70;
    io.PIO.WriteData = 9;
    ULONG s = sizeof(io);
    HandlePIO(s, s, &io);

    io.PIO.IOType = 1;
    io.PIO.IOLength = 1;
    io.PIO.IOPort = 0x71;
    s = sizeof(io);
    HandlePIO(s, s, &io);


    CKBuffer<UCHAR> TEMP(0X1000);

    BreakPoint();
    SIZE_T S = 0X1000;
    KUtil_RWPhyMem(0, 0X1000, TEMP, S, FALSE);

    KUtil_RWMsrSafe(0XFFFFFFFF, S, FALSE);


    KIRQL IRQL =  KeAcquireQueuedSpinLock(LockQueueIoDatabaseLock);

    
    KeReleaseQueuedSpinLock(LockQueueIoDatabaseLock, IRQL);

	return	STATUS_NO_MEMORY;

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