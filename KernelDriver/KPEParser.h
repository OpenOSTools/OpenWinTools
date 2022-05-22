#pragma once
#include <ntimage.h>

class CKPEParser
{
private:
    unsigned char* m_PEBase;
    ULONG m_PESize;
public:

    CKPEParser(PVOID Base, ULONG Size)
    {
        Init(Base, Size);
    }

    VOID Init(PVOID Base, ULONG Size)
    {
        m_PEBase = (unsigned char*)Base;
        m_PESize = Size;
    }

    //from titanhide
    ULONG RvaToSection(IMAGE_NT_HEADERS* pNtHdr, ULONG dwRVA)
    {
        USHORT wSections;
        PIMAGE_SECTION_HEADER pSectionHdr;
        pSectionHdr = IMAGE_FIRST_SECTION(pNtHdr);
        wSections = pNtHdr->FileHeader.NumberOfSections;
        for (int i = 0; i < wSections; i++)
        {
            if (pSectionHdr[i].VirtualAddress <= dwRVA)
                if ((pSectionHdr[i].VirtualAddress + pSectionHdr[i].Misc.VirtualSize) > dwRVA)
                {
                    return i;
                }
        }
        return (ULONG)-1;
    }

    ULONG RvaToOffset(PIMAGE_NT_HEADERS pnth, ULONG Rva)
    {
        PIMAGE_SECTION_HEADER psh = IMAGE_FIRST_SECTION(pnth);
        USHORT NumberOfSections = pnth->FileHeader.NumberOfSections;
        for (int i = 0; i < NumberOfSections; i++)
        {
            if (psh->VirtualAddress <= Rva)
            {
                if ((psh->VirtualAddress + psh->Misc.VirtualSize) > Rva)
                {
                    Rva -= psh->VirtualAddress;
                    Rva += psh->PointerToRawData;
                    return Rva < m_PESize ? Rva : (ULONG)-1;
                }
            }
            psh++;
        }
        return (ULONG)-1;
    }

    ULONG GetExportOffset(const char* ExportName)
    {
        //Verify DOS Header
        PIMAGE_DOS_HEADER pdh = (PIMAGE_DOS_HEADER)m_PEBase;
        if (pdh->e_magic != IMAGE_DOS_SIGNATURE)
        {
            return (ULONG)-1;
        }

        //Verify PE Header
        PIMAGE_NT_HEADERS pnth = (PIMAGE_NT_HEADERS)(m_PEBase + pdh->e_lfanew);
        if (pnth->Signature != IMAGE_NT_SIGNATURE)
        {
            return (ULONG)-1;
        }

        //Verify Export Directory
        PIMAGE_DATA_DIRECTORY pdd = NULL;
        if (pnth->OptionalHeader.Magic == IMAGE_NT_OPTIONAL_HDR64_MAGIC)
            pdd = ((PIMAGE_NT_HEADERS64)pnth)->OptionalHeader.DataDirectory;
        else
            pdd = ((PIMAGE_NT_HEADERS32)pnth)->OptionalHeader.DataDirectory;
        ULONG ExportDirRva = pdd[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress;
        ULONG ExportDirSize = pdd[IMAGE_DIRECTORY_ENTRY_EXPORT].Size;
        ULONG ExportDirOffset = RvaToOffset(pnth, ExportDirRva);
        if (ExportDirOffset == -1)
        {
            return (ULONG)-1;
        }

        //Read Export Directory
        PIMAGE_EXPORT_DIRECTORY ExportDir = (PIMAGE_EXPORT_DIRECTORY)(m_PEBase + ExportDirOffset);
        ULONG NumberOfNames = ExportDir->NumberOfNames;
        ULONG AddressOfFunctionsOffset = RvaToOffset(pnth, ExportDir->AddressOfFunctions);
        ULONG AddressOfNameOrdinalsOffset = RvaToOffset(pnth, ExportDir->AddressOfNameOrdinals);
        ULONG AddressOfNamesOffset = RvaToOffset(pnth, ExportDir->AddressOfNames);
        if (AddressOfFunctionsOffset == (ULONG)-1 ||
            AddressOfNameOrdinalsOffset == (ULONG)-1 ||
            AddressOfNamesOffset == (ULONG)-1)
        {
            return (ULONG)-1;
        }
        ULONG* AddressOfFunctions = (ULONG*)(m_PEBase + AddressOfFunctionsOffset);
        USHORT* AddressOfNameOrdinals = (USHORT*)(m_PEBase + AddressOfNameOrdinalsOffset);
        ULONG* AddressOfNames = (ULONG*)(m_PEBase + AddressOfNamesOffset);

        //Find Export
        ULONG ExportOffset = (ULONG)-1;
        for (ULONG i = 0; i < NumberOfNames; i++)
        {
            ULONG CurrentNameOffset = RvaToOffset(pnth, AddressOfNames[i]);
            if (CurrentNameOffset == (ULONG)-1)
                continue;
            const char* CurrentName = (const char*)(m_PEBase + CurrentNameOffset);
            ULONG CurrentFunctionRva = AddressOfFunctions[AddressOfNameOrdinals[i]];
            if (CurrentFunctionRva >= ExportDirRva && CurrentFunctionRva < ExportDirRva + ExportDirSize)
                continue; //we ignore forwarded exports
            if (!strcmp(CurrentName, ExportName))  //compare the export name to the requested export
            {
                ExportOffset = RvaToOffset(pnth, CurrentFunctionRva);
                break;
            }
        }

        if (ExportOffset == (ULONG)-1)
        {
        }

        return ExportOffset;
    }

    PVOID GetPageBase(PVOID lpHeader, ULONG* Size, PVOID ptr)
    {
        if ((unsigned char*)ptr < (unsigned char*)lpHeader)
            return 0;
        ULONG dwRva = (ULONG)((unsigned char*)ptr - (unsigned char*)lpHeader);
        IMAGE_DOS_HEADER* pdh = (IMAGE_DOS_HEADER*)lpHeader;
        if (pdh->e_magic != IMAGE_DOS_SIGNATURE)
            return 0;
        IMAGE_NT_HEADERS* pnth = (IMAGE_NT_HEADERS*)((unsigned char*)lpHeader + pdh->e_lfanew);
        if (pnth->Signature != IMAGE_NT_SIGNATURE)
            return 0;
        IMAGE_SECTION_HEADER* psh = IMAGE_FIRST_SECTION(pnth);
        int section = RvaToSection(pnth, dwRva);
        if (section == (ULONG)-1)
            return 0;
        if (Size)
            *Size = psh[section].SizeOfRawData;
        return (PVOID)((unsigned char*)lpHeader + psh[section].VirtualAddress);
    }
private:

};
