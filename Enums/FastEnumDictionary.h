#pragma once
#include "Stdafx.h"
#include "GenericNumericEnumCore.h"


ref class GenericNumericEnumCore;

namespace Diagonactic
{
	/// <summary>
	/// An implementation of the .NET <see cref="Dictionary"/> class that includes a non-boxing, fast equality comparer to make
	/// <see cref="Dictionary"/> objects have the same performance as those with integer based keys.
	/// <remarks>
	/// Because this class includes a built-in equality comparer, the constructors that include equality comparers are omitted.  In addition,
	/// it's not possible to assign the equality comparer for the serialization constructor, so dictionaries created via deserialization will not
	/// be optimised.
	/// </remarks>
	/// </summary>
	generic <typename TEnum, typename TValue> where TEnum : IComparable, IFormattable, IConvertible, System::Enum, value class
	public ref class FastEnumDictionary : public Dictionary<TEnum, TValue>{
	public:
		/// <summary>
		/// Initializes a new instance of the <see cref="FastEnumDictionary{TEnum, TValue}"/> class that is empty, has the default initial capacity, and uses the enum optimised equality comparer <typeparamref name="TEnum"/> key.
		/// </summary>
		FastEnumDictionary() : Dictionary(GenericNumericEnumCore<TEnum>::s_comparer) { }

		/// <summary>
		/// Initializes a new instance of the <see cref="FastEnumDictionary{TEnum, TValue}"/> class that contains elements copied from the specified <see cref="IDictionary{TEnum, TValue}"/> and uses the enum optimised equality comparer <typeparamref name="TEnum"/> key
		/// </summary>
		/// <param name="dictionary">The dictionary whose elements are copied to the new <see cref="FastEnumDictionary{TEnum, TValue}"/>.</param>
		FastEnumDictionary(IDictionary<TEnum, TValue>^ dictionary) : Dictionary(dictionary, GenericNumericEnumCore<TEnum>::s_comparer) { }

		/// <summary>
		/// Initializes a new instance of the <see cref="FastEnumDictionary{TEnum, TValue}"/> class that is empty, has the <paramref name="capacity"/> class that is empty, has the specified initial capacity, and uses the enum optimised equality comparer <typeparamref name="TEnum"/> key
		/// </summary>
		/// <param name="capacity"></param>
		FastEnumDictionary(System::Int32 capacity) : Dictionary(capacity, GenericNumericEnumCore<TEnum>::s_comparer) { }

		/// <summary>
		/// Initializes a new instance of the <see cref="FastEnumDictionary{TEnum, TValue}"/> class with serialized data.
		/// </summary>
		/// <param name="info">A <see cref="System::Runtime::Serialization::SerializationInfo"/> object containing the information required to serialize the <see cref="FastEnumDictionary{TEnum, TValue}"/>.</param>
		/// <param name="context">A System.Runtime.Serialization.StreamingContext structure containing the source and destination of the serialized stream associated with the <see cref="FastEnumDictionary{TEnum, TValue}"/>.</param>
		FastEnumDictionary(System::Runtime::Serialization::SerializationInfo^ info, System::Runtime::Serialization::StreamingContext context) : Dictionary(info, context)
		{
			
		}
	};
}