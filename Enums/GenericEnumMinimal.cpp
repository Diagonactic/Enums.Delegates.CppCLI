#include "Stdafx.h"
#include "MsilConvert.h"
#include "GenericEnumMinimal.h"

#define GenericEnumMinimalMethod(returnType) GenericEnumType returnType Diagonactic::GenericEnumMinimal<TEnum>::

#define CaseKind(macroName, kind, source, target) switch (kind) {\
			macroName(Int32, source, target);\
			macroName(Int64, source, target);\
			macroName(Int16, source, target);\
			macroName(Byte, source, target);\
			macroName(UInt32, source, target);\
			macroName(UInt64, source, target);\
			macroName(UInt16, source, target);\
			macroName(SByte, source, target);\
	}


#define AREALLFLAGSSET(type, sourceEnum, enumFlagsToCheck) case UnderlyingKind::type##Kind:\
{\
	auto i = enumFlagsToCheck->Length;\
	do {\
		i--;\
		if (!(Util::IsFlagSet(Util::ClobberTo##type(sourceEnum), Util::ClobberTo##type(enumFlagsToCheck[i]))))\
			return false;\
		if (i == 0) return true;\
	} while(true);\
}

#define AREANYFLAGSSET(type, sourceEnum, enumFlagsToCheck) case UnderlyingKind::type##Kind:\
{\
	auto i = enumFlagsToCheck->Length;\
	do {\
		i--;\
		if (Util::IsFlagSet(Util::ClobberTo##type(sourceEnum), Util::ClobberTo##type(enumFlagsToCheck[i])))\
			return true;\
		if (i == 0) return false;\
	} while(true);\
}
#define AREANYFLAGSSETALL(sourceEnum, enumFlagsToCheck) switch(s_kind) {\
	AREANYFLAGSSET(Int32, sourceEnum, enumFlagsToCheck)\
	AREANYFLAGSSET(Int64, sourceEnum, enumFlagsToCheck)\
	AREANYFLAGSSET(Int16, sourceEnum, enumFlagsToCheck)\
	AREANYFLAGSSET(UInt32, sourceEnum, enumFlagsToCheck)\
	AREANYFLAGSSET(UInt64, sourceEnum, enumFlagsToCheck)\
	AREANYFLAGSSET(UInt16, sourceEnum, enumFlagsToCheck)\
	AREANYFLAGSSET(Byte, sourceEnum, enumFlagsToCheck)\
	AREANYFLAGSSET(SByte, sourceEnum, enumFlagsToCheck)\
}
#define AREALLFLAGSSETALL(sourceEnum, enumFlagsToCheck) switch(s_kind) {\
	AREALLFLAGSSET(Int32, sourceEnum, enumFlagsToCheck)\
	AREALLFLAGSSET(Int64, sourceEnum, enumFlagsToCheck)\
	AREALLFLAGSSET(Int16, sourceEnum, enumFlagsToCheck)\
	AREALLFLAGSSET(UInt32, sourceEnum, enumFlagsToCheck)\
	AREALLFLAGSSET(UInt64, sourceEnum, enumFlagsToCheck)\
	AREALLFLAGSSET(UInt16, sourceEnum, enumFlagsToCheck)\
	AREALLFLAGSSET(Byte, sourceEnum, enumFlagsToCheck)\
	AREALLFLAGSSET(SByte, sourceEnum, enumFlagsToCheck)\
}



#define TYPECASECALLRETURN(type, callPart, p1, p2) case UnderlyingKind::type##Kind: return MsilConvert::ClobberFrom<TEnum>(Util::##callPart(Util::ClobberTo##type(p1), Util::ClobberTo##type(p2)))
#define EXECUTEFOREACHALLTYPES(enumMethod, enumVal, enumArray) switch(s_kind) {\
	TYPECASEEXECUTEFOREACH(Int32, enumMethod, enumVal, enumArray)\
	TYPECASEEXECUTEFOREACH(Int64, enumMethod, enumVal, enumArray)\
	TYPECASEEXECUTEFOREACH(Int16, enumMethod, enumVal, enumArray)\
	TYPECASEEXECUTEFOREACH(UInt32, enumMethod, enumVal, enumArray)\
	TYPECASEEXECUTEFOREACH(UInt64, enumMethod, enumVal, enumArray)\
	TYPECASEEXECUTEFOREACH(UInt16, enumMethod, enumVal, enumArray)\
	TYPECASEEXECUTEFOREACH(Byte, enumMethod, enumVal, enumArray)\
	TYPECASEEXECUTEFOREACH(SByte, enumMethod, enumVal, enumArray)\
}
#define EXECUTEALLTYPES(callPart, p1, p2) switch (s_kind) { \
	TYPECASECALLRETURN(Int32, callPart, p1, p2);\
	TYPECASECALLRETURN(UInt32, callPart, p1, p2);\
	TYPECASECALLRETURN(Int64, callPart, p1, p2);\
	TYPECASECALLRETURN(UInt64, callPart, p1, p2);\
	TYPECASECALLRETURN(Int16, callPart, p1, p2);\
	TYPECASECALLRETURN(UInt16, callPart, p1, p2);\
	TYPECASECALLRETURN(Byte, callPart, p1, p2);\
	TYPECASECALLRETURN(SByte, callPart, p1, p2);\
}

#define EXECUTEALLTYPESARRAYTARGET(callPart, p1, p2) switch (s_kind) { \
	TYPECASECALLRETURN(Int32,  ArrayInt32,  callPart, p1, p2);\
	TYPECASECALLRETURN(UInt32, ArrayUInt32, callPart, p1, p2);\
	TYPECASECALLRETURN(Int64,  ArrayInt64,  callPart, p1, p2);\
	TYPECASECALLRETURN(UInt64, ArrayUInt64, callPart, p1, p2);\
	TYPECASECALLRETURN(Int16,  ArrayInt16,  callPart, p1, p2);\
	TYPECASECALLRETURN(UInt16, ArrayUInt16, callPart, p1, p2);\
	TYPECASECALLRETURN(Byte,   ArrayByte,   callPart, p1, p2);\
	TYPECASECALLRETURN(SByte,  ArraySByte,  callPart, p1, p2);\
}

#define IsFlagSetNumerically(type, source, target) case UnderlyingKind::type##Kind: return Util::IsFlagSet<type>(*reinterpret_cast<type*>(&source), *reinterpret_cast<type*>(&target));

#define AddFlagArray(type, source, targetArray) case UnderlyingKind::type##Kind: return AddFlags##type(source, targetArray);

#define TYPECASEEXECUTEFOREACH(type, enumMethod, enumVal, enumArray)				\
	case UnderlyingKind::type##Kind:												\
	{																				\
		auto retVal = Util::ClobberTo##type(enumVal);								\
		for (int i = 0; i < enumArray->Length; i++)									\
			retVal = Util::enumMethod(retVal, Util::ClobberTo##type(enumArray[i]));	\
		return MsilConvert::ClobberFrom<TEnum>(retVal);								\
	}

#define CaseAddFlagNumerically(type, source, target) \
	case UnderlyingKind::type##Kind: \
		return MsilConvert::ClobberFrom<TEnum>((*reinterpret_cast<type*>(&source)) | (*reinterpret_cast<type*>(&target)))


#define AddFlagArrayMethod(type) GenericEnumMinimalMethod(TEnum) AddFlags##type(TEnum enumVal, array<TEnum>^ enumArray) {	\
	type retVal = *reinterpret_cast<type*>(&enumVal);													\
	TEnum flagToAdd;																					\
	for (int i = 0; i < enumArray->Length; i++)															\
		retVal = retVal | (Util::ClobberTo##type(flagToAdd));											\
	return MsilConvert::ClobberFrom<TEnum>(retVal);														\
}
#pragma warning(disable:4958)
#pragma warning(disable:4957)
#pragma warning(disable:4956)
AddFlagArrayMethod(Int32)
AddFlagArrayMethod(UInt32)
AddFlagArrayMethod(Int64)
AddFlagArrayMethod(UInt64)
AddFlagArrayMethod(Int16)
AddFlagArrayMethod(UInt16)
AddFlagArrayMethod(Byte)
AddFlagArrayMethod(SByte)
#pragma warning(default:4958)
#pragma warning(default:4957)
#pragma warning(default:4956)

GenericEnumMinimalMethod(Boolean) IsFlagSet(TEnum source, TEnum testVal)
{
	CaseKind(IsFlagSetNumerically, s_kind, source, testVal)
	throw gcnew Exception("This should never throw. All underlying types are represented above.");
}

GenericEnumMinimalMethod(Boolean) AreAllFlagsSet(array<TEnum>^ enumFlagsToCheck, TEnum sourceEnum)
{
	AREALLFLAGSSETALL(sourceEnum, enumFlagsToCheck);
	throw gcnew Exception("This should never throw. All underlying types are represented above.");
}

GenericEnumMinimalMethod(Boolean) AreAnyFlagsSet(array<TEnum>^ enumFlagsToCheck, TEnum sourceEnum)
{
	AREANYFLAGSSETALL(sourceEnum, enumFlagsToCheck);
	throw gcnew Exception("This should never throw. All underlying types are represented above.");
}


GenericEnumMinimalMethod(TEnum) AddFlag(TEnum sourceEnum, TEnum target)
{
	CaseKind(CaseAddFlagNumerically, s_kind, sourceEnum, target)
	throw gcnew Exception("This should never throw. All underlying types are represented above.");
}


GenericEnumMinimalMethod(TEnum) RemoveFlags(TEnum sourceEnum, ...array<TEnum>^ enumFlagsToRemove)
{
	EXECUTEFOREACHALLTYPES(RemoveFlagFrom, sourceEnum, enumFlagsToRemove)
	throw gcnew Exception("This should never throw. All underlying types are represented above.");
}


GenericEnumMinimalMethod(TEnum) AddFlags(array<TEnum>^ enumFlagsToAdd, TEnum sourceEnum)
{
	EXECUTEFOREACHALLTYPES(AddFlagTo, sourceEnum, enumFlagsToAdd);
	throw gcnew Exception("This should never throw. All underlying types are represented above.");
}


GenericEnumMinimalMethod(TEnum) RemoveFlag(TEnum sourceEnum, TEnum enumFlagToRemove)
{
	EXECUTEALLTYPES(RemoveFlagFrom, sourceEnum, enumFlagToRemove);
	throw gcnew Exception("This should never throw. All underlying types are represented above.");
}

GenericEnumMinimalMethod(TEnum) AddFlagsSpecial(array<TEnum>^ enumFlagsToAdd, TEnum sourceEnum)
{
	EXECUTEFOREACHALLTYPES(AddFlagToSpecial, sourceEnum, enumFlagsToAdd);
	throw gcnew Exception("This should never throw. All underlying types are represented above.");
}

GenericEnumMinimalMethod(Boolean) EqualsAny(array<TEnum>^ enumValuesToCheck, TEnum sourceEnum)
{
	auto len = enumValuesToCheck->Length;
	for (int i = 0; i < len; i++) {
		if (enumValuesToCheck[i] == sourceEnum)
			return true;
	}
	return false;
}
