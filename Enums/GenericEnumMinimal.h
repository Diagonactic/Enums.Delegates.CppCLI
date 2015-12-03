#pragma once
#include "Stdafx.h"
using namespace System;
using namespace System::Collections::Generic;
using namespace System::Reflection;
using namespace System::ComponentModel;
using namespace System::Runtime::InteropServices;

enum UnderlyingKind : char;
ref class Util;
ref class MsilConvert;

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

#define TYPECASEEXECUTEFOREACH(type, enumMethod, enumVal, enumArray) case UnderlyingKind::type##Kind:\
{\
Int32 len = enumArray->Length;\
auto retVal = Util::ClobberTo##type(enumVal);\
for (int i = 0; i < len; i++)\
	retVal = Util::enumMethod(retVal, Util::ClobberTo##type(enumArray[i]));\
return MsilConvert::ClobberFrom<TEnum>(retVal);\
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

namespace Diagonactic
{
	
	generic<typename TEnum>
		where TEnum : IComparable, IFormattable, IConvertible, System::Enum

		private ref class GenericEnumMinimal abstract
		{

		internal:

			static TEnum s_defaultValue = TEnum();
			static Type^ s_type = TEnum::typeid;
			static UnderlyingKind s_kind = Util::GetKind(s_defaultValue);

			static Boolean HasFlag(TEnum source, TEnum testVal)
			{				
				return Util::IsFlagSet(source, testVal, s_kind);
			}

			static TEnum RemoveFlags(TEnum sourceEnum, ...array<TEnum>^ enumFlagsToRemove)
			{
				EXECUTEFOREACHALLTYPES(RemoveFlagFrom, sourceEnum, enumFlagsToRemove)
				throw gcnew Exception("This should never throw. All underlying types are represented above.");
			}

			static TEnum AddFlags(array<TEnum>^ enumFlagsToAdd, TEnum sourceEnum)
			{
				EXECUTEFOREACHALLTYPES(AddFlagTo, sourceEnum, enumFlagsToAdd)
				throw gcnew Exception("This should never throw. All underlying types are represented above.");
			}

			static Boolean AreAllFlagsSet(array<TEnum>^ enumFlagsToCheck, TEnum sourceEnum)
			{
				AREALLFLAGSSETALL(sourceEnum, enumFlagsToCheck);				
				throw gcnew Exception("This should never throw. All underlying types are represented above.");
			}

			static Boolean AreAnyFlagsSet(array<TEnum>^ enumFlagsToCheck, TEnum sourceEnum)
			{
				AREANYFLAGSSETALL(sourceEnum, enumFlagsToCheck);
				throw gcnew Exception("This should never throw. All underlying types are represented above.");
			}		

			static TEnum AddFlag(TEnum sourceEnum, TEnum target)
			{
				EXECUTEALLTYPES(AddFlagTo, sourceEnum, target);
				throw gcnew Exception("This should never throw. All underlying types are represented above.");
			}

			static TEnum RemoveFlag(TEnum sourceEnum, TEnum enumFlagToRemove)
			{
				EXECUTEALLTYPES(RemoveFlagFrom, sourceEnum, enumFlagToRemove);
				throw gcnew Exception("This should never throw. All underlying types are represented above.");
			}

			static Boolean EqualsAny(array<TEnum>^ enumValuesToCheck, TEnum sourceEnum)
			{
				auto len = enumValuesToCheck->Length;
				for (int i = 0; i < len; i++) {
					if (enumValuesToCheck[i] == sourceEnum)
						return true;
				}
				return false;
			}
		};
}