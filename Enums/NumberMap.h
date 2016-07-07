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




namespace Diagonactic {
	template <typename TNumber>
	ref class NumberMap {
	internal:
		Dictionary<TNumber, String^>^ s_valueMap;
		Int32 s_length;
		array<TNumber>^ s_values;

		NumberMap(array<TNumber>^ values, array<String^>^ names, UnderlyingKind kind) {
			s_values = values;
			s_length = values->Length;
			auto len = s_length;
			if (kind == UnderlyingKind::Int64Kind || kind == UnderlyingKind::UInt64Kind)
				s_valueMap = gcnew Dictionary<TNumber, String^>(len, EqualityComparer<TNumber>::Default);
			else
				s_valueMap = gcnew Dictionary<TNumber, String^>(len, EqualityComparer<TNumber>::Default);

			do {
				len--;
				if (!s_valueMap->ContainsKey(values[len]))
					s_valueMap->Add(values[len], names[len]);
			} while (len != 0);
		}

		inline Boolean GetValueFromString(String ^value, Boolean ignoreCase, Boolean throwOnFail, TNumber %result)
		{
			return TryGetSingleValue(value, ignoreCase, result) ? true : ThrowOrDefaultEnum(throwOnFail);
		}

		inline Boolean TryGetSingleValue(String^ key, bool ignoreCase, [Out]TNumber %result)
		{
			return ignoreCase ? s_nameMap->TryGetValue(key, result) : s_nameCasedMap->TryGetValue(key, result);
		}

		inline static Boolean ThrowOrDefaultEnum(Boolean throwException) {
			if (throwException)
				throw gcnew ArgumentException("There is no key matching provided value", "value");
			return false;
		}

		String^ AsString(TNumber value) {
			String ^retVal;
			if (s_valueMap->TryGetValue(value, retVal))
				return retVal;

			StringBuilder ^result = gcnew StringBuilder();

			int len = s_length;
			do {
				len--;
				TNumber flagToTest = s_values[len];
				if (flagToTest == 0)
					continue;
				if ((value & flagToTest) == flagToTest)
					result->Insert(0, s_valueMap[flagToTest])->Insert(0, ", ");
			} while (len != 0);

			return (result->Length > 2) ? result->ToString(2, result->Length - 2) : value.ToString();
		}
	};
}