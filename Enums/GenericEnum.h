#pragma once
#include "Stdafx.h"
#include "GenericEnumValues.h"
#include "NumberMap.h"
#include "MsilConvert.h"

using namespace System;

namespace Diagonactic
{
	GenericEnumType private ref class GenericEnum
	{
	internal:
		SByte SByteVal;
		Byte ByteVal;
		Int16 Int16Val;
		UInt16 UInt16Val;
		Int32 Int32Val;
		UInt32 UInt32Val;
		Int64 Int64Val;
		UInt64 UInt64Val;

	public:
#define Assign(type, fromValue) case UnderlyingKind::type##Kind: type##Val = Util::ClobberTo##type(fromValue); break;
#define Return(type) case UnderlyingKind::type##Kind: return MsilConvert::ClobberFrom<TEnum>(type##Val);
#define ReturnValue \
		switch (EnumKind)\
		{\
			Return(Byte)\
		Return(SByte)\
		Return(Int16)\
		Return(UInt16)\
		Return(Int32)\
		Return(UInt32)\
		Return(Int64)\
		Return(UInt64)\
		default: ThrowEnumUnderlyingValueInvalid break;\
		}

		GenericEnum(TEnum value)
		{
			switch(EnumKind)
			{
				Assign(Byte, value)
				Assign(SByte, value)
				Assign(Int16, value)
				Assign(UInt16, value)
				Assign(Int32, value)
				Assign(UInt32, value)
				Assign(Int64, value)
				Assign(UInt64, value)
			}
		}

		TEnum ToValue()
		{
			ReturnValue
		}
#define PerformOpEach(type, var2, op)\
		case UnderlyingKind::type##Kind: {\
			type val = type##Val op var2->type##Val;\
			return MsilConvert::ClobberFrom<TEnum>(val);\
		}
#define PerformOp(var2, op) \
		switch (EnumKind) \
		{ \
			PerformOpEach(Byte, var2, op)\
		PerformOpEach(SByte, var2, op)\
		PerformOpEach(Int16, var2, op)\
		PerformOpEach(UInt16, var2, op)\
		PerformOpEach(Int32, var2, op)\
		PerformOpEach(UInt32, var2, op)\
		PerformOpEach(Int64, var2, op)\
		PerformOpEach(UInt64, var2, op)\
		}

		TEnum Caret(GenericEnum<TEnum>^ item2)
		{
			PerformOp(item2, ^);
		}		
		
		static GenericEnum<TEnum>^ operator ^(const GenericEnum<TEnum>^ item1, const GenericEnum<TEnum>^ item2){			
			return gcnew GenericEnum<TEnum>(item1->Caret(item2));
		}

	};

}
	