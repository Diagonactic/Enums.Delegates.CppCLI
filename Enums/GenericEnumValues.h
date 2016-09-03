#pragma once
#include "GenericEnumMinimal.h"

ref class GenericEnumMinimal;
enum UnderlyingKind : char;

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Collections::ObjectModel;

namespace Diagonactic
{

	GenericEnumType private ref class GenericEnumValues abstract : public GenericEnumMinimal<TEnum>
	{
	internal:
		static array<TEnum> ^s_values = (array<TEnum>^)Enum::GetValues(s_type);
		static Int32 s_length = s_values->Length;
	};
}