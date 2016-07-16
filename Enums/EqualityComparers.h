#pragma once
#include "Util.h"

using namespace System;
using namespace System::Collections::Generic;

namespace Diagonactic {
	
	private ref class FastStringComparer : public IEqualityComparer<String^> {		
	public:
		static FastStringComparer^ Default = gcnew FastStringComparer();
		virtual bool Equals(String^ left, String^ right) { return String::Equals(left, right, StringComparison::Ordinal); }
		virtual int GetHashCode(String^ value) 
		{ 
			if (value == nullptr) return 0;
			int len = value->Length;
			if (len == 0) return 0;			
			
			int p1 = value[0] + len;
			return (89 * p1) + value[len - 1] + len;			
		}
	};

	private ref class FastIgnoreCaseStringComparer : public IEqualityComparer<String^> {
	public:
		static FastIgnoreCaseStringComparer^ Default = gcnew FastIgnoreCaseStringComparer();
		virtual bool Equals(String^ left, String^ right) { return String::Equals(left, right, StringComparison::OrdinalIgnoreCase); }
		virtual int GetHashCode(String^ value)
		{
			return StringComparer::OrdinalIgnoreCase->GetHashCode(value);
		}
	};
	// For 32-bit and below
	template <typename TNumber> private ref class NumericEqualityComparer : public IEqualityComparer<TNumber>
	{
	public:
		static NumericEqualityComparer<TNumber>^ Default = gcnew NumericEqualityComparer<TNumber>();
		virtual bool Equals(TNumber left, TNumber right) sealed { return left == right; }
		virtual int GetHashCode(TNumber value) sealed { return *reinterpret_cast<int*>(&value); }
	};

	template <typename TNumber> private ref class HashCodeNumericEqualityComparer : public IEqualityComparer<TNumber>
	{
		public:
			static HashCodeNumericEqualityComparer<TNumber>^ Default = gcnew HashCodeNumericEqualityComparer<TNumber>();
			virtual bool Equals(TNumber left, TNumber right) sealed {
				return left == right;
			}
			virtual int GetHashCode(TNumber value) sealed { return EqualityComparer<TNumber>::Default->GetHashCode(value); }
	};
	/// <summary>
	/// An equality comparer for enums that have an underlying type of <see cref="System::Int32"/>
	/// </summary>
	generic<typename TEnum> where TEnum : IComparable, IFormattable, IConvertible, System::Enum, value class
	private ref class Int32EnumEqualityComparer : public IEqualityComparer<TEnum>
	{
	public:
		static Int32EnumEqualityComparer^ Default = gcnew Int32EnumEqualityComparer();
		virtual bool Equals(TEnum left, TEnum right) sealed { return left == right; }
		virtual int GetHashCode(TEnum value) sealed { return Util::ClobberToInt32(value); }
	};

	/// <summary>
	/// An equality comparer for enums that have an underlying type of <see cref="System::UInt32"/>
	/// </summary>
	generic<typename TEnum> where TEnum : IComparable, IFormattable, IConvertible, System::Enum, value class
	private ref class UInt32EnumEqualityComparer : public IEqualityComparer<TEnum>
	{
	public:
		static UInt32EnumEqualityComparer^ Default = gcnew UInt32EnumEqualityComparer();
		virtual bool Equals(TEnum left, TEnum right) sealed { return left == right; }
		virtual int GetHashCode(TEnum value) sealed { return Util::ClobberToUInt32(value); }
	};

	/// <summary>
	/// An equality comparer for enums that have an underlying type of <see cref="System::Int16"/>
	/// </summary>
	generic<typename TEnum> where TEnum : IComparable, IFormattable, IConvertible, System::Enum, value class
	private ref class Int16EnumEqualityComparer : public IEqualityComparer<TEnum>
	{
	public:
		static Int16EnumEqualityComparer^ Default = gcnew Int16EnumEqualityComparer();
		virtual bool Equals(TEnum left, TEnum right) sealed { return left == right; }
		virtual int GetHashCode(TEnum value) sealed { return Util::ClobberToInt16(value); }
	};

	/// <summary>
	/// An equality comparer for enums that have an underlying type of <see cref="System::UInt32"/>
	/// </summary>
	generic<typename TEnum> where TEnum : IComparable, IFormattable, IConvertible, System::Enum, value class
	private ref class UInt16EnumEqualityComparer : public IEqualityComparer<TEnum>
	{
	public:
		static UInt16EnumEqualityComparer^ Default = gcnew UInt16EnumEqualityComparer();
		virtual bool Equals(TEnum left, TEnum right) sealed { return left == right; }
		virtual int GetHashCode(TEnum value) sealed { return Util::ClobberToUInt16(value); }
	};

	/// <summary>
	/// An equality comparer for enums that have an underlying type of <see cref="System::Int64"/>
	/// </summary>
	generic<typename TEnum> where TEnum : IComparable, IFormattable, IConvertible, System::Enum, value class
	private ref class Int64EnumEqualityComparer : public IEqualityComparer<TEnum>
	{
	public:
		static Int64EnumEqualityComparer^ Default = gcnew Int64EnumEqualityComparer();
		virtual bool Equals(TEnum left, TEnum right) sealed { return left == right; }
		virtual int GetHashCode(TEnum value) sealed { return Util::ClobberToInt64(value).GetHashCode(); }
	};
	/// <summary>
	/// An equality comparer for enums that have an underlying type of <see cref="System::UInt64"/>
	/// </summary>
	generic<typename TEnum> where TEnum : IComparable, IFormattable, IConvertible, System::Enum, value class
	private ref class UInt64EnumEqualityComparer : public IEqualityComparer<TEnum>
	{
	public:
		static UInt64EnumEqualityComparer^ Default = gcnew UInt64EnumEqualityComparer();
		virtual bool Equals(TEnum left, TEnum right) sealed { return left == right; }
		virtual int GetHashCode(TEnum value) sealed { return Util::ClobberToUInt64(value).GetHashCode(); }
	};

	/// <summary>
	/// An equality comparer for enums that have an underlying type of <see cref="System::Byte"/>
	/// </summary>
	generic<typename TEnum> where TEnum : IComparable, IFormattable, IConvertible, System::Enum, value class
	private ref class ByteEnumEqualityComparer : public IEqualityComparer<TEnum>
	{
	public:
		static ByteEnumEqualityComparer^ Default = gcnew ByteEnumEqualityComparer();
		virtual bool Equals(TEnum left, TEnum right) sealed { return left == right; }
		virtual int GetHashCode(TEnum value) sealed { return Util::ClobberToByte(value); }
	};

	/// <summary>
	/// An equality comparer for enums that have an underlying type of <see cref="System::SByte"/>
	/// </summary>
	generic<typename TEnum> where TEnum : IComparable, IFormattable, IConvertible, System::Enum, value class
	private ref class SByteEnumEqualityComparer : public IEqualityComparer<TEnum>
	{
	public:
		static SByteEnumEqualityComparer^ Default = gcnew SByteEnumEqualityComparer();
		virtual bool Equals(TEnum left, TEnum right) sealed { return left == right; }
		virtual int GetHashCode(TEnum value) sealed { return Util::ClobberToSByte(value); }
	};	
}


