#pragma once
#include "EqualityComparers.h"
#include "GenericEnumValues.h"

enum UnderlyingKind : char;
ref class Util;
ref class GenericEnumValues;
using namespace System;
using namespace System::Collections::Generic;
using namespace System::Runtime::InteropServices;
using namespace System::Text;

#define AssignStaticMapField(type) {\
auto enumValues = s_values;\
auto values = gcnew array<type>(len);\
do {\
	len--;\
	values[len] = Util::ClobberTo##type(enumValues[len]);\
} while(len != 0);\
s_enum##type = gcnew NumberMap<type>(values, names);\
}


#define ForAllTypes(valueWithTypeParameter)\
valueWithTypeParameter(Int32);\
valueWithTypeParameter(Int64);\
valueWithTypeParameter(Int16);\
valueWithTypeParameter(Byte);\
valueWithTypeParameter(UInt32); \
valueWithTypeParameter(UInt64); \
valueWithTypeParameter(UInt16); \
valueWithTypeParameter(SByte)

#define ExecuteForType(targetEnumValue, valueWithTypeParameter)\
switch (targetEnumValue) {\
	case UnderlyingKind::Int32Kind:\
		valueWithTypeParameter(Int32);\
	break;\
	case UnderlyingKind::UInt32Kind:\
		valueWithTypeParameter(UInt32);\
	break;\
	case UnderlyingKind::Int64Kind:\
		valueWithTypeParameter(Int64);\
	break;\
	case UnderlyingKind::UInt64Kind:\
		valueWithTypeParameter(UInt64);\
	break;\
	case UnderlyingKind::Int16Kind:\
		valueWithTypeParameter(Int16);\
	break;\
	case UnderlyingKind::UInt16Kind:\
		valueWithTypeParameter(UInt16);\
	break;\
	case UnderlyingKind::ByteKind:\
		valueWithTypeParameter(Byte);\
	break;\
	case UnderlyingKind::SByteKind:\
		valueWithTypeParameter(SByte);\
	break;\
}

namespace Diagonactic {
	template <typename TNumber>	
	ref class NumberMap {
	internal:
		Dictionary<String^, TNumber>^ s_nameCasedMap;
		Dictionary<String^, TNumber>^ s_nameMap;
		Dictionary<TNumber, String^>^ s_valueMap;
		Int32 s_length;
		array<TNumber>^ s_values;

		NumberMap(array<TNumber>^ values, array<String^>^ names) {
			s_values = values;
			s_length = values->Length;
			auto len = s_length;
			s_nameCasedMap = gcnew Dictionary<String^, TNumber>(len, Comparers::s_stringComparer);
			s_valueMap = gcnew Dictionary<TNumber, String^>(len);
			do {
				len--;
				auto name = names[len];
				auto value = values[len];
				s_nameCasedMap->Add(name, value);
				s_valueMap->Add(value, name);
			} while (len != 0);

			s_nameMap = gcnew Dictionary<String^, TNumber>(s_nameCasedMap, StringComparer::OrdinalIgnoreCase);
		}

		inline Boolean TryGetSingleName(TNumber key, [Out]String^ %result) { return s_valueMap->TryGetValue(key, result); }

		inline Boolean GetValueFromString(String ^value, Boolean ignoreCase, Boolean throwOnFail, [Out] TNumber %result) { 
			return ThrowOrDefaultEnum(TryGetSingleValue(value, ignoreCase, result), throwOnFail); 
		}
			
		inline Boolean TryGetSingleValue(String^ key, bool ignoreCase, [Out]TNumber %result) { return ignoreCase ? s_nameMap->TryGetValue(key, result) : s_nameCasedMap->TryGetValue(key, result); }
		
		inline static Boolean ThrowOrDefaultEnum(Boolean success, Boolean throwException) {
			if (success) return true;

			if (throwException)
				throw gcnew ArgumentException("There is no key matching provided value", "value");
			return false;
		}

		String^ AsString(TNumber value) {
			String ^retVal;
			if (TryGetSingleName(value, retVal))
				return retVal;

			StringBuilder ^result = gcnew StringBuilder();

			int len = s_length;
			do {
				len--;
				TNumber flagToTest = s_values[len];
				if (value == 0)
					continue;
				if ((value & flagToTest) == flagToTest)
					result->Append(s_valueMap[flagToTest])->Append(", ");
			} while (len != 0);

			return (result->Length > 2) ? result->ToString(0, result->Length - 2) : value.ToString();
		}

		Boolean Parse(String^ value, Boolean ignoreCase, Boolean throwOnFail, [Out] TNumber %result) {
			if (!value->Contains(","))
				return GetValueFromString(value, ignoreCase, throwOnFail, result);

			array<String^> ^parts = value->Split(Util::s_Split, StringSplitOptions::RemoveEmptyEntries);

			int i = parts->Length;

			do {
				i--;
				String ^part = parts[i];
				bool needsTrim = (Char::IsWhiteSpace(part[0]) || Char::IsWhiteSpace(part[part->Length - 1])); 
				
				if (!GetValueFromString(needsTrim ? part->Trim() : part, ignoreCase, throwOnFail, result)) 
				{
					result = 0; 
					return ThrowOrDefaultEnum(false, throwOnFail); 
				}

				result |= result; 
			} while(i != 0);

			return true;
		}		
	};

	generic<typename TEnum> where TEnum : IComparable, IFormattable, IConvertible, System::Enum
	private ref class GenericNumericEnumCore abstract : GenericEnumValues<TEnum>
	{
	private:
		static GenericNumericEnumCore() {
			Int32 len = s_length; 
			array<String^>^ names = Enum::GetNames(s_type);

			ExecuteForType(s_kind, AssignStaticMapField);
			
			s_names = names;
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
		}

#define ParseEnumByType(type) {\
			type numResult = 0;\
			Boolean success = s_enum##type->Parse(value, ignoreCase, throwOnFail, numResult);\
			if (success) result = MsilConvert::ClobberFrom<TEnum>(numResult);\
			return success;\
		}
		static Boolean ParseEnum(String ^value, Boolean ignoreCase, Boolean throwOnFail, [Out] TEnum %result) {
			switch (s_kind) {
			case UnderlyingKind::Int16Kind: ParseEnumByType(Int16);
			case UnderlyingKind::Int32Kind: ParseEnumByType(Int32);
			case UnderlyingKind::Int64Kind: ParseEnumByType(Int64);
			case UnderlyingKind::UInt32Kind: ParseEnumByType(UInt32);
			case UnderlyingKind::UInt64Kind: ParseEnumByType(UInt64);
			case UnderlyingKind::UInt16Kind: ParseEnumByType(UInt16);
			case UnderlyingKind::ByteKind: ParseEnumByType(Byte);
			case UnderlyingKind::SByteKind: ParseEnumByType(SByte);
			}
		}

		static array<String^>^ s_names;
		static NumberMap<Int16>^ s_enumInt16;
		static NumberMap<UInt16>^ s_enumUInt16;
		static NumberMap<Int32>^ s_enumInt32;
		static NumberMap<UInt32>^ s_enumUInt32;
		static NumberMap<Int64>^ s_enumInt64;
		static NumberMap<UInt64>^ s_enumUInt64;
		static NumberMap<Byte>^ s_enumByte;
		static NumberMap<SByte>^ s_enumSByte;
	};

	
}
