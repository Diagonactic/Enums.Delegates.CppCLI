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