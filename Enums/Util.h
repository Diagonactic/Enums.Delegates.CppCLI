#pragma once
#include "MsilConvert.h"

using namespace System;

enum UnderlyingKind : char
{
	Unknown, Int32Kind, ByteKind, SByteKind, Int16Kind, Int64Kind, UInt16Kind, UInt32Kind, UInt64Kind
};

namespace Diagonactic
{
	private ref class Util sealed abstract
	{
	private:
		static Util()
		{
			s_Split[0] = ',';
		}

	internal:
		static array<Char> ^s_Split = gcnew array<Char>(1);
		


		generic <typename TEnum> 
			where TEnum:IComparable, IFormattable, IConvertible, System::Enum
		static UnderlyingKind GetKind(TEnum)
		{
			auto uKind = Enum::GetUnderlyingType(TEnum::typeid);
			if (uKind == Int32::typeid)
				return UnderlyingKind::Int32Kind;
			if (uKind == UInt32::typeid)
				return UnderlyingKind::UInt32Kind;
			if (uKind == Byte::typeid)
				return UnderlyingKind::ByteKind;
			if (uKind == SByte::typeid)
				return UnderlyingKind::SByteKind;
			if (uKind == Int16::typeid)
				return UnderlyingKind::Int16Kind;
			if (uKind == UInt16::typeid)
				return UnderlyingKind::UInt16Kind;
			if (uKind == Int64::typeid)
				return UnderlyingKind::Int64Kind;
			if (uKind == UInt64::typeid)
				return UnderlyingKind::UInt64Kind;

			throw gcnew NotSupportedException("Type " + (uKind::typeid)->ToString() + " is not supported");
		}

#pragma warning(disable:4956 4957)
		template <typename TNumber>	static TNumber ClobberTo(void* enumVal)
		{
			return *reinterpret_cast<TNumber*>(enumVal);
		}

		template <typename TNumber>	static TNumber RemoveFlag(void* enumValue, void* flagToAdd)
		{
			return ClobberTo<TNumber>(enumValue) & ~ClobberTo<TNumber>(flagToAdd);
		}

		template <typename TNumber>	static TNumber AddFlagTo(void* enumValue, void* flagToAdd)
		{
			return ClobberTo<TNumber>(enumValue) | ClobberTo<TNumber>(flagToAdd);
		}

		generic <typename TEnum> where TEnum:IComparable, IFormattable, IConvertible, System::Enum
		static Byte ClobberToByte(TEnum val) { return *reinterpret_cast<Byte*>(&val); }

		generic <typename TEnum> where TEnum:IComparable, IFormattable, IConvertible, System::Enum
		static SByte ClobberToSByte(TEnum val) { return *reinterpret_cast<SByte*>(&val); }

		generic <typename TEnum> where TEnum:IComparable, IFormattable, IConvertible, System::Enum
		static Int16 ClobberToInt16(TEnum val) { return *reinterpret_cast<Int16*>(&val); }

		generic <typename TEnum> where TEnum:IComparable, IFormattable, IConvertible, System::Enum
		static UInt16 ClobberToUInt16(TEnum val) { return *reinterpret_cast<UInt16*>(&val);	}

		generic <typename TEnum> where TEnum:IComparable, IFormattable, IConvertible, System::Enum		
		static Int32 ClobberToInt32(TEnum val) { return *reinterpret_cast<Int32*>(&val); }
		
		generic <typename TEnum> where TEnum:IComparable, IFormattable, IConvertible, System::Enum
		static UInt32 ClobberToUInt32(TEnum val) { return *reinterpret_cast<UInt32*>(&val);	}

		generic <typename TEnum> where TEnum:IComparable, IFormattable, IConvertible, System::Enum
		static Int64 ClobberToInt64(TEnum val)	{ return *reinterpret_cast<Int64*>(&val); }
		
		generic <typename TEnum> where TEnum:IComparable, IFormattable, IConvertible, System::Enum
		static UInt64 ClobberToUInt64(TEnum val) { return *reinterpret_cast<UInt64*>(&val);	}

#pragma warning(default:4956 4957)
		
//--------------------------------------------------------------------------------------------------------------------------------------------------------------- Add Flags
		template <typename TNumber> static TNumber AddFlags(void* currentEnum, void* values)
		{
			TNumber result = ClobberTo<TNumber>(currentEnum);
			array<TNumber>^ vals = ClobberTo<array<TNumber>^>(values);
			for (Int32 i = 0; i < vals->Length; i++)
				result |= vals[i];
			return result;
		}
		template <typename TNumber> static TNumber RemoveFlags(void* currentEnum, void* values)
		{
			TNumber result = ClobberTo<TNumber>(currentEnum);
			array<TNumber>^ vals = ClobberTo<array<TNumber>^>(values);
			for (Int32 i = 0; i < vals->Length; i++)
				result &= ~vals[i];
			return result;
		}

		template <typename TNumber>	static Boolean IsFlagSet(void* enumValue, void* enumFlagToTest)
		{
			TNumber flag = ClobberTo<TNumber>(enumFlagToTest);
			return ((ClobberTo<TNumber>(enumValue) & flag) == flag);
		}

		template <typename TNumber>	static Boolean AreAllFlagsSet(void* enumValue, void* enumFlagToTest)
		{
			array<TNumber>^ flags = ClobberTo<array<TNumber>^>(enumFlagToTest);
			for (Int32 i = 0; i < flags->Length; i++)
				if (!((ClobberTo<TNumber>(enumValue) & flags[i]) == flags[i]))
					return false;
			return true;			
		}

		template <typename TNumber>	static Boolean AreAnyFlagsSet(void* enumValue, void* enumFlagToTest)
		{
			array<TNumber>^ flags = ClobberTo<array<TNumber>^>(enumFlagToTest);
			auto value = ClobberTo<TNumber>(enumValue);
			for (Int32 i = 0; i < flags->Length; i++)
				if ((value & flags[i]) == flags[i])
					return true;
			return false;
		}

		generic <typename TEnum>
			where TEnum:IComparable, IFormattable, IConvertible, System::Enum
		static Boolean IsFlagSet(TEnum enumSource, TEnum enumFlagToTest, UnderlyingKind kind)
		{
			pin_ptr<TEnum> source(&enumSource);
			pin_ptr<TEnum> enumToTest(&enumFlagToTest);
			switch(kind)
			{
				case UnderlyingKind::Int32Kind:  return IsFlagSet<Int32>(source, enumToTest);
				case UnderlyingKind::SByteKind:  return IsFlagSet<SByte>(source, enumToTest);
				case UnderlyingKind::ByteKind:   return IsFlagSet<Byte>(source, enumToTest);
				case UnderlyingKind::UInt32Kind: return IsFlagSet<UInt32>(source, enumToTest);
				case UnderlyingKind::Int64Kind:  return IsFlagSet<Int64>(source, enumToTest);
				case UnderlyingKind::Int16Kind:  return IsFlagSet<Int16>(source, enumToTest);
				case UnderlyingKind::UInt16Kind: return IsFlagSet<UInt16>(source, enumToTest);
				case UnderlyingKind::UInt64Kind: return IsFlagSet<UInt64>(source, enumToTest);
			}
				
			throw gcnew InvalidOperationException("Failed to determine underlying type when detecting whether or not flag was set");
		}
	};
}