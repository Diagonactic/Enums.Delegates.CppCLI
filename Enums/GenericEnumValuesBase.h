#pragma once
#include "Stdafx.h"

ref class GenericEnumBase;
enum UnderlyingKind : char;

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Collections::ObjectModel;

namespace Diagonactic
{
	generic<typename TEnum> where TEnum : IComparable, IFormattable, IConvertible, System::Enum
		private ref class GenericEnumValuesBase abstract : public GenericEnumBase<TEnum>
	{
	internal:
		static array<TEnum> ^s_values = (array<TEnum>^)Enum::GetValues(s_type);
		static Int32 s_length = s_values->Length;
	};
}