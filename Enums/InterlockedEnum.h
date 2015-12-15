#pragma once
#include "GenericEnumValues.h"

#include <cliext/hash_map>
ref class GenericEnumMinimal;
ref class GenericEnumValues;
enum UnderlyingKind : char;

using namespace System;
using namespace System::Threading;
using namespace cliext;
using namespace System::Linq;
using namespace System::Collections::Generic;

namespace Diagonactic
{
	
	/// <summary>
	/// Allows multiple threads to read an enum value while protecting atomicity and ensuring the latest
	/// value written is returned
	/// </summary>
	/// <remarks><para>Class uses the underlying type for operations using a volatile read to return value and an
	/// Interlocked.Exchange to set the value.</para>
	/// <para>While care was taken to ensure correctness and safety, there are very likely corner cases or platforms
	/// where this class behaves incorrectly.  The implementation is simple.  Review the code of the class to ensure
	/// it will fit with your particular use. Writing multi-threaded code that mutates values is hard.</para>
	/// <para>Because of the above, this implementation is considered beta.</para>
	/// <para>Not all enum types are supported.  The underlying type must be a 32-bit or 64-bit signed integer</para>
	/// <exception cref="NotSupportedException">Underlying type of enum must be a signed 32-bit or 64-bit integer.</exception>
	/// </remarks>
	generic <typename TEnum> where TEnum:IComparable, IFormattable, IConvertible, System::Enum, value class
		public ref class InterlockedEnum
	{

	private:
		Int32 int32Value;
		Int64 int64Value;
		static UnderlyingKind s_kind = GenericEnumMinimal<TEnum>::s_kind;
	public:
		InterlockedEnum(TEnum value)
		{
			switch(s_kind)
			{
			case UnderlyingKind::Int32Kind: 
				int32Value = Util::ClobberToInt32(value);
				break;
			case UnderlyingKind::Int64Kind: 
				int64Value = Util::ClobberToInt64(value);
				break;
			default: throw gcnew NotSupportedException("Underlying type of enum must be a signed 32 - bit or 64 - bit integer.");
			}
		}
		/// <summary>
		/// Gets or Sets the value of the enum using Interlocked.Exchange and VolatileRead/Interlocked.Read depending on the
		/// underlying type.
		/// </summary>
		property TEnum Value {
			TEnum get()
			{
				switch(s_kind)
				{
				case UnderlyingKind::Int32Kind: {
					auto %int32Ref = int32Value;
					return MsilConvert::ClobberFrom<TEnum>(Thread::VolatileRead(int32Ref)); 
				}
				case UnderlyingKind::Int64Kind: {
					auto %int64Ref = int64Value;
					return MsilConvert::ClobberFrom<TEnum>(Interlocked::Read(int64Ref)); 
				}
				default: throw gcnew NotSupportedException("Underlying Type for Enum must be a signed 16-bit, 32-bit or 64-bit Integer");
				}
			}
			void set(TEnum value)
			{				
				switch (s_kind)
				{
				case UnderlyingKind::Int32Kind: {
					auto %int32Ref = int32Value;
					Interlocked::Exchange(int32Ref, Util::ClobberToInt32(value));
					return;
				}
				case UnderlyingKind::Int64Kind: {
					auto %int64Ref = int64Value;
					Interlocked::Exchange(int64Ref, Util::ClobberToInt64(value));
					return;
				}
				default: throw gcnew NotSupportedException("Underlying Type for Enum must be a signed 16-bit, 32-bit or 64-bit Integer");
				}
			}
		}
	};
}


