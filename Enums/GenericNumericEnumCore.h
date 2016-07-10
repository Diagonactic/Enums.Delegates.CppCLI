#pragma once
#include "GenericEnumValues.h"
#include "NumberMap.h"

#define NumberMapField(typeName) <typeName>^ s_enum##typeName

ref class GenericEnumValues;
enum UnderlyingKind : char;
ref class MsilConvert;

using namespace System;
using namespace System::Collections::Generic;

using namespace System::Runtime::InteropServices;
using namespace System::Runtime::CompilerServices;
using namespace System::Diagnostics;
using namespace System::Collections::ObjectModel;
using namespace System::Linq;

namespace Diagonactic {

	GenericEnumType	private ref class GenericNumericEnumCore abstract : GenericEnumValues<TEnum>
	{
	private:
		static GenericNumericEnumCore(); 

	internal:

		static String^ AsString(TEnum value); 

		static Boolean GetValueFromString(String ^value, Boolean ignoreCase, Boolean throwOnFail, [Out] TEnum %result);

		static List<TEnum>^ ToList();

		static List<TEnum>^ ToList(TEnum value);

		static array<String^>^ GetNames();

		static array<TEnum>^ ToArray();
		
		static Boolean ParseEnum(String ^value, Boolean ignoreCase, Boolean throwOnFail, [Out] TEnum %result);

		inline static Boolean ThrowOrDefaultEnum(Boolean throwException);

		static Dictionary<String^, TEnum>^ s_nameMap;
		static Dictionary<String^, TEnum>^ s_caseMap;
		static IEqualityComparer<TEnum>^ s_comparer;		
		static NumberMap NumberMapField(Int16);
		static NumberMap NumberMapField(UInt16);
		static NumberMap NumberMapField(Int32);
		static NumberMap NumberMapField(UInt32);
		static NumberMap NumberMapField(Int64);
		static NumberMap NumberMapField(UInt64);
		static NumberMap NumberMapField(Byte);
		static NumberMap NumberMapField(SByte);
	};


}

