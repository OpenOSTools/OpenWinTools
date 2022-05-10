#pragma once
#include <windows.h>
#include <tchar.h>
#include "../Shared/IOControl.h"

using namespace System;

namespace CSSDK {
	public ref class CDriverIO
	{
	public:
		
	private:
		HANDLE m_hIODevice;
		
	public:
		bool Init()
		{
			m_hIODevice = CreateFile(_T("\\??\\OpenWinTools"), GENERIC_ALL, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
			
			return	m_hIODevice != INVALID_HANDLE_VALUE;
		}

		bool GetProcessInfo(IOProcessInfo& PsInfo)
		{
			memset(&PsInfo, 0, sizeof(PsInfo));
			return	true;	
		}

	};
}
