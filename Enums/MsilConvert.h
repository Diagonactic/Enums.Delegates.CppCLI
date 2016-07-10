#pragma once

using namespace System;
using namespace System::Runtime::CompilerServices;
/// <summary>
/// As written, these conversion methods will use Enum::ToObject, which comes with
/// a small expense associated.  When transformed with the MSIL project, the call
/// is replaced with a direct cast to the type.  The code is written this way to
/// allow profiling in before/after manner.
/// </summary>
namespace Diagonactic {
	private ref class MsilConvert sealed abstract
	{
	internal:
		template <typename TNumber>	static TNumber ClobberTo(void* enumVal)
		{
			return *reinterpret_cast<TNumber*>(enumVal);
		}

		
		GenericEnumType	[MethodImpl(MethodImplOptions::NoInlining)]	static TEnum ClobberFrom(Byte val)
		{
			return (TEnum)Enum::ToObject(TEnum::typeid, val);
		}

		GenericEnumType	[MethodImpl(MethodImplOptions::NoInlining)]	static TEnum ClobberFrom(SByte val)
		{
			return (TEnum)Enum::ToObject(TEnum::typeid, val);
		}

		GenericEnumType	[MethodImpl(MethodImplOptions::NoInlining)]	static TEnum ClobberFrom(Int16 val)
		{
			return (TEnum)Enum::ToObject(TEnum::typeid, val);
		}

		GenericEnumType	[MethodImpl(MethodImplOptions::NoInlining)]	static TEnum ClobberFrom(UInt16 val)
		{
			return (TEnum)Enum::ToObject(TEnum::typeid, val);
		}

		GenericEnumType	[MethodImpl(MethodImplOptions::NoInlining)]	static TEnum ClobberFrom(Int32 val)
		{
			return (TEnum)Enum::ToObject(TEnum::typeid, val);
		}

		GenericEnumType	[MethodImpl(MethodImplOptions::NoInlining)]	static TEnum ClobberFrom(UInt32 val)
		{
			return (TEnum)Enum::ToObject(TEnum::typeid, val);
		}

		GenericEnumType	[MethodImpl(MethodImplOptions::NoInlining)]	static TEnum ClobberFrom(Int64 val)
		{
			return (TEnum)Enum::ToObject(TEnum::typeid, val);
		}

		GenericEnumType	[MethodImpl(MethodImplOptions::NoInlining)]	static TEnum ClobberFrom(UInt64 val)
		{
			return (TEnum)Enum::ToObject(TEnum::typeid, val);
		}
	};
}