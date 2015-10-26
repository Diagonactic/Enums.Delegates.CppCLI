#pragma once
#include "Stdafx.h"
#using <C:\Program Files (x86)\Reference Assemblies\Microsoft\Framework\.NETCore\v4.5\System.Linq.Dll>

ref class GenericEnumValuesBase;
enum UnderlyingKind : char;

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Text;
using namespace System::Runtime::InteropServices;
using namespace System::Runtime::CompilerServices;
using namespace System::Diagnostics;
using namespace System::Collections::ObjectModel;
using namespace System::Linq;

namespace Diagonactic {
		
	generic<typename TEnum> where TEnum : IComparable, IFormattable, IConvertible, System::Enum
	private ref class GenericEnumCore : public GenericEnumValuesBase<TEnum>
	{

	private:

		static GenericEnumCore()
		{			
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
		static Dictionary<TEnum, String^> ^s_enumMap = gcnew Dictionary<TEnum, String^>(s_length);
		static Dictionary<String^, TEnum> ^s_nameMap = gcnew Dictionary<String^, TEnum>(s_length);
		static Dictionary<String^, String^> ^s_caseMap = gcnew Dictionary<String^, String^>(s_length, StringComparer::OrdinalIgnoreCase);		
		
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

			for each(TEnum item in s_enumMap->Keys)
			{
				if (item == s_defaultValue)
					continue;

				if (Util::IsFlagSet(value, item, s_kind))
					result->Append(s_enumMap[item] + ", ");
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

		static Boolean ParseEnum(String ^value, Boolean ignoreCase, Boolean throwOnFail, [Out] TEnum %result)
		{
			if (!value->Contains(","))
				return GetValueFromString(value, ignoreCase, throwOnFail, result);				
			
			array<String^> ^parts = value->Split(Util::s_Split, StringSplitOptions::RemoveEmptyEntries);

			SByte sbVal = 0;
			Byte bVal = 0;
			Int32 iVal = 0;
			Int64 i64Val = 0;
			UInt32 ui32Val = 0;
			UInt64 ui64Val = 0;
			Int16 i16Val = 0;
			UInt16 ui16Val = 0;

			TEnum valToAdd;
			int endTest = parts->Length;
			for (int i = 0; i != endTest; i++)
			{
				String ^part = parts[i];
				bool needsTrim = (Char::IsWhiteSpace(part[0]) || Char::IsWhiteSpace(part[part->Length - 1]));

				if (!GetValueFromString(needsTrim ? part->Trim() : part, ignoreCase, throwOnFail, valToAdd))
				{
					result = s_defaultValue;
					return ThrowOrDefaultEnum(throwOnFail);
				}

				switch(s_kind)
				{
					case UnderlyingKind::Int32Kind:	 Util::AddFlag(iVal, valToAdd);    break;
					case UnderlyingKind::UInt32Kind: Util::AddFlag(ui32Val, valToAdd); break;
					case UnderlyingKind::Int64Kind:  Util::AddFlag(i64Val, valToAdd);  break;
					case UnderlyingKind::UInt64Kind: Util::AddFlag(ui64Val, valToAdd); break;
					case UnderlyingKind::Int16Kind:  Util::AddFlag(i16Val, valToAdd);  break;
					case UnderlyingKind::UInt16Kind: Util::AddFlag(ui16Val, valToAdd); break;
					case UnderlyingKind::ByteKind:   Util::AddFlag(bVal, valToAdd);    break;
					case UnderlyingKind::SByteKind:  Util::AddFlag(sbVal, valToAdd);   break;

					default: throw gcnew Exception("This should never throw. All underlying types are represented above.");
				}				
			}

			switch (s_kind)
			{
				case UnderlyingKind::Int32Kind:	 result = (TEnum)Enum::ToObject(TEnum::typeid, iVal);    break;
				case UnderlyingKind::UInt32Kind: result = (TEnum)Enum::ToObject(TEnum::typeid, ui32Val); break;
				case UnderlyingKind::Int64Kind:  result = (TEnum)Enum::ToObject(TEnum::typeid, i64Val);  break;
				case UnderlyingKind::UInt64Kind: result = (TEnum)Enum::ToObject(TEnum::typeid, ui64Val); break;
				case UnderlyingKind::Int16Kind:  result = (TEnum)Enum::ToObject(TEnum::typeid, i16Val);  break;
				case UnderlyingKind::UInt16Kind: result = (TEnum)Enum::ToObject(TEnum::typeid, ui16Val); break;
				case UnderlyingKind::ByteKind:   result = (TEnum)Enum::ToObject(TEnum::typeid, bVal);    break;
				case UnderlyingKind::SByteKind:  result = (TEnum)Enum::ToObject(TEnum::typeid, sbVal);   break;

				default: throw gcnew Exception("This should never throw. All underlying types are represented above.");
			}

			return true;
		}
	};
}
