#pragma once
using namespace System;
using namespace System::Runtime::CompilerServices;

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
		[MethodImpl(MethodImplOptions::AggressiveInlining)]
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

#define CLOBBERTOTYPETARGETTEMPLATE(type) generic <typename TEnum> where TEnum:IComparable, IFormattable, IConvertible, System::Enum\
			[MethodImpl(MethodImplOptions::AggressiveInlining)] static type ClobberTo##type(TEnum val) { return *reinterpret_cast<type*>(&val); }

		CLOBBERTOTYPETARGETTEMPLATE(Byte)
		CLOBBERTOTYPETARGETTEMPLATE(SByte)
		CLOBBERTOTYPETARGETTEMPLATE(Int16)
		CLOBBERTOTYPETARGETTEMPLATE(UInt16)
		CLOBBERTOTYPETARGETTEMPLATE(Int32)
		CLOBBERTOTYPETARGETTEMPLATE(UInt32)
		CLOBBERTOTYPETARGETTEMPLATE(Int64)
		CLOBBERTOTYPETARGETTEMPLATE(UInt64)
#pragma warning(default:4956 4957)
		
		template <typename TNumber>
		[MethodImpl(MethodImplOptions::AggressiveInlining)]
		static TNumber AddFlagTo(TNumber %enumValue, TNumber %flagToAdd)
		{						
			return enumValue | flagToAdd;
		}


		template <typename TNumber>
		[MethodImpl(MethodImplOptions::AggressiveInlining)]
		static TNumber AddFlagToSpecial(TNumber %enumValue, TNumber %flagToAdd)
		{
			if (flagToAdd <= 0)
				return enumValue;
			
			if (flagToAdd == 0x1 ||	flagToAdd == 0x2 ||	flagToAdd == 0x4 ||	flagToAdd == 0x8 ||
				flagToAdd == 0x10 || flagToAdd == 0x20 || flagToAdd == 0x40)
				return enumValue | flagToAdd;
			if (TNumber::typeid == SByte::typeid)
				return enumValue;
			
			if (flagToAdd == 0x80)
				return enumValue | flagToAdd;
			if (TNumber::typeid == Byte::typeid)
				return enumValue;
			
			if (flagToAdd == 0x100 || flagToAdd == 0x200 ||	flagToAdd == 0x400 || flagToAdd == 0x800 ||
				flagToAdd == 0x1000 || flagToAdd == 0x2000 || flagToAdd == 0x4000)
				return enumValue | flagToAdd;
			if (TNumber::typeid == Int16::typeid)			
				return enumValue;

			if (flagToAdd == 0x8000)
				return enumValue | flagToAdd;
			if (TNumber::typeid == UInt16::typeid)
				return enumValue;

			if (flagToAdd == 0x10000 || flagToAdd == 0x20000 || flagToAdd == 0x40000 || flagToAdd == 0x80000 ||
				flagToAdd == 0x100000 || flagToAdd == 0x200000 || flagToAdd == 0x400000 || flagToAdd == 0x800000 ||
				flagToAdd == 0x1000000 || flagToAdd == 0x2000000 || flagToAdd == 0x4000000 || flagToAdd == 0x8000000 ||
				flagToAdd == 0x10000000 || flagToAdd == 0x20000000 || flagToAdd == 0x40000000)
				return enumValue | flagToAdd;
			if (TNumber::typeid == Int32::typeid)
				return enumValue;

			if (flagToAdd == 0x80000000)
				return enumValue | flagToAdd;
			if (TNumber::typeid == UInt32::typeid)
				return enumValue;

			if (flagToAdd == 0x100000000 || flagToAdd == 0x200000000 || flagToAdd == 0x400000000 || flagToAdd == 0x800000000 ||
				flagToAdd == 0x1000000000 || flagToAdd == 0x2000000000 || flagToAdd == 0x4000000000 || flagToAdd == 0x8000000000 ||
				flagToAdd == 0x10000000000 || flagToAdd == 0x20000000000 || flagToAdd == 0x40000000000 || flagToAdd == 0x80000000000 ||
				flagToAdd == 0x100000000000 || flagToAdd == 0x200000000000 || flagToAdd == 0x400000000000 || flagToAdd == 0x800000000000 ||
				flagToAdd == 0x1000000000000 || flagToAdd == 0x2000000000000 || flagToAdd == 0x4000000000000 || flagToAdd == 0x8000000000000 ||
				flagToAdd == 0x10000000000000 || flagToAdd == 0x20000000000000 || flagToAdd == 0x40000000000000 || flagToAdd == 0x80000000000000 ||
				flagToAdd == 0x100000000000000 || flagToAdd == 0x200000000000000 || flagToAdd == 0x400000000000000 || flagToAdd == 0x800000000000000 ||
				flagToAdd == 0x1000000000000000 || flagToAdd == 0x2000000000000000 || flagToAdd == 0x4000000000000000)
				return enumValue | flagToAdd;
			if (TNumber::typeid == Int64::typeid)
				return enumValue;

			if (flagToAdd == 0x8000000000000000)
				return enumValue | flagToAdd;

			return enumValue;
		}

		template <typename TNumber>
		[MethodImpl(MethodImplOptions::AggressiveInlining)]
		static TNumber RemoveFlagFrom(TNumber enumValue, TNumber flagToAdd)
		{
			return enumValue & ~flagToAdd;
		}

		template <typename TNumber>
		inline static Boolean IsFlagSet(TNumber enumValue, TNumber enumFlagToTest)
		{
			if (enumFlagToTest == enumValue)
				return true;
			if (enumFlagToTest == 0)
				return false;
			return ((enumValue & enumFlagToTest) == enumFlagToTest);
		}
	};
}