#pragma once
#include "GenericEnumCoreDescriptions.h"

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Runtime::InteropServices;
using namespace JetBrains::Annotations;



namespace Diagonactic
{
	/// <summary>A set of extension and static methods for working with <see langword="enum"/> types generically.</summary>
	/// <remarks>
	/// <para>
	///		An unfortuate omission of the C# and VB.NET specification (as of version 6.0) is the lack of being able
	///		to declare <see langword="enum"/> as a generic type constraint.  There are options available that involve rewriting
	///		the compiled .DLL after the fact, however, using these methods confuses Visual Studio's Intellisense.
	/// </para>
	/// <para>
	///		In addition, many of the methods statically available on <see cref="System::Enum"/> are slow.  While their performance
	///		is acceptable in most scenarios and improving on them would be a premature optimization for most scenarios, when the requirements
	///		call for optimization for speed, doing so results in coding practices (switches with string returns and such) that are easy
	///		to make errors with and painful to maintain.
	/// </para>
	/// <para>
	///		This library targets the worst speed offenders and trades memory for performance.  It attempts to do so intelligently, however
	///		more work can be done to reduce the memory load without sacrificing performance.  For each <see langword="enum"/> type, any method
	///		that is not a direct call to a static or instance method from <see cref="System::Enum"/> has a start-up penality where the
	///		enum values and their string representations are cached (by array for performance). This is done using the default behavior of 
	///		generic static classes, where an instance of the static type is created per generic parameter.
	/// </para>
	/// <para>
	///		The cached static class is shared among any call that is not a direct call to an <see langword="enum"/> static or instance method
	///		and inheritance was used to ensure that only the hash maps required to complete the call are cached. This ensure the initial expense of 
	///		startup is incurred only once if <see cref="Diagonactic::EnumExtensions::AsString(TEnum,Boolean)"/> is used before <see cref="EnumExtensions::Parse(String)"/> or vice-versa.
	/// </para>
	/// <para>
	///		AsString() should reliably be able to be used as a replacement for ToString(). Even on the first call for UInt64 based enums
	///		that have less than 20 values, the execution time is on par with ToString() as of .Net Framework 4.5.  Future calls are dramatically
	///		faster.  In tests, calls with 1,000,000 complete in under 900ms that take ToString() a litle less than 4500ms.  This is, obviously,
	///		not a real world scenario and would be a micro-optimisation.
	/// </para>
	/// <para>For methods that do not directly call <see cref="System::Enum"/> instance or static methods, the following memory overhead applies</para>
	/// <list type="bullet">
	///		<item>
	///			<term>Base</term>
	///			<description>
	///				All methods that are not direct calls to <see cref="System::Enum"/> members discover and cache the underlying kind and the default value 
	///				of the <see langword="enum"/>.
	///			</description>
	///		</item>		
	///		<item>
	///			<term>Minimal</term>
	///			<description>Calls to get all values cache everything from Base, and store those values for future calls</description>
	///		</item>
	///		<item>
	///			<term>Core</term>
	///			<description>Calls to get all or any name cache do the above, and store all enum names as strings in <see cref="System::Collections::Generic::Dictionary"/> objects.</description>
	///		</item>
	///		<item>
	///			<term>Description</term>
	///			<description>
	///				The value stored in the <see cref="System::ComponentModel::DescriptionAttribute::Description"/> with each entry of the <see langword="enum"/>
	///				along with everything above.
	///			</description>
	///		</item>
	/// </list>
	/// <para>
	///		Startup time is shared among all methods that are not direct calls to enum instance or static methods.  Methods that use similar things,
	///		such as <c>AsString</c> and <c>Parse</c>, share their startup time (the first call to either handles startup for both).  Descriptions are only acquired
	///		when GetDescription is called.
	/// </para>
	/// <para>The first call to AsString should be the same as ToString or better for enums smaller than 20 items of UInt64 kind.  Future calls are about 4 times faster.</para>
	/// <para>The first call to Parse is slower than the equivalent <see cref="System::Enum::Parse(System::Type, System::String)"/> call, however, future calls are about twice as fast.</para>
	/// <para>
	///		Add/Remove calls are optimized to hopefully be faster than other implementations.  Direct (unsafe) casts are made to get underlying
	///		values in the correct type and binary math operations are performed to get values. There is, however, a cost to looping the array of
	///		values and a required cast back to the enum value using <see cref="System::Enum::ToObject(System::Type, System::Object)"/> that I haven't figured a way around yet.
	/// </para>
	/// <para>Direct use of binary math will always be faster, however, it comes at a cost of readability and maintanability so the trade-off is often worth it.</para>
	/// <para>
	///		In nearly all cases the memory overhead of the calls and startup penality are suitable to use these as drop-in replacements for
	///		native calls.  Readability is improved quite a bit without the need to cast to and from objects for several calls or use binary math
	///		operations
	/// </para>
	/// <para>All underlying types are supported and can contain values as large as the underlying type's <c>MaxValue</c>, however, types with more than <see cref="Int32::MaxValue"/> are not.</para>
	/// </remarks>
	public ref class Enums sealed abstract
	{
	public:
		/// <summary>
		/// Constants for generating flags enums conveniently from byte enums to Int64 enums, simply use F1 - F64 to define each item.
		/// </summary>
		ref class Flag sealed abstract
		{
			
		public:			
			literal Byte None = 0;
			literal Byte F1 = 0x1;
			literal Byte F2 = 0x2;
			literal Byte F3 = 0x4;
			literal Byte F4 = 0x8;
			literal Byte F5 = 0x10;
			literal Byte F6 = 0x20;
			literal Byte F7 = 0x40;
			literal Byte F8 = 0x80;
			literal Int16 F9 = 0x100;
			literal Int16 F10 = 0x200;
			literal Int16 F11 = 0x400;
			literal UInt16 F12 = 0x800;
			literal Int32 F13 = 0x1000;
			literal Int32 F14 = 0x2000;
			literal Int32 F15 = 0x4000;
			literal Int32 F16 = 0x8000;
			literal Int32 F17 = 0x10000;
			literal Int32 F18 = 0x20000;
			literal Int32 F19 = 0x40000;
			literal Int32 F20 = 0x80000;
			literal Int32 F21 = 0x100000;
			literal Int32 F22 = 0x200000;
			literal Int32 F23 = 0x400000;
			literal Int32 F24 = 0x800000;
			literal Int32 F25 = 0x1000000;
			literal Int32 F26 = 0x2000000;
			literal Int32 F27 = 0x4000000;
			literal Int32 F28 = 0x8000000;
			literal Int32 F29 = 0x10000000;
			literal Int32 F30 = 0x20000000;
			literal Int32 F31 = 0x40000000;
			literal UInt32 F32 = 0x80000000;
			literal Int64 F33 = 0x100000000;
			literal Int64 F34 = 0x200000000;
			literal Int64 F35 = 0x400000000;
			literal Int64 F36 = 0x800000000;
			literal Int64 F37 = 0x1000000000;
			literal Int64 F38 = 0x2000000000;
			literal Int64 F39 = 0x4000000000;
			literal Int64 F40 = 0x8000000000;
			literal Int64 F41 = 0x10000000000;
			literal Int64 F42 = 0x20000000000;
			literal Int64 F43 = 0x40000000000;
			literal Int64 F44 = 0x80000000000;
			literal Int64 F45 = 0x100000000000;
			literal Int64 F46 = 0x200000000000;
			literal Int64 F47 = 0x400000000000;
			literal Int64 F48 = 0x800000000000;
			literal Int64 F49 = 0x1000000000000;
			literal Int64 F50 = 0x2000000000000;
			literal Int64 F51 = 0x4000000000000;
			literal Int64 F52 = 0x8000000000000;
			literal Int64 F53 = 0x10000000000000;
			literal Int64 F54 = 0x20000000000000;
			literal Int64 F55 = 0x40000000000000;
			literal Int64 F56 = 0x80000000000000;
			literal Int64 F57 = 0x100000000000000;
			literal Int64 F58 = 0x200000000000000;
			literal Int64 F59 = 0x400000000000000;
			literal Int64 F60 = 0x800000000000000;
			literal Int64 F61 = 0x1000000000000000;
			literal Int64 F62 = 0x2000000000000000;
			literal Int64 F63 = 0x4000000000000000;
			literal UInt64 F64 = 0x8000000000000000;
		};

		generic <typename TEnum> where TEnum : IComparable, IFormattable, IConvertible, System::Enum, value class
		static IReadOnlyList<TEnum>^ GetValues();

		generic <typename TEnum> where TEnum : IComparable, IFormattable, IConvertible, System::Enum, value class
		static IReadOnlyList<String^>^ GetNames();
		
		/// <summary>
		/// Gets an array of names of the enum
		/// </summary>
		/// <returns>An array of the enum names</returns>
		generic <typename TEnum> where TEnum : IComparable, IFormattable, IConvertible, System::Enum, value class
		 static array<String^>^ GetNamesArray()
		{ // This had to be defined here due to compiler problem
			return Enumerable::ToArray<String^>(GenericNumericEnumCore<TEnum>::s_nameMap->Keys);
		}

		/// <summary>Gets the values of the enum as an array</summary>
		/// <returns>An array of values of the enum</returns>
		generic <typename TEnum> where TEnum : IComparable, IFormattable, IConvertible, System::Enum, value class
			static array<TEnum>^ GetValuesArray()
		{ // This had to be defined here due to compiler problem
			int len = GenericEnumValues<TEnum>::s_length;
			// A copy of the internal representation is made to ensure the internal representaion cannot be changed.
			array<TEnum>^ newVals = (array<TEnum>^)Array::CreateInstance(GenericEnumMinimal<TEnum>::s_type, len);
			Array::Copy(GenericEnumValues<TEnum>::s_values, 0, newVals, 0, len);
			return newVals;
		}

		/// <summary>Returns an equality comparer for <typeparamref name="TEnum"/> based on the underlying type of the TEnum</summary>
		/// <remarks><see cref="System::Enum"/> does not implement IEquatable and as a result, HashSet, Dictionary and anything else that relies on
		/// GetHashCode calls route them through <see cref="System::Object"/> resulting in a boxing/unboxing of the value.  This implementation performs
		/// the call to GetHashCode directly on the underlying type and when passed in as the comparer parameter, will result in faster hash lookups</remarks>
		/// <typeparam name="TEnum">An <see langword="enum"/> (<see cref="System::Enum"/>)</typeparam>
		/// <returns></returns>
		generic <typename TEnum> where TEnum : IComparable, IFormattable, IConvertible, System::Enum, value class
			static IEqualityComparer<TEnum>^ EqualityComparer() 
		{ 
			return GenericNumericEnumCore<TEnum>::s_comparer;
		}

		generic <typename TEnum> where TEnum : IComparable, IFormattable, IConvertible, System::Enum, value class		
		static Object^ AsObject(SByte value);

		generic <typename TEnum> where TEnum : IComparable, IFormattable, IConvertible, System::Enum, value class
		static Object^ AsObject(Byte value);

		generic <typename TEnum> where TEnum : IComparable, IFormattable, IConvertible, System::Enum, value class
		static Object^ AsObject(Int16 value);

		generic <typename TEnum> where TEnum : IComparable, IFormattable, IConvertible, System::Enum, value class
		static Object^ AsObject(UInt16 value);

		generic <typename TEnum> where TEnum : IComparable, IFormattable, IConvertible, System::Enum, value class
		static Object^ AsObject(Int32 value);

		generic <typename TEnum> where TEnum : IComparable, IFormattable, IConvertible, System::Enum, value class
		static Object^ AsObject(UInt32 value);

		generic <typename TEnum> where TEnum : IComparable, IFormattable, IConvertible, System::Enum, value class
		static Object^ AsObject(Int64 value);

		generic <typename TEnum> where TEnum : IComparable, IFormattable, IConvertible, System::Enum, value class
		static Object^ AsObject(UInt64 value);

		generic <typename TEnum> where TEnum : IComparable, IFormattable, IConvertible, System::Enum, value class
		static TEnum ToEnum(Object^ value);

		generic <typename TEnum> where TEnum : IComparable, IFormattable, IConvertible, System::Enum, value class		
		static TEnum ToEnum(SByte value);

		generic <typename TEnum> where TEnum : IComparable, IFormattable, IConvertible, System::Enum, value class
		static TEnum ToEnum(Byte value);

		generic <typename TEnum> where TEnum : IComparable, IFormattable, IConvertible, System::Enum, value class
		static TEnum ToEnum(Int16 value);

		generic <typename TEnum> where TEnum : IComparable, IFormattable, IConvertible, System::Enum, value class
		static TEnum ToEnum(UInt16 value);

		generic <typename TEnum> where TEnum : IComparable, IFormattable, IConvertible, System::Enum, value class
		static TEnum ToEnum(Int32 value);

		generic <typename TEnum> where TEnum : IComparable, IFormattable, IConvertible, System::Enum, value class
		static TEnum ToEnum(UInt32 value);

		generic <typename TEnum> where TEnum : IComparable, IFormattable, IConvertible, System::Enum, value class
		static TEnum ToEnum(Int64 value);

		generic <typename TEnum> where TEnum : IComparable, IFormattable, IConvertible, System::Enum, value class
		static TEnum ToEnum(UInt64 value);
				
		generic <typename TEnum> where TEnum : IComparable, IFormattable, IConvertible, System::Enum, value class			
		static TEnum Parse(String ^source, Boolean ignoreCase);

		generic <typename TEnum> where TEnum : IComparable, IFormattable, IConvertible, System::Enum, value class
		static TEnum Parse(String ^source);

		generic <typename TEnum> where TEnum : IComparable, IFormattable, IConvertible, System::Enum, value class
		static Boolean TryParse(String ^source, [Out] TEnum %result);

		generic <typename TEnum> where TEnum : IComparable, IFormattable, IConvertible, System::Enum, value class
		static Boolean TryParse(String ^source, Boolean ignoreCase, [Out] TEnum %result);
		
		generic <typename TEnum> where TEnum : IComparable, IFormattable, IConvertible, System::Enum, value class
		static Boolean TryGetFromDescription(String ^source, [Out] TEnum %result);

	};
}