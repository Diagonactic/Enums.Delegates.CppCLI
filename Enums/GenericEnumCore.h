#pragma once

#include "Stdafx.h"
#include "GenericEnumValues.h"
#include "EqualityComparers.h"
#include <cliext\hash_map>

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
	
	generic<typename TEnum> where TEnum : IComparable, IFormattable, IConvertible, System::Enum
	private ref class GenericEnumCore : public GenericEnumValues<TEnum>
	{
		
	private:
		
		static GenericEnumCore()
		{	
			//s_enumMap = gcnew Dictionary<TEnum, String^>(s_length);
			
			switch (s_kind) {
			case UnderlyingKind::ByteKind: {
				s_comparer = gcnew ByteEnumEqualityComparer<TEnum>();
				s_enumMap = gcnew Dictionary<TEnum, String^>(s_length, s_comparer);
				break;
			}
			case UnderlyingKind::SByteKind: {
				s_comparer = gcnew SByteEnumEqualityComparer<TEnum>();
				s_enumMap = gcnew Dictionary<TEnum, String^>(s_length, s_comparer);
				break;
			}
			case UnderlyingKind::Int16Kind: {
				s_comparer = gcnew Int16EnumEqualityComparer<TEnum>();
				s_enumMap = gcnew Dictionary<TEnum, String^>(s_length, s_comparer);
				break;
			}
			case UnderlyingKind::UInt16Kind: {
				s_comparer = gcnew UInt16EnumEqualityComparer<TEnum>();
				s_enumMap = gcnew Dictionary<TEnum, String^>(s_length, s_comparer);
				break;
			}
			case UnderlyingKind::Int32Kind: {
				s_comparer = gcnew Int32EnumEqualityComparer<TEnum>();
				s_enumMap = gcnew Dictionary<TEnum, String^>(s_length, s_comparer);
				break;
			}
			case UnderlyingKind::UInt32Kind: {
				s_comparer = gcnew UInt32EnumEqualityComparer<TEnum>();
				s_enumMap = gcnew Dictionary<TEnum, String^>(s_length, s_comparer);
				break;
			}
			case UnderlyingKind::Int64Kind: {
				s_comparer = gcnew Int64EnumEqualityComparer<TEnum>();
				s_enumMap = gcnew Dictionary<TEnum, String^>(s_length, s_comparer);
				break;
			}
			case UnderlyingKind::UInt64Kind: {
				s_comparer = gcnew UInt64EnumEqualityComparer<TEnum>();
				s_enumMap = gcnew Dictionary<TEnum, String^>(s_length, s_comparer);
				break;
			}
			}
			
			auto values = s_values;
			array<String^>^ names = Enum::GetNames(s_type);
			for (Int32 i = 0; i < s_length; i++)
			{
				s_nameMap->Add(names[i], s_values[i]);
				s_enumMap->Add(s_values[i], names[i]);
				try
				{
					s_caseMap->Add(names[i], names[i]);
				}
				catch(ArgumentException^)
				{
					
				}				
			}			
		}		

		[MethodImpl(MethodImplOptions::AggressiveInlining)]
		static Boolean ThrowOrDefaultEnum(Boolean throwException)
		{
			if (throwException)
				throw gcnew ArgumentException("There is no key matching provided value", "value");
			return false;
		}

		[MethodImpl(MethodImplOptions::AggressiveInlining)]
		static Boolean GetValueFromString(String ^value, Boolean ignoreCase, Boolean throwOnFail, [Out] TEnum %result)
		{
			if (!ignoreCase)
			{
				if (s_nameMap->TryGetValue(value, result))
					return true;
				
				return ThrowOrDefaultEnum(throwOnFail);
			}

			String^ keyVal;
			if (s_caseMap->TryGetValue(value, keyVal))
			{
				result = s_nameMap[keyVal];
				return true;
			}				

			return ThrowOrDefaultEnum(throwOnFail);
		}

	internal:
		static Dictionary<TEnum, String^> ^s_enumMap;
		static Dictionary<String^, TEnum> ^s_nameMap = gcnew Dictionary<String^, TEnum>(s_length, Comparers::s_stringComparer);
		static Dictionary<String^, String^> ^s_caseMap = gcnew Dictionary<String^, String^>(s_length, StringComparer::OrdinalIgnoreCase);		
		static IEqualityComparer<TEnum>^ s_comparer;

		static array<String^>^ GetNames()
		{			
			return Enumerable::ToArray(s_enumMap->Values);
		}

		static String^ AsString(TEnum value)
		{
			String ^retVal;
			if (s_enumMap->TryGetValue(value, retVal))
				return retVal;

			StringBuilder ^result = gcnew StringBuilder();

			for (int i = 0; i < s_length; i++)
			{
				if (s_values[i] == s_defaultValue)
					continue;
				if (Util::IsFlagSet(value, s_values[i], s_kind))
					result->Append(s_enumMap[s_values[i]])->Append(", ");
			}

			return (result->Length > 2) ? result->ToString(0, result->Length - 2) : value->ToString();
		}		
		
		static List<TEnum>^ ToList(TEnum value)
		{
			List<TEnum>^ retVal = gcnew List<TEnum>();
			for each(TEnum item in s_enumMap->Keys)
			{
				if (item == s_defaultValue)
					continue;

				if (Util::IsFlagSet(value, item, s_kind))
					retVal->Add(item);
			}

			return retVal;
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
		}
	};
}
