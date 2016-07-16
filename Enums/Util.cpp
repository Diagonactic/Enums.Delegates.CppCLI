#include "Stdafx.h"
#include "Util.h"
#define UtilMethod(returnType) GenericEnumType returnType Diagonactic::Util::
#define UtilInlineMethod(returnType) GenericEnumType inline returnType Diagonactic::Util::

UtilInlineMethod(UnderlyingKind) GetKind() {
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



#define ClobberTo(typeName) ClobberTo##typeName(TEnum value) { return *reinterpret_cast<typeName*>(&value); }


UtilInlineMethod(SByte) ClobberTo(SByte)
UtilInlineMethod(Byte) ClobberTo(Byte)
UtilInlineMethod(Int16) ClobberTo(Int16)
UtilInlineMethod(UInt16) ClobberTo(UInt16)
UtilInlineMethod(Int32) ClobberTo(Int32)
UtilInlineMethod(UInt32) ClobberTo(UInt32)
UtilInlineMethod(Int64) ClobberTo(Int64)
UtilInlineMethod(UInt64) ClobberTo(UInt64)

		
#pragma warning(default:4956 4957)