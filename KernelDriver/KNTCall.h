#pragma once
#include "KFile.h"
#include "KPEParser.h"

class CKNTCall
{
public:
    NTSTATUS Init()
    {
        NTSTATUS Status;

        Status = File.Create(L"\\SystemRoot\\system32\\ntdll.dll");
        if (!OK(NT_SUCCESS(Status))) {
            return  Status;
        }

        Status = File.Read();
        if (!OK(NT_SUCCESS(Status))) {
            return  Status;
        }

        PEParser.Init(File.Data(), (ULONG)File.Size());

        return  STATUS_SUCCESS;
    }

    

private:
    static CKFile     File;
    static CKPEParser PEParser;
};


