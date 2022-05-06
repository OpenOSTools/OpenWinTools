#pragma once

#define WIN32_LEAN_AND_MEAN
#include <tchar.h>
#include <windows.h>
#include <ATLBASE.h>
#include <stdint.h>
#include <vector>
#include <WindowsX.h>
#include <commctrl.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <atlstr.h>
#include <atltime.h>
#include <unordered_map>

#ifndef ASSERT
#define ASSERT(f)	ATLASSERT(f)
#endif
#ifndef VERIFY
#define VERIFY(f)	ATLVERIFY(f)
#endif
#ifndef ENSURE
#define ENSURE(f)	ATLENSURE(f)
#endif

#ifndef TRACE
#include <atltrace.h>

#define TRACE							AtlTrace
#define TRACE0(f)						TRACE(f)
#define TRACE1(f, p1)					TRACE(f, p1)
#define TRACE2(f, p1, p2)				TRACE(f, p1, p2)
#define TRACE3(f, p1, p2, p3)			TRACE(f, p1, p2, p3)
#define TRACE4(f, p1, p2, p3, p4)		TRACE(f, p1, p2, p3, p4)
#define TRACE5(f, p1, p2, p3, p4, p5)	TRACE(f, p1, p2, p3, p4, p5)
#endif


#include "Singleton.h"
#include "BufferPtr.h"
#include "Thread.h"
#include "Semaphore.h"
#include "CriticalSection.h"
#include "Event.h"

