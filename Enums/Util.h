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

		template < class T, class U > 
		inline static Boolean IsType(U u) { return dynamic_cast<T>(u) != nullptr;	}
		
		GenericEnumType	inline static UnderlyingKind GetKind();
		GenericEnumType inline static SByte ClobberToSByte(TEnum value);
		GenericEnumType inline static Byte ClobberToByte(TEnum value);
		GenericEnumType inline static Int16 ClobberToInt16(TEnum value);
		GenericEnumType inline static UInt16 ClobberToUInt16(TEnum value);
		GenericEnumType inline static Int32 ClobberToInt32(TEnum value);
		GenericEnumType inline static UInt32 ClobberToUInt32(TEnum value);
		GenericEnumType inline static Int64 ClobberToInt64(TEnum value);
		GenericEnumType inline static UInt64 ClobberToUInt64(TEnum value);

		
		template <typename TNumber>	inline static TNumber AddFlagTo(TNumber %enumValue, TNumber %flagToAdd) { return enumValue | flagToAdd;	}
		template <typename TNumber> inline static TNumber RemoveFlagFrom(TNumber enumValue, TNumber flagToAdd)	{ return enumValue & ~flagToAdd; }

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

		template <typename TNumber>	inline static Boolean IsFlagSet(TNumber enumValue, TNumber enumFlagToTest)
		{
			if (enumFlagToTest == enumValue)
				return true;
			if (enumFlagToTest == 0)
				return false;
			return ((enumValue & enumFlagToTest) == enumFlagToTest);
		}
	};
}