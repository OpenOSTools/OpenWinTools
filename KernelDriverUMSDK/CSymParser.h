#pragma once
#define _NO_CVCONST_H
#define DBGHELP_TRANSLATE_TCHAR
#include <DbgHelp.h>
#include <string>


class CSymParser
{
public:
	enum BasicType
	{
		btNoType = 0,
		btVoid = 1,
		btChar = 2,
		btWChar = 3,
		btInt = 6,
		btUInt = 7,
		btFloat = 8,
		btBCD = 9,
		btBool = 10,
		btLong = 13,
		btULong = 14,
		btCurrency = 25,
		btDate = 26,
		btVariant = 27,
		btComplex = 28,
		btBit = 29,
		btBSTR = 30,
		btHresult = 31,
		btChar16 = 32,  // char16_t
		btChar32 = 33,  // char32_t
		btChar8 = 34,  // char8_t
	};

	struct SYMINFO
	{
		PSYMBOL_INFOW DataPtr;
		CBufferPtr	TempBuff;
		operator PSYMBOL_INFOW() const throw()
		{
			return	(PSYMBOL_INFOW)TempBuff.Ptr();
		}

		PSYMBOL_INFOW operator ->() const throw()
		{
			return	(PSYMBOL_INFOW)TempBuff.Ptr();
		}

		#define SYM_INFO_SIZE (sizeof(SYMBOL_INFOW) + (MAX_SYM_NAME + 1) * sizeof(WCHAR))
		SYMINFO() :TempBuff(SYM_INFO_SIZE, true)
		{
			DataPtr = (PSYMBOL_INFOW)TempBuff.Ptr();
			if (TempBuff.Ptr())
			{
				operator PSYMBOL_INFOW()->MaxNameLen = MAX_SYM_NAME;
				operator PSYMBOL_INFOW()->SizeOfStruct = (ULONG)TempBuff.Size();
			}
		}
	};

	struct MemberInfo {
		CStringW Name;
		CStringW TypeName;
		UINT64 ElementsCount;
		UINT64 Size;
		ULONG Offset;
		BOOL IsBitField;
		ULONG BitPosition;
		enum SymTagEnum SymTag;
	};
	struct SymbolLayout {
		CStringW Name;
		UINT64 Size;
		UINT64 Offset;
		enum SymTagEnum SymTag;
		std::vector<MemberInfo> Entries;
		SymbolLayout()
		{
			Size = 0;
			Offset = 0;
		}
	};

public:
	BOOL LoadFile(LPCTSTR szFile, LPCTSTR szSymbolPath);
	BOOL GetSymbolLayout(LPCTSTR SymbolName, SymbolLayout& SymInfo);
private:
	BOOL GetSymTypeName(ULONG Index, PUINT64 BaseTypeSize, CStringW& Ret);
	BOOL GetSymSize(ULONG Index, UINT64& Size);
	BOOL GetSymName(ULONG Index, CStringW& Ret);
	BOOL GetSymTag(ULONG Index, enum SymTagEnum& Tag);
	BOOL GetSymType(ULONG Index, enum BasicType& Type);
	BOOL GetSymBaseType(ULONG Index, enum BasicType& Type);
	BOOL GetSymArrayTypeId(ULONG Index, ULONG& ArrayTypeID);
	BOOL GetSymTypeId(ULONG Index, ULONG& SymTypeID);
	BOOL GetFiledOffset(ULONG Index, ULONG& Offset);
	BOOL GetSymAddressOffset(ULONG Index, ULONG& SymAddrOffset);
	BOOL GetVAddressOffset(ULONG Index, ULONG& Offset);
	BOOL GetSymBitPosition(ULONG Index, ULONG& BitPos);

private:
	static BOOL m_Inited;

private:
	CCriSec	m_SymLock;
	HANDLE	m_SymProcess;
	DWORD64	m_SymModBase;

	//most of DbgHelp functions are not threadsafe
	#define LOCKSYM CCriSecLock	_LocalLock(m_SymLock);
};


