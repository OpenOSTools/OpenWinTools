#pragma once

class CKObjAttr
{
public:
    CKObjAttr(UNICODE_STRING* ObjName,
            ULONG ObjAttr = OBJ_KERNEL_HANDLE,
            HANDLE Root = NULL,
            SECURITY_DESCRIPTOR* SecDesc = NULL)
    {
        InitializeObjectAttributes(&m_ObjAttr, ObjName, ObjAttr, Root, SecDesc);
    }
    
    OBJECT_ATTRIBUTES* operator&()
    {
        return  &m_ObjAttr;
    }

    operator OBJECT_ATTRIBUTES*() 
    {
        return &m_ObjAttr;
    }

private:
    OBJECT_ATTRIBUTES   m_ObjAttr;
};

class CKString
{
public:

private:

};

class CKRegistry
{
public:
    

private:

};

class CKFile
{
public:
    CKFile() :m_hFile(NULL)
    {

    }

    ~CKFile()
    {
        if (m_hFile)
        {
            ZwClose(m_hFile);
        }
    }

    operator HANDLE()
    {
        return  m_hFile;
    }

    NTSTATUS Create(WCHAR* FileName, 
        ACCESS_MASK DesiredAccess = GENERIC_READ,
        ULONG CreateDisposition = FILE_OPEN,
        ULONG ShareAccess = FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
        ULONG FileAttrFlags = FILE_ATTRIBUTE_NORMAL,
        ULONG CreateOptions = FILE_SYNCHRONOUS_IO_NONALERT,
        ULONG ObjAttrFlags = OBJ_CASE_INSENSITIVE | OBJ_KERNEL_HANDLE)
    {
        NTSTATUS        Status;
        IO_STATUS_BLOCK IoStatus;
        UNICODE_STRING  ustrFileName;

        RtlInitUnicodeString(&ustrFileName, FileName);
        CKObjAttr Obj(&ustrFileName, ObjAttrFlags);
        
        KASSRT(KeAreAllApcsDisabled() == FALSE);

        Status = ZwCreateFile(&m_hFile, 
                    DesiredAccess, 
                    Obj, &IoStatus, 
                    NULL, FileAttrFlags,
                    ShareAccess, 
                    CreateDisposition, CreateOptions,
                    NULL, 0);
        
        return  Status;
    }

    NTSTATUS Read(void* Buffer, ULONG Length, PLARGE_INTEGER Offset = NULL)
    {
        KASSRT(KeAreAllApcsDisabled() == FALSE);

        IO_STATUS_BLOCK IoStatus;

        return ZwReadFile(m_hFile, NULL, NULL, NULL, &IoStatus, Buffer, Length, Offset, NULL);
    }

    NTSTATUS Write(void* Buffer, ULONG Length, PLARGE_INTEGER Offset = NULL)
    {
        KASSRT(KeAreAllApcsDisabled() == FALSE);

        IO_STATUS_BLOCK IoStatus;

        return ZwWriteFile(m_hFile, NULL, NULL, NULL, &IoStatus, Buffer, Length, Offset, NULL);
    }

    ULONGLONG Size()
    {
        NTSTATUS Status;
        IO_STATUS_BLOCK IoStatus;
        FILE_STANDARD_INFORMATION FileInfo = { 0 };

        Status = ZwQueryInformationFile(m_hFile, &IoStatus, &FileInfo, sizeof(FileInfo), FileStandardInformation);

        return  NT_SUCCESS(Status) ? (ULONGLONG)FileInfo.EndOfFile.QuadPart : 0;
    }

    NTSTATUS Read()
    {
        ULONGLONG FileSize = Size();

        if (!FileSize)
        {
            return  STATUS_FILE_NOT_AVAILABLE;
        }

        if (!m_Buff.Alloc((ULONG)FileSize))
        {
            return  STATUS_NO_MEMORY;
        }
        
        return  Read(m_Buff.Ptr(), (ULONG)FileSize);

    }

    PVOID Data()
    {
        return  m_Buff.Ptr();
    }
    
private:
    HANDLE m_hFile;
    CKBuffer<UCHAR> m_Buff;
};

class CKFileMap
{
public:
    CKFileMap()
    {
        m_Base = NULL;
        m_hSection = NULL;
        m_MapedSize = 0;
        m_hProcess = NULL;
    }

    ~CKFileMap()
    {
        if (m_Base)
        {
            ZwUnmapViewOfSection(m_hProcess, m_Base);
        }

        if (m_hSection)
        {
            ZwClose(m_hSection);
        }
    }
    
    NTSTATUS Map(HANDLE hFile,
        HANDLE      Process = NtCurrentProcess(),
        ULONGLONG   Offset = 0,
        ULONGLONG   Size = 0,
        ACCESS_MASK AccessMask = SECTION_MAP_READ,
        ULONG       Protection = PAGE_READONLY,
        ULONG       SecAttr = SEC_RESERVE,
        ULONG       ObjAttr = OBJ_CASE_INSENSITIVE | OBJ_KERNEL_HANDLE)
    {
        NTSTATUS Status;
        CKObjAttr Oa(NULL, ObjAttr);

        LARGE_INTEGER MapOffset;
        LARGE_INTEGER MapSize;

        MapOffset.QuadPart = Offset;
        MapSize.QuadPart = (LONGLONG)Size;

        m_hProcess = Process;

        Status = ZwCreateSection(&m_hSection, AccessMask, &Oa, &MapSize, Protection, SecAttr, hFile);

        if (OK(NT_SUCCESS(Status)))
        {
            Status = ZwMapViewOfSection(m_hSection, m_hProcess,
                        &m_Base, 0, 0, &MapOffset, &m_MapedSize,
                        ViewUnmap, SecAttr, Protection);
        }

        return  Status;
    }

private:
    HANDLE m_hProcess;
    HANDLE m_hSection;
    PVOID  m_Base;
    SIZE_T m_MapedSize;
};