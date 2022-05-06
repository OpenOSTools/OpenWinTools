#include "stdafx.h"
#include "KMSDK.h"


namespace OWTKMSDK
{

BOOL	KMSDK::InstallDriver(LPCTSTR DriverBinPath, DWORD StartType, LPCTSTR ServiceName)
{

	return	FALSE;
}

BOOL	KMSDK::UnInstallDriver(LPCTSTR ServiceName)
{
	return	FALSE;
}

HANDLE	KMSDK::OpenDriver(LPCTSTR ServiceName)
{
	return INVALID_HANDLE_VALUE;
}

BOOL	KMSDK::CloseDriver(HANDLE DeviceHandle)
{
	return	FALSE;
}

}