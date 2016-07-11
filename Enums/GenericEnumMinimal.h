#pragma once

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Reflection;
using namespace System::ComponentModel;
using namespace System::Runtime::InteropServices;

enum UnderlyingKind : char;
ref class Util;
ref class MsilConvert;

namespace Diagonactic
{
	
	GenericEnumType	private ref class GenericEnumMinimal abstract
	{
		internal:

			static TEnum s_defaultValue = TEnum();
			static Type^ s_type = TEnum::typeid;
			static UnderlyingKind s_kind = Util::GetKind(s_defaultValue);			

			static Boolean IsFlagSet(TEnum source, TEnum testVal);		

			static TEnum AddFlagsInt32(TEnum enumVal, array<TEnum>^ enumArray);

			static TEnum AddFlagsUInt32(TEnum enumVal, array<TEnum>^ enumArray);

			static TEnum AddFlagsInt64(TEnum enumVal, array<TEnum>^ enumArray);

			static TEnum AddFlagsUInt64(TEnum enumVal, array<TEnum>^ enumArray);

			static TEnum AddFlagsInt16(TEnum enumVal, array<TEnum>^ enumArray);

			static TEnum AddFlagsUInt16(TEnum enumVal, array<TEnum>^ enumArray);

			static TEnum AddFlagsByte(TEnum enumVal, array<TEnum>^ enumArray);

			static TEnum AddFlagsSByte(TEnum enumVal, array<TEnum>^ enumArray);
			
			static Boolean AreAllFlagsSet(array<TEnum>^ enumFlagsToCheck, TEnum sourceEnum);

			static Boolean AreAnyFlagsSet(array<TEnum>^ enumFlagsToCheck, TEnum sourceEnum);

			static TEnum AddFlag(TEnum sourceEnum, TEnum target);

#pragma warning(disable:4956)
#pragma warning(default:4957)
#pragma warning(default:4958)

			static TEnum RemoveFlags(TEnum sourceEnum, array<TEnum>^ enumFlagsToRemove);

			static TEnum AddFlags(array<TEnum>^ enumFlagsToAdd, TEnum sourceEnum);

			static TEnum AddFlagsSpecial(array<TEnum>^ enumFlagsToAdd, TEnum sourceEnum);
			
			static TEnum RemoveFlag(TEnum sourceEnum, TEnum enumFlagToRemove);

			static Boolean EqualsAny(array<TEnum>^ enumValuesToCheck, TEnum sourceEnum);
		};
}