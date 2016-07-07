#pragma once

#include "Stdafx.h"
#include "GenericEnumValues.h"
#include "EqualityComparers.h"
#include "NumberMap.h"
#include <cliext\hash_map>

#define NumberMapField(typeName) <typeName>^ s_enum##typeName

#define AssignStaticMapField(type) {															\
	s_comparer = type##EnumEqualityComparer<TEnum>::Default;									\
	s_nameMap = gcnew Dictionary<String^, TEnum>(len, FastStringComparer::Default);				\
	auto values = gcnew array<type>(len);														\
	TEnum enumValue;																			\
	for (int i = 0; i < len; i++)																\
	{																							\
		enumValue = enumValues[i];																\
		values[i] = Util::ClobberTo##type(enumValue);											\
		s_nameMap->Add(names[i], enumValue);													\
	}																							\
	s_caseMap = gcnew Dictionary<String^, TEnum>(s_nameMap, StringComparer::OrdinalIgnoreCase);	\
	s_enum##type = gcnew NumberMap<type>(values, names, UnderlyingKind::type##Kind);			\
}


#define ForAllTypes(valueWithTypeParameter)\
valueWithTypeParameter(Int32);\
valueWithTypeParameter(Int64);\
valueWithTypeParameter(Int16);\
valueWithTypeParameter(Byte);\
valueWithTypeParameter(UInt32);\
valueWithTypeParameter(UInt64);\
valueWithTypeParameter(UInt16);\
valueWithTypeParameter(SByte)

#define ExecuteForType(targetEnumValue, valueWithTypeParameter)		\
switch (targetEnumValue) {											\
	case UnderlyingKind::Int32Kind:									\
		valueWithTypeParameter(Int32);								\
	break;															\
	case UnderlyingKind::UInt32Kind:								\
		valueWithTypeParameter(UInt32);								\
	break;															\
	case UnderlyingKind::Int64Kind:									\
		valueWithTypeParameter(Int64);								\
	break;															\
	case UnderlyingKind::UInt64Kind:								\
		valueWithTypeParameter(UInt64);								\
	break;															\
	case UnderlyingKind::Int16Kind:									\
		valueWithTypeParameter(Int16);								\
	break;															\
	case UnderlyingKind::UInt16Kind:								\
		valueWithTypeParameter(UInt16);								\
	break;															\
	case UnderlyingKind::ByteKind:									\
		valueWithTypeParameter(Byte);								\
	break;															\
	case UnderlyingKind::SByteKind:									\
		valueWithTypeParameter(SByte);								\
	break;															\
}



ref class GenericEnumValues;
enum UnderlyingKind : char;
ref class MsilConvert;
using namespace System;
using namespace System::Collections::Generic;
using namespace System::Text;
using namespace System::Runtime::InteropServices;
using namespace System::Runtime::CompilerServices;
using namespace System::Diagnostics;
using namespace System::Collections::ObjectModel;
using namespace System::Linq;
using namespace cliext;

namespace Diagonactic {

