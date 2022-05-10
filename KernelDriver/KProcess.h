#ifndef _KPROCESS_
#define _KPROCESS_

NTSTATUS HandleEnumKernelModule(ULONG& inLen, ULONG& outLen, PVOID pBuffer);
NTSTATUS HandleEnumProcess(ULONG& inLen, ULONG& outLen, PVOID pBuffer);

#endif
