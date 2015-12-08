#pragma once

using namespace System;
using namespace System::Collections::Generic;

namespace Diagonactic {
	
	private ref class FastStringComparer : public IEqualityComparer<String^> {
	public:
		virtual bool Equals(String^ left, String^ right) { return left->Equals(right); }
		virtual int GetHashCode(String^ value) { return value->GetHashCode(); }
	};

	/// <summary>
	/// An equality comparer for enums that have an underlying type of <see cref="System::Int32"/>
	/// </summary>
	generic<typename TEnum> where TEnum : IComparable, IFormattable, IConvertible, System::Enum
	private ref class Int32EnumEqualityComparer : public IEqualityComparer<TEnum>
	{
	public:
		virtual bool Equals(TEnum left, TEnum right) sealed { return left == right; }
		virtual int GetHashCode(TEnum value) sealed { return Util::ClobberToInt32(value); }
	};

	/// <summary>
	/// An equality comparer for enums that have an underlying type of <see cref="System::UInt32"/>
	/// </summary>
	generic<typename TEnum> where TEnum : IComparable, IFormattable, IConvertible, System::Enum
	private ref class UInt32EnumEqualityComparer : public IEqualityComparer<TEnum>
	{
	public:
		virtual bool Equals(TEnum left, TEnum right) sealed { return left == right; }
		virtual int GetHashCode(TEnum value) sealed { return Util::ClobberToUInt32(value); }
	};

	/// <summary>
	/// An equality comparer for enums that have an underlying type of <see cref="System::Int16"/>
	/// </summary>
	generic<typename TEnum> where TEnum : IComparable, IFormattable, IConvertible, System::Enum
	private ref class Int16EnumEqualityComparer : public IEqualityComparer<TEnum>
	{
	public:
		virtual bool Equals(TEnum left, TEnum right) sealed { return left == right; }
		virtual int GetHashCode(TEnum value) sealed { return Util::ClobberToInt16(value); }
	};

	/// <summary>
	/// An equality comparer for enums that have an underlying type of <see cref="System::UInt32"/>
	/// </summary>
	generic<typename TEnum> where TEnum : IComparable, IFormattable, IConvertible, System::Enum
	private ref class UInt16EnumEqualityComparer : public IEqualityComparer<TEnum>
	{
	public:
		virtual bool Equals(TEnum left, TEnum right) sealed { return left == right; }
		virtual int GetHashCode(TEnum value) sealed { return Util::ClobberToUInt16(value); }
	};

	/// <summary>
	/// An equality comparer for enums that have an underlying type of <see cref="System::Int64"/>
	/// </summary>
	generic<typename TEnum> where TEnum : IComparable, IFormattable, IConvertible, System::Enum
	private ref class Int64EnumEqualityComparer : public IEqualityComparer<TEnum>
	{
	public:
		virtual bool Equals(TEnum left, TEnum right) sealed { return left == right; }
		virtual int GetHashCode(TEnum value) sealed { return Util::ClobberToInt64(value).GetHashCode(); }
	};
	/// <summary>
	/// An equality comparer for enums that have an underlying type of <see cref="System::UInt64"/>
	/// </summary>
	generic<typename TEnum> where TEnum : IComparable, IFormattable, IConvertible, System::Enum
	private ref class UInt64EnumEqualityComparer : public IEqualityComparer<TEnum>
	{
	public:
		virtual bool Equals(TEnum left, TEnum right) sealed { return left == right; }
		virtual int GetHashCode(TEnum value) sealed { return Util::ClobberToUInt64(value).GetHashCode(); }
	};

	/// <summary>
	/// An equality comparer for enums that have an underlying type of <see cref="System::Byte"/>
	/// </summary>
	generic<typename TEnum> where TEnum : IComparable, IFormattable, IConvertible, System::Enum
	private ref class ByteEnumEqualityComparer : public IEqualityComparer<TEnum>
	{
	public:
		virtual bool Equals(TEnum left, TEnum right) sealed { return left == right; }
		virtual int GetHashCode(TEnum value) sealed { return Util::ClobberToByte(value); }
	};

	/// <summary>
	/// An equality comparer for enums that have an underlying type of <see cref="System::SByte"/>
	/// </summary>
	generic<typename TEnum> where TEnum : IComparable, IFormattable, IConvertible, System::Enum
	private ref class SByteEnumEqualityComparer : public IEqualityComparer<TEnum>
	{
	public:
		virtual bool Equals(TEnum left, TEnum right) sealed { return left == right; }
		virtual int GetHashCode(TEnum value) sealed { return Util::ClobberToSByte(value); }
	};

	private ref class Comparers {
	internal:
		static FastStringComparer^ s_stringComparer = gcnew FastStringComparer();		
	};
}


