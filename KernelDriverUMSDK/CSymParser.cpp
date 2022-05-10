#include "stdafx.h"
#include "CSymParser.h"

#pragma comment(lib,"Dbghelp.lib")

BOOL CSymParser::m_Inited = FALSE;

BOOL CSymParser::LoadFile(LPCTSTR szFile, LPCTSTR szSymbolPath)
{
	LOCKSYM;

	if (!m_Inited)
	{
		m_SymProcess = GetCurrentProcess();
		m_Inited = SymInitialize(m_SymProcess, CT2W(szSymbolPath), FALSE);
		DWORD OldOpt = SymGetOptions();
		OldOpt |= SYMOPT_DEFERRED_LOADS | SYMOPT_ALLOW_ABSOLUTE_SYMBOLS 
					| SYMOPT_UNDNAME | SYMOPT_FAIL_CRITICAL_ERRORS;
#ifdef _DEBUG
		OldOpt |= SYMOPT_DEBUG;
#endif
		SymSetOptions(OldOpt);
	}

	if (m_Inited == FALSE)
	{
		return	FALSE;
	}
	
	if (!(m_SymModBase = SymLoadModuleExW(m_SymProcess, NULL, CT2W(szFile), 0, 0, NULL, 0, 0)))
	{
		return	FALSE;
	}

	return TRUE;
}

 BOOL CSymParser::GetSymName(ULONG Index, CStringW& Ret) 
{
	LPCWSTR Name = NULL;
	if (SymGetTypeInfo(m_SymProcess, m_SymModBase, Index, TI_GET_SYMNAME, &Name) && Name) {
		Ret = Name;
		LocalFree((HLOCAL)Name);
		return TRUE;
	}
	return FALSE;
}
BOOL CSymParser::GetSymType(ULONG Index, enum CSymParser::BasicType& Type)
{
	return SymGetTypeInfo(m_SymProcess, m_SymModBase, Index, TI_GET_TYPE, &Type);;
}

BOOL CSymParser::GetSymBaseType(ULONG Index, enum CSymParser::BasicType& Type)
{
	return SymGetTypeInfo(m_SymProcess, m_SymModBase, Index, TI_GET_BASETYPE, &Type);
}

BOOL CSymParser::GetSymSize(ULONG Index, UINT64& Size)
{
	return SymGetTypeInfo(m_SymProcess, m_SymModBase, Index, TI_GET_LENGTH, &Size);
}
BOOL CSymParser::GetSymTag(ULONG Index, enum SymTagEnum& SymTag)
{
	return SymGetTypeInfo(m_SymProcess, m_SymModBase, Index, TI_GET_SYMTAG, &SymTag);
}

BOOL CSymParser::GetSymTypeName(ULONG Index, PUINT64 BaseTypeSize, CStringW& TypeName)
{
	if (!Index)
	{
		TypeName = L"";
		return FALSE;
	}

	UINT64 SymSize;
	GetSymSize(Index, SymSize);
	if (BaseTypeSize) *BaseTypeSize = SymSize;
	GetSymName(Index, TypeName);
	if (!TypeName.IsEmpty()) return TRUE;
	
	enum SymTagEnum Tag;
	GetSymTag(Index, Tag);
	switch (Tag) {
	case SymTagBaseType: {
		enum BasicType Type;
		GetSymBaseType(Index, Type);
		switch (Type) {
		case btNoType:
			TypeName = L"NO_TYPE";
			break;
		case btVoid:
			TypeName = L"VOID";
			break;
		case btChar:
			TypeName = L"CHAR";
			break;
		case btWChar:
			TypeName = L"WCHAR";
			break;
		case btInt:
			TypeName = SymSize == sizeof(INT64) ? L"INT64" : L"INT";
			break;
		case btUInt:
			TypeName = SymSize == sizeof(UINT64) ? L"UINT64" : L"UINT";
			break;
		case btFloat:
			TypeName = L"float";
			break;
		case btBCD:
			TypeName = L"BCD";
			break;
		case btBool:
			TypeName = L"BOOL";
			break;
		case btLong:
			TypeName = SymSize == sizeof(LONGLONG) ? L"LONGLONG" : L"LONG";
			break;
		case btULong:
			TypeName = SymSize == sizeof(ULONGLONG) ? L"ULONGLONG" : L"ULONG";
			break;
		case btCurrency:
			TypeName = L"Currency";
			break;
		case btDate:
			TypeName = L"DATE";
			break;
		case btVariant:
			TypeName = L"VARIANT";
			break;
		case btComplex:
			TypeName = L"_Complex";
			break;
		case btBit:
			TypeName = L"Bit";
			break;
		case btBSTR:
			TypeName = L"BSTR";
			break;
		case btHresult:
			TypeName = L"HRESULT";
			break;
		case btChar16:
			TypeName = L"char16_t";
			break;
		case btChar32:
			TypeName = L"char32_t";
			break;
		case btChar8:
			TypeName = L"char8_t";
			break;
		}
		break;
	}
	case SymTagPointerType: {
		BasicType Type;
		GetSymType(Index, Type);
		GetSymTypeName(Type, BaseTypeSize, TypeName);

		//TODO:: Check TI_GET_IS_REFERENCE
		TypeName += L"*";

		break;
	}
	case SymTagArrayType: {
		ULONG Type;
		GetSymArrayTypeId(Index, Type);
		GetSymTypeName(Type, BaseTypeSize, TypeName);
		break;
	}
	default: {
		BasicType Type;
		GetSymType(Index, Type);
		GetSymTypeName(Type,  BaseTypeSize, TypeName);
	}
	}

	return TRUE;
}
BOOL CSymParser::GetSymArrayTypeId(ULONG Index, ULONG& TypeID) 
{
	BOOL SymStatus = SymGetTypeInfo(m_SymProcess, m_SymModBase, Index, TI_GET_ARRAYINDEXTYPEID, &TypeID);
	return SymStatus;
}
BOOL CSymParser::GetSymTypeId(ULONG Index, ULONG& TypeId)
{
	return SymGetTypeInfo(m_SymProcess, m_SymModBase, Index, TI_GET_TYPEID, &TypeId);
}

