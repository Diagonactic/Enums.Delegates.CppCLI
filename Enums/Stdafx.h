// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently,
// but are changed infrequently

#pragma once
#include "Util.h"

#using <C:\Src\EnumCpp\External Dependencies\JetBrains.Annotations.PCL328.dll>
#using <C:\Program Files (x86)\Reference Assemblies\Microsoft\Framework\.NETCore\v4.5\System.Linq.Dll>

#define GenericEnumTypeConstraint(name) where name : IComparable, IFormattable, IConvertible, System::Enum, value class
#define GenericEnumTypeName(name) generic <typename name> GenericEnumTypeConstraint(name)
#define GenericEnumType GenericEnumTypeName(TEnum)

// http://stackoverflow.com/questions/13872586/macro-how-do-i-change-each-value-in-va-args - variation of this

#define TYPENAME0 typename TParam0
#define TYPENAME1 typename TParam1, TYPENAME0
#define TYPENAME2 typename TParam2, TYPENAME1
#define TYPENAME3 typename TParam3, TYPENAME2
#define TYPENAME4 typename TParam4, TYPENAME3
#define TYPENAME5 typename TParam5, TYPENAME4
#define TYPENAME6 typename TParam6, TYPENAME5
#define TYPENAME(i) TYPENAME##i

// http://stackoverflow.com/questions/28231743/self-unrolling-macro-loop-in-c-c - Self Unrolling Macro Loop

#define M_REPEAT_1(X) X
#define M_REPEAT_2(X) X X
#define M_REPEAT_3(X) X X X
#define M_REPEAT_4(X) X X X X
#define M_REPEAT_5(X) X M_REPEAT_4(X)
#define M_REPEAT_6(X) M_REPEAT_3(X) M_REPEAT_3(X)

#define M_EXPAND(...) __VA_ARGS__

#define M_REPEAT__(N, X) M_EXPAND(M_REPEAT_ ## N)(X)
#define M_REPEAT_(N, X) M_REPEAT__(N, X)
#define M_REPEAT(N, X) M_REPEAT_(M_EXPAND(N), X)


#define SwitchOnType(targetEnumValue, valueWithTypeParameter)		\
switch (targetEnumValue) {											\
	case UnderlyingKind::Int32Kind:									\
		valueWithTypeParameter(Int32);								\
	break;															\
	case UnderlyingKind::UInt32Kind:								\
		valueWithTypeParameter(UInt32);								\
	break;															\
	case UnderlyingKind::Int64Kind:									\
		valueWithTypeParameter(Int64);								\
	break;															\
	case UnderlyingKind::UInt64Kind:								\
		valueWithTypeParameter(UInt64);								\
	break;															\
	case UnderlyingKind::Int16Kind:									\
		valueWithTypeParameter(Int16);								\
	break;															\
	case UnderlyingKind::UInt16Kind:								\
		valueWithTypeParameter(UInt16);								\
	break;															\
	case UnderlyingKind::ByteKind:									\
		valueWithTypeParameter(Byte);								\
	break;															\
	case UnderlyingKind::SByteKind:									\
		valueWithTypeParameter(SByte);								\
	break;															\
}
