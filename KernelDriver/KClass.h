#pragma once

void* __cdecl operator new(size_t Size, POOL_TYPE Pool, ULONG tag = 'weNK');
void* __cdecl operator new(size_t Size, POOL_TYPE Pool, EX_POOL_PRIORITY priority, ULONG tag = 'weNK');
void __cdecl  operator delete(void* p,size_t s);
void __cdecl  operator delete(void* p);

void* __cdecl operator new[](size_t Size, POOL_TYPE Pool, ULONG tag = 'weNK');
void* __cdecl operator new[](size_t Size, POOL_TYPE Pool, EX_POOL_PRIORITY priority, ULONG tag = 'weNK');
void __cdecl  operator delete[](void* p);

class CKSpinLock
{
public:
    CKSpinLock()
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

class CKMutex
{
public:
    CKMutex() 
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
class CKAutoLock
{
private:
    T& _Lock;
public:
    CKAutoLock(T& LockObj):_Lock(LockObj)
    {
        
        _Lock.Lock();
    }

    ~CKAutoLock()
    {
        _Lock.UnLock();
    }
};

typedef	CKAutoLock<CKSpinLock>				CKAutoSpinLock;
typedef	CKAutoLock<CKMutex>				    CKAutoMutex;


template <typename T>
class CKBuffer
{
public:
    CKBuffer(ULONG SizeInBytes, POOL_TYPE PoolType = NonPagedPool, ULONG Tag = 'fuBK')
    {
        Alloc(SizeInBytes, PoolType, Tag);
    }

    CKBuffer()
    {
        m_Size = 0;
        m_Buffer = NULL;
    }

    T* Alloc(ULONG SizeInBytes, POOL_TYPE PoolType = NonPagedPool, ULONG Tag = 'fuBK')
    {
        delete m_Buffer;
        m_Size = SizeInBytes;
        m_Buffer = new(PoolType, Tag) char[m_Size];
        return  (T*)m_Buffer;
    }

    ~CKBuffer()
    {
        delete []m_Buffer;
    }

    T* Ptr()
    {
        return  (T*)m_Buffer;
    }

    T* operator->() 
    { 
        return Ptr();
    }

    operator T*()
    {
        return  (T*)m_Buffer;
    }

    ULONG Size()
    {
        return  m_Size;
    }

private:
    ULONG   m_Size;
    char*   m_Buffer;
};

class CKAttachProcess
{
public:
    CKAttachProcess(PEPROCESS PsObj)
    {
        if (PsObj)
        {
            KeStackAttachProcess(PsObj, &m_State);
            m_Attached = TRUE;
        }
    }

    ~CKAttachProcess()
    {
        if (m_Attached)
        {
            KeUnstackDetachProcess(&m_State);
        }
    }

private:
    KAPC_STATE m_State;
    BOOLEAN m_Attached;
};


class CKHandle
{
public:
    CKHandle(HANDLE h) :m_h(h)
    {

    }

    CKHandle()
    {

    }

    VOID Close()
    {
        if (m_h)
        {
            ZwClose(m_h);
            m_h = NULL;
        }
    }

    VOID Attach(HANDLE h)
    {
        Close();
        m_h = h;
    }

    HANDLE Detach()
    {
        HANDLE bak = m_h;
        m_h = NULL;
        return  bak;
    }
    ~CKHandle()
    {
        Close();
    }

    operator HANDLE()
    {
        return  m_h;
    }

    HANDLE* operator &()
    {
        return  &m_h;
    }

private:
    HANDLE m_h;
};

class CKRefObj
{
public:
    CKRefObj(
        _In_ HANDLE Handle,
        _In_ ACCESS_MASK DesiredAccess,
        _In_opt_ POBJECT_TYPE ObjectType = NULL,
        _In_ KPROCESSOR_MODE AccessMode = KernelMode,
        _Out_opt_ POBJECT_HANDLE_INFORMATION HandleInformation = NULL
    ):m_p(NULL)
    {
        m_st = ObReferenceObjectByHandle(Handle, DesiredAccess, ObjectType, AccessMode, &m_p, HandleInformation);
       if (!STATUS_OK(m_st))
       {
           m_p = NULL;
       }
    }

    CKRefObj(_In_ PVOID pObj):m_p(pObj)
    {

    }

    PVOID Detach()
    {
        PVOID Ret = m_p;
        m_p = NULL;
        return  Ret;
    }

    NTSTATUS Status()
    {
        return  m_st;
    }

    BOOLEAN Valid()
    {
        return  m_p != NULL;
    }

    ~CKRefObj()
    {
        if (m_p)
        {
            ObDereferenceObject(m_p);
        }
    }

private:
    PVOID       m_p;
    NTSTATUS    m_st;
};
