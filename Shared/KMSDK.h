#pragma once

namespace OWTKMSDK
{
	class KMSDK
	{
	public:
		KMSDK();
		~KMSDK();
	public:

		static BOOL		InstallDriver(LPCTSTR DriverBinPath, DWORD StartType,LPCTSTR ServiceName);
		static BOOL		UnInstallDriver(LPCTSTR ServiceName);
	public:
		static HANDLE	OpenDriver(LPCTSTR ServiceName);
		static BOOL		CloseDriver(HANDLE DeviceHandle);

	private:

	};

	KMSDK::KMSDK()
	{
	}

	KMSDK::~KMSDK()
	{
	}


}