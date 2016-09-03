#pragma once
#include "Stdafx.h"
#include "MsilConvert.h"
#include "Util.h"
#include "GenericEnumMinimal.h"

#using <WindowsBase.dll>
#using <PresentationFramework.dll>
ref class MsilConvert;
ref class Util;


using namespace System;
using namespace System::Globalization;

namespace Diagonactic
{
	/// <summary>
	/// Implements a value converter that can be used with a group of checkboxes to determine, based on which flags are set, the value
	/// if the IsChecked (or other boolean component)
	/// </summary>
	/// <remarks>
	/// Based on the implementation provided on StackOverflow in C# at: http://stackoverflow.com/questions/326802/how-can-you-two-way-bind-a-checkbox-to-an-individual-bit-of-a-flags-enumeration
	/// by PaulJ http://stackoverflow.com/users/11308/paulj
	/// </remarks>
	GenericEnumType public ref class FlagsToBooleanValueConverter : public System::Windows::Data::IValueConverter {
		private:
			TEnum m_targetEnumValue;
	
		public:
#define ConvertNumeric(type) (Util::ClobberTo##type((TEnum)parameter) & Util::ClobberTo##type((TEnum)m_targetEnumValue)) != 0
#define ConvertBackNumeric(type) \
		m_targetEnumValue = MsilConvert::ClobberFrom<TEnum>((Util::ClobberTo##type(m_targetEnumValue) ^ Util::ClobberTo##type((TEnum)parameter))); \
		return m_targetEnumValue;
			virtual Object^ __clrcall Convert(Object^ value, Type^ type, Object^ parameter, CultureInfo^ cultureInfo)
			{
				m_targetEnumValue = (TEnum)value;

				switch (EnumKind)
				{
				case UnderlyingKind::ByteKind: return ConvertNumeric(Byte);	break;
				case UnderlyingKind::SByteKind: return ConvertNumeric(SByte); break;
				case UnderlyingKind::Int16Kind: return ConvertNumeric(Int16); break;
				case UnderlyingKind::UInt16Kind: return ConvertNumeric(UInt16); break;
				case UnderlyingKind::Int32Kind: return ConvertNumeric(Int32); break;
				case UnderlyingKind::UInt32Kind: return ConvertNumeric(UInt32); break;
				case UnderlyingKind::Int64Kind: return ConvertNumeric(Int64); break;
				case UnderlyingKind::UInt64Kind: return ConvertNumeric(UInt64); break;
				default: ThrowEnumUnderlyingValueInvalid; break;
				}
			}

			virtual Object^ __clrcall ConvertBack(Object^ value, Type^ type, Object^ parameter, CultureInfo^ cultureInfo)
			{
				TEnum enumParameter = (TEnum)parameter;
				switch(EnumKind)
				{
					case UnderlyingKind::ByteKind: ConvertBackNumeric(Byte); break;
					case UnderlyingKind::SByteKind: ConvertBackNumeric(SByte); break;
					case UnderlyingKind::Int16Kind: ConvertBackNumeric(Int16); break;
					case UnderlyingKind::UInt16Kind: ConvertBackNumeric(UInt16); break;
					case UnderlyingKind::Int32Kind: ConvertBackNumeric(Int32); break;
					case UnderlyingKind::UInt32Kind: ConvertBackNumeric(UInt32); break;
					case UnderlyingKind::Int64Kind: ConvertBackNumeric(Int64); break;
					case UnderlyingKind::UInt64Kind: ConvertBackNumeric(UInt64); break;
					default: ThrowEnumUnderlyingValueInvalid; break;
				}
			}
	};
}