	GenericEnumType	private ref class GenericNumericEnumCore abstract : GenericEnumValues<TEnum>
	{
	private:
		static GenericNumericEnumCore() {
			Int32 len = s_length;
			array<String^>^ names = Enum::GetNames(s_type);
			auto enumValues = s_values;
			
			ExecuteForType(s_kind, AssignStaticMapField);
						
			len = s_length;
		}

	internal:
#define AsStringByType(type) s_enum##type->AsString(Util::ClobberTo##type(value));
		static String^ AsString(TEnum value) {
			switch (s_kind) {
			case UnderlyingKind::Int16Kind: return AsStringByType(Int16);
			case UnderlyingKind::Int32Kind: return AsStringByType(Int32);
			case UnderlyingKind::Int64Kind: return AsStringByType(Int64);
			case UnderlyingKind::UInt32Kind: return AsStringByType(UInt32);
			case UnderlyingKind::UInt64Kind: return AsStringByType(UInt64);
			case UnderlyingKind::UInt16Kind: return AsStringByType(UInt16);
			case UnderlyingKind::ByteKind: return AsStringByType(Byte);
			case UnderlyingKind::SByteKind: return AsStringByType(SByte);
			}
			throw gcnew Exception("Underlying is not supported");
		}

		static Boolean GetValueFromString(String ^value, Boolean ignoreCase, Boolean throwOnFail, [Out] TEnum %result)
		{			
			if (!(ignoreCase ? s_caseMap->TryGetValue(value, result) : s_nameMap->TryGetValue(value, result)))
				return ThrowOrDefaultEnum(throwOnFail);
			return true;
		}

		static List<TEnum>^ ToList() { return gcnew List<TEnum>(s_nameMap->Values); }

		static List<TEnum>^ ToList(TEnum value)
		{
			List<TEnum>^ retVal = gcnew List<TEnum>();
			for each(TEnum item in s_nameMap->Values)
			{
				if (item == s_defaultValue)
					continue;

				if (GenericEnumMinimal<TEnum>::IsFlagSet(value, item))
					retVal->Add(item);
			}

			return retVal;
		}

		static array<String^>^ GetNames()
		{
			return Enumerable::ToArray(s_nameMap->Keys);
		}

		static array<TEnum>^ ToArray() 
		{
			array<TEnum>^ result = (array<TEnum>^)Array::CreateInstance(TEnum::typeid, s_values->Length);
			int i = 0;
			for each(auto val in s_nameMap->Values) {
				result[i] = val;
				i++;
			}
			return result;
		}

#define PARSEPART(type) case UnderlyingKind::type##Kind: {\
	##type value##type = 0;\
	do {\
		i--;\
		String ^part = parts[i];\
		bool needsTrim = (Char::IsWhiteSpace(part[0]) || Char::IsWhiteSpace(part[part->Length - 1]));\
		if (!GetValueFromString(needsTrim ? part->Trim() : part, ignoreCase, throwOnFail, result)) \
		{\
			result = s_defaultValue;\
			return ThrowOrDefaultEnum(throwOnFail);\
		}\
		value##type |= Util::ClobberTo##type(result);\
	} while(i!=0);\
	result = MsilConvert::ClobberFrom<TEnum>(value##type);\
	return true;\
}
		static Boolean ParseEnum(String ^value, Boolean ignoreCase, Boolean throwOnFail, [Out] TEnum %result)
		{
			if (!value->Contains(","))
				return GetValueFromString(value, ignoreCase, throwOnFail, result);

			array<String^> ^parts = value->Split(Util::s_Split, StringSplitOptions::RemoveEmptyEntries);

			int i = parts->Length;

			switch (s_kind) {
				PARSEPART(Int32)
					PARSEPART(Int64)
					PARSEPART(Int16)
					PARSEPART(UInt32)
					PARSEPART(UInt64)
					PARSEPART(UInt16)
					PARSEPART(Byte)
					PARSEPART(SByte)
			}
			throw gcnew Exception("Underlying Kind is not supported");
		}

		inline static Boolean ThrowOrDefaultEnum(Boolean throwException) {
			if (throwException)
				throw gcnew ArgumentException("There is no key matching provided value", "value");
			return false;
		}



		static Dictionary<String^, TEnum>^ s_nameMap;
		static Dictionary<String^, TEnum>^ s_caseMap;
		static IEqualityComparer<TEnum>^ s_comparer;		
		static NumberMap NumberMapField(Int16);
		static NumberMap NumberMapField(UInt16);
		static NumberMap NumberMapField(Int32);
		static NumberMap NumberMapField(UInt32);
		static NumberMap NumberMapField(Int64);
		static NumberMap NumberMapField(UInt64);
		static NumberMap NumberMapField(Byte);
		static NumberMap NumberMapField(SByte);
	};


}

