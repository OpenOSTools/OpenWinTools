#pragma once
#include "../Shared/IOControl.h"
#include <cliext/vector>

class CDriverIO
{
public:
	CDriverIO();
	~CDriverIO();

public:
	static BOOL Init();
	static BOOL CDriverIO::GetProcessList(IOProcessInfo* PsArray, ULONG& Count);

private:
	static HANDLE m_hDevice;
};