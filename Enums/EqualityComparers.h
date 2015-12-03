#pragma once

using namespace System;
using namespace System::Collections::Generic;

namespace Diagonactic {
	generic<typename TEnum> where TEnum : IComparable, IFormattable, IConvertible, System::Enum
	ref class Int32EnumEqualityComparer : public IEqualityComparer<TEnum>
	{
	public:
		virtual bool Equals(TEnum left, TEnum right) sealed { return left == right; }
		virtual int GetHashCode(TEnum value) sealed { return Util::ClobberToInt32(value); }
	};
	generic<typename TEnum> where TEnum : IComparable, IFormattable, IConvertible, System::Enum
	ref class UInt32EnumEqualityComparer : public IEqualityComparer<TEnum>
	{
	public:
		virtual bool Equals(TEnum left, TEnum right) sealed { return left == right; }
		virtual int GetHashCode(TEnum value) sealed { return Util::ClobberToUInt32(value); }
	};
	generic<typename TEnum> where TEnum : IComparable, IFormattable, IConvertible, System::Enum
	ref class Int16EnumEqualityComparer : public IEqualityComparer<TEnum>
	{
	public:
		virtual bool Equals(TEnum left, TEnum right) sealed { return left == right; }
		virtual int GetHashCode(TEnum value) sealed { return Util::ClobberToInt16(value); }
	};
	generic<typename TEnum> where TEnum : IComparable, IFormattable, IConvertible, System::Enum
	ref class UInt16EnumEqualityComparer : public IEqualityComparer<TEnum>
	{
	public:
		virtual bool Equals(TEnum left, TEnum right) sealed { return left == right; }
		virtual int GetHashCode(TEnum value) sealed { return Util::ClobberToUInt16(value); }
	};
	generic<typename TEnum> where TEnum : IComparable, IFormattable, IConvertible, System::Enum
	ref class Int64EnumEqualityComparer : public IEqualityComparer<TEnum>
	{
	public:
		virtual bool Equals(TEnum left, TEnum right) sealed { return left == right; }
		virtual int GetHashCode(TEnum value) sealed { return Util::ClobberToInt64(value).GetHashCode(); }
	};
	generic<typename TEnum> where TEnum : IComparable, IFormattable, IConvertible, System::Enum
	ref class UInt64EnumEqualityComparer : public IEqualityComparer<TEnum>
	{
	public:
		virtual bool Equals(TEnum left, TEnum right) sealed { return left == right; }
		virtual int GetHashCode(TEnum value) sealed { return Util::ClobberToUInt64(value).GetHashCode(); }
	};
	generic<typename TEnum> where TEnum : IComparable, IFormattable, IConvertible, System::Enum
	ref class ByteEnumEqualityComparer : public IEqualityComparer<TEnum>
	{
	public:
		virtual bool Equals(TEnum left, TEnum right) sealed { return left == right; }
		virtual int GetHashCode(TEnum value) sealed { return Util::ClobberToByte(value); }
	};
	generic<typename TEnum> where TEnum : IComparable, IFormattable, IConvertible, System::Enum
	ref class SByteEnumEqualityComparer : public IEqualityComparer<TEnum>
	{
	public:
		virtual bool Equals(TEnum left, TEnum right) sealed { return left == right; }
		virtual int GetHashCode(TEnum value) sealed { return Util::ClobberToSByte(value); }
	};
}


