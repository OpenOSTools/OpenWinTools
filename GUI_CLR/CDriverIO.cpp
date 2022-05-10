#include "pch.h"
#include "CDriverIO.h"
#include "../Shared/IOControl.h"
#include <cliext/vector>

HANDLE CDriverIO::m_hDevice = INVALID_HANDLE_VALUE;

CDriverIO::CDriverIO()
{
}

CDriverIO::~CDriverIO()
{
	if (m_hDevice != INVALID_HANDLE_VALUE){
		CloseHandle(m_hDevice);
	}
}

BOOL CDriverIO::Init()
{
	m_hDevice = CreateFile(_T("\\\\.\\OpenWinTools"), GENERIC_ALL, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	return m_hDevice != INVALID_HANDLE_VALUE;
}

BOOL CDriverIO::GetProcessList(IOProcessInfo* PsArray, ULONG& Count)
{
	ULONG Size = Count * sizeof(IOProcessInfo);
	ULONG RetSize = 0;

	IOCTL_BUFF	IoCtl;
	IoCtl.dwCtlCode = IOEnumProcess;

	BOOL Ret = DeviceIoControl(m_hDevice, IOCTL_EVERYTHING, &IoCtl, sizeof(IoCtl), PsArray, Size, &RetSize, NULL);

	Count = RetSize / sizeof(IOProcessInfo);
	return	Ret;
}
