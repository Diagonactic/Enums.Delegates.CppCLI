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
		static TNumber AddFlagTo(TNumber enumValue, TNumber flagToAdd)
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
			return (enumValue & enumFlagToTest) == enumFlagToTest;
		}

		generic <typename TEnum>
			where TEnum:IComparable, IFormattable, IConvertible, System::Enum
		static Boolean IsFlagSet(TEnum enumSource, TEnum enumFlagToTest, UnderlyingKind kind)
		{
			switch(kind)
			{
				case UnderlyingKind::Int32Kind:  return IsFlagSet(ClobberToInt32<TEnum>(enumSource), ClobberToInt32<TEnum>(enumFlagToTest));
				case UnderlyingKind::SByteKind:  return IsFlagSet(ClobberToSByte<TEnum>(enumSource), ClobberToSByte<TEnum>(enumFlagToTest));
				case UnderlyingKind::ByteKind:   return IsFlagSet(ClobberToByte<TEnum>(enumSource), ClobberToByte<TEnum>(enumFlagToTest));
				case UnderlyingKind::UInt32Kind: return IsFlagSet(ClobberToUInt32<TEnum>(enumSource), ClobberToUInt32<TEnum>(enumFlagToTest));
				case UnderlyingKind::Int64Kind:  return IsFlagSet(ClobberToInt64<TEnum>(enumSource), ClobberToInt64<TEnum>(enumFlagToTest));
				case UnderlyingKind::Int16Kind:  return IsFlagSet(ClobberToInt16<TEnum>(enumSource), ClobberToInt16<TEnum>(enumFlagToTest));
				case UnderlyingKind::UInt16Kind: return IsFlagSet(ClobberToUInt16<TEnum>(enumSource), ClobberToUInt16<TEnum>(enumFlagToTest));
				case UnderlyingKind::UInt64Kind: return IsFlagSet(ClobberToUInt64<TEnum>(enumSource), ClobberToUInt64<TEnum>(enumFlagToTest));
			}
				
			throw gcnew InvalidOperationException("Failed to determine underlying type when detecting whether or not flag was set");
		}
	};
}