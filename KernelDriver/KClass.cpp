#include "stdafx.h"
#include "KClass.h"


void* __cdecl operator new(size_t size, POOL_TYPE pool, ULONG tag) 
{
    void* p = ExAllocatePoolWithTag(pool, size, tag);
    return p;
}

void* __cdecl operator new(size_t size, POOL_TYPE pool, EX_POOL_PRIORITY priority, ULONG tag) 
{
    return ExAllocatePoolWithTagPriority(pool, size, tag, priority);
}

void __cdecl operator delete(void* p, size_t) {
    NT_ASSERT(p);
    ExFreePool(p);
}