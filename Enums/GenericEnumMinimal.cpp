#include "Stdafx.h"
#include "MsilConvert.h"
#include "GenericEnumMinimal.h"


#define ReturnConvertedFromUtilSourceTargetMethod(type, utilMethodName) return MsilConvert::ClobberFrom<TEnum>(Util::##utilMethodName(Util::ClobberTo##type(source), Util::ClobberTo##type(target)))

#define FlagsOperationOnEnumArray(type, enumMethod)											\
{																							\
	auto retVal = Util::ClobberTo##type(source);											\
	for (int i = 0; i < enumArray->Length; i++)												\
		retVal = Util::enumMethod(retVal, Util::ClobberTo##type(enumArray[i]));				\
	return MsilConvert::ClobberFrom<TEnum>(retVal);											\
}

#define ForEachBooleanReturn(type, arrayName, macroNameWithArrayParameter, defaultValue)	\
{																							\
	auto i = arrayName->Length;																\
	do {																					\
		i--;																				\
		macroNameWithArrayParameter(type, arrayName)										\
		if (i==0) return defaultValue;														\
	} while (true);																			\
}

#define AreAllEnumFlagsToCheckSetOnSourceOperation(type, arrayName) if (!Util::IsFlagSet(Util::ClobberTo##type(sourceEnum), Util::ClobberTo##type(arrayName[i]))) return false;
#define AreAnyEnumFlagsToCheckSetOnSourceOperation(type, arrayName) if (Util::IsFlagSet(Util::ClobberTo##type(sourceEnum), Util::ClobberTo##type(arrayName[i]))) return true;
#define AreAllEnumFlagsToCheckSetOnSource(type) ForEachBooleanReturn(type, enumFlagsToCheck, AreAllEnumFlagsToCheckSetOnSourceOperation, true)
#define AreAnyEnumFlagsToCheckSetOnSource(type) ForEachBooleanReturn(type, enumFlagsToCheck, AreAnyEnumFlagsToCheckSetOnSourceOperation, false)

#define RemoveTargetFromSource(type) ReturnConvertedFromUtilSourceTargetMethod(type, RemoveFlagFrom)
#define AddEnumArrayToSource(type) FlagsOperationOnEnumArray(type, AddFlagTo)
#define RemoveEnumArrayFromSource(type) FlagsOperationOnEnumArray(type, RemoveFlagFrom)
#define AddSpecialEnumArrayToSource(type) FlagsOperationOnEnumArray(type, AddFlagToSpecial)
#define IsFlagSetNumerically(type) return Util::IsFlagSet<type>(*reinterpret_cast<type*>(&source), *reinterpret_cast<type*>(&target));
#define AddFlagNumerically(type) return MsilConvert::ClobberFrom<TEnum>((*reinterpret_cast<type*>(&source)) | (*reinterpret_cast<type*>(&target)));

#define GenericEnumMinimalMethod(returnType) GenericEnumType returnType Diagonactic::GenericEnumMinimal<TEnum>::

#define AddFlagArrayMethod(type)																			\
	GenericEnumMinimalMethod(TEnum) AddFlags##type(TEnum enumVal, array<TEnum>^ enumArray) {				\
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

GenericEnumMinimalMethod(Boolean) IsFlagSet(TEnum source, TEnum target)
{
	SwitchOnType(s_kind, IsFlagSetNumerically)	
	ThrowEnumUnderlyingValueInvalid
}

GenericEnumMinimalMethod(Boolean) AreAllFlagsSet(array<TEnum>^ enumFlagsToCheck, TEnum sourceEnum)
{	
	SwitchOnType(s_kind, AreAllEnumFlagsToCheckSetOnSource)
	throw gcnew Exception("This should never throw. All underlying types are represented above.");
}

GenericEnumMinimalMethod(Boolean) AreAnyFlagsSet(array<TEnum>^ enumFlagsToCheck, TEnum sourceEnum)
{
	SwitchOnType(s_kind, AreAnyEnumFlagsToCheckSetOnSource)
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

GenericEnumMinimalMethod(TEnum) AddFlag(TEnum source, TEnum target)
{
	SwitchOnType(s_kind, AddFlagNumerically)
	throw gcnew Exception("This should never throw. All underlying types are represented above.");
}


GenericEnumMinimalMethod(TEnum) AddFlags(array<TEnum>^ enumArray, TEnum source)
{
	SwitchOnType(s_kind, AddEnumArrayToSource)
	throw gcnew Exception("This should never throw. All underlying types are represented above.");
}

GenericEnumMinimalMethod(TEnum) RemoveFlag(TEnum source, TEnum target)
{
	SwitchOnType(s_kind, RemoveTargetFromSource)
	throw gcnew Exception("This should never throw. All underlying types are represented above.");
}

GenericEnumMinimalMethod(TEnum) RemoveFlags(TEnum source, array<TEnum>^ enumArray)
{
	SwitchOnType(s_kind, RemoveEnumArrayFromSource)
	throw gcnew Exception("This should never throw. All underlying types are represented above.");
}

GenericEnumMinimalMethod(TEnum) AddFlagsSpecial(array<TEnum>^ enumArray, TEnum source)
{
	SwitchOnType(s_kind, AddSpecialEnumArrayToSource)
	throw gcnew Exception("This should never throw. All underlying types are represented above.");
}