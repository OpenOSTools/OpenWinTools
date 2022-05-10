#ifndef _IOCONTROL_HANDLER_
#define _IOCONTROL_HANDLER_

VOID IOControlInit();
NTSTATUS HandleIOControl(ULONG& ulInputLen, ULONG& ulOutputLen, PVOID pBuffer);

#endif