BOOL CSymParser::GetFiledOffset(ULONG Index, ULONG& Offset)
{
	return SymGetTypeInfo(m_SymProcess, m_SymModBase, Index, TI_GET_OFFSET, &Offset);;
}

BOOL CSymParser::GetSymAddressOffset(ULONG Index, ULONG& Offset)
{
	return SymGetTypeInfo(m_SymProcess, m_SymModBase, Index, TI_GET_ADDRESSOFFSET, &Offset);
}
BOOL CSymParser::GetVAddressOffset(ULONG Index, ULONG& Offset)
{
	return SymGetTypeInfo(m_SymProcess, m_SymModBase, Index, TI_GET_VIRTUALBASEPOINTEROFFSET, &Offset);
}

BOOL CSymParser::GetSymBitPosition(ULONG Index, ULONG& BitPos)
{
	return SymGetTypeInfo(m_SymProcess, m_SymModBase, Index, TI_GET_BITPOSITION, &BitPos);
}
BOOL CSymParser::GetSymbolLayout(LPCTSTR SymbolName, SymbolLayout& SymInfo) 
{
	LOCKSYM;

	SYMINFO RootSymbolInfo;

	if (!SymGetTypeFromNameW(m_SymProcess, m_SymModBase, CT2W(SymbolName), RootSymbolInfo))
	{
		return FALSE;
	}

	ULONG RootIndex = RootSymbolInfo->Index;
	
	GetSymName(RootIndex, SymInfo.Name);
	GetSymSize(RootIndex, SymInfo.Size);
	
	if (RootSymbolInfo->Address > RootSymbolInfo->ModBase)
	{
		SymInfo.Offset = RootSymbolInfo->Address - RootSymbolInfo->ModBase;
	}

	

	UINT64 s;
	CStringW	n;
	GetSymTypeName(RootIndex,&s,n);

	GetSymTag(RootIndex, SymInfo.SymTag);
	SymInfo.Name = SymbolName;

	if (SymInfo.SymTag != SymTagUDT)
	{
		return	TRUE;
	}

	ULONG ChildrenCount = 0;
	SymGetTypeInfo(m_SymProcess, m_SymModBase, RootIndex, TI_GET_CHILDRENCOUNT, &ChildrenCount);
	SymGetTypeInfo(m_SymProcess, m_SymModBase, RootIndex, TI_GET_LENGTH, &SymInfo.Size);

	if (ChildrenCount) {
		std::vector<BYTE> FindChildrenParamsBuffer(sizeof(TI_FINDCHILDREN_PARAMS) + ChildrenCount * sizeof(ULONG));
		TI_FINDCHILDREN_PARAMS* Children = (TI_FINDCHILDREN_PARAMS*)FindChildrenParamsBuffer.data();

		Children->Count = ChildrenCount;
		Children->Start = 0;

		SymGetTypeInfo(m_SymProcess, m_SymModBase, RootIndex, TI_FINDCHILDREN, Children);

		for (ULONG i = 0; i < ChildrenCount; i++) {
			MemberInfo Entry;
			ULONG ChildIndex = Children->ChildId[i];
			ULONG TypeId;

			GetSymTypeId(ChildIndex, TypeId);
			GetSymName(ChildIndex, Entry.Name);
			GetSymSize(TypeId, Entry.Size);
			GetFiledOffset(ChildIndex, Entry.Offset);
			GetSymTag(ChildIndex, Entry.SymTag);

			Entry.IsBitField = GetSymBitPosition(ChildIndex, Entry.BitPosition);
			
			UINT64 BaseTypeSize = 0;
			GetSymTypeName(TypeId, &BaseTypeSize, Entry.TypeName);
			Entry.ElementsCount = BaseTypeSize != 0 ? Entry.Size / BaseTypeSize : 1;

			if (Entry.Name.IsEmpty()) Entry.Name = L"UNKNOWN_NAME";
			if (Entry.TypeName.IsEmpty()) Entry.TypeName = L"UNKNOWN_TYPE";

			SymInfo.Entries.emplace_back(Entry);
		}
	}

	return TRUE;
}
