#pragma once

void* __cdecl operator new(size_t Size, POOL_TYPE Pool, ULONG tag = 'weNK');
void* __cdecl operator new(size_t Size, POOL_TYPE Pool, EX_POOL_PRIORITY priority, ULONG tag = 'weNK');
void __cdecl  operator delete(void* p, size_t);

class KSpinLock
{
public:
    KSpinLock()
    {
        KeInitializeSpinLock(&m_LockObj);
    }

    VOID Lock()
    {
        KeAcquireSpinLock(&m_LockObj, &m_irql);
    }

    VOID UnLock()
    {
        KeReleaseSpinLock(&m_LockObj, m_irql);
    }

private:
    KSPIN_LOCK  m_LockObj;
    KIRQL       m_irql;
};

class KMutex
{
public:
    KMutex() 
    {
        KeInitializeMutex(&m_LockObj, 0);
    }

    VOID Lock()
    {
        KeWaitForSingleObject(&m_LockObj, Executive, KernelMode, FALSE, NULL);
    }

    VOID UnLock()
    {
        KeReleaseMutex(&m_LockObj, FALSE);
    }

private:
    KMUTEX m_LockObj;
};


template <typename T>
class KAutoLock
{
private:
    T& _Lock;
public:
    KAutoLock(T& LockObj):_Lock(LockObj)
    {
        
        _Lock.Lock();
    }

    ~KAutoLock()
    {
        _Lock.UnLock();
    }
};

typedef	KAutoLock<KSpinLock>				CAutoSpinLock;
typedef	KAutoLock<KMutex>				    CAutoMutex;