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

void __cdecl operator delete(void* p, size_t s) {
    UNREFERENCED_PARAMETER(s);
    operator    delete(p);
}
void __cdecl operator delete(void* p) {
    if (p)
    {
        ExFreePool(p);
    }
}

void* __cdecl operator new[](size_t Size, POOL_TYPE Pool, ULONG tag)
{
    return operator new(Size, Pool, tag);
}

void* __cdecl operator new[](size_t Size, POOL_TYPE Pool, EX_POOL_PRIORITY priority, ULONG tag)
{
    return operator new(Size, Pool, priority, tag);
}

void __cdecl operator delete[](void* p)
{
    operator delete(p);
}
