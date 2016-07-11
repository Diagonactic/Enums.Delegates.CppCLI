#include "stdafx.h"
#include "EqualityComparers.h"
#include "GenericNumericEnumCore.h"
#include "MsilConvert.h"

using namespace System::Text;

#define AssignStaticMapField(type) {															\
	s_comparer = type##EnumEqualityComparer<TEnum>::Default;									\
	s_nameMap = gcnew Dictionary<String^, TEnum>(len, FastStringComparer::Default);				\
	auto values = gcnew array<type>(len);														\
	TEnum enumValue;																			\
	for (int i = 0; i < len; i++)																\
	{																							\
		enumValue = enumValues[i];																\
		values[i] = Util::ClobberTo##type(enumValue);											\
		s_nameMap->Add(names[i], enumValue);													\
	}																							\
	s_caseMap = gcnew Dictionary<String^, TEnum>(s_nameMap, StringComparer::OrdinalIgnoreCase);	\
	s_enum##type = gcnew NumberMap<type>(values, names, UnderlyingKind::type##Kind);			\
}



#define ParseEnumPart(type)																					\
	{																										\
		##type value##type = 0;																				\
		do {																								\
			i--;																							\
			String ^part = parts[i];																		\
			bool needsTrim = (Char::IsWhiteSpace(part[0]) || Char::IsWhiteSpace(part[part->Length - 1]));	\
			if (!GetValueFromString(needsTrim ? part->Trim() : part, ignoreCase, throwOnFail, result))		\
			{																								\
				result = s_defaultValue;																	\
				return ThrowOrDefaultEnum(throwOnFail);														\
			}																								\
			value##type |= Util::ClobberTo##type(result);													\
		} while(i!=0);																						\
		result = MsilConvert::ClobberFrom<TEnum>(value##type);												\
		return true;																						\
	}

#define AsStringByType(type) return s_enum##type->AsString(Util::ClobberTo##type(value));

#define GenericNumericEnumCoreMethod(returnType) GenericEnumType returnType Diagonactic::GenericNumericEnumCore<TEnum>::

GenericNumericEnumCoreMethod(String^) AsString(TEnum value)
{
	SwitchOnType(s_kind, AsStringByType)
	throw gcnew Exception("Underlying is not supported");
}

GenericNumericEnumCoreMethod(Boolean) GetValueFromString(String ^value, Boolean ignoreCase, Boolean throwOnFail, [Out] TEnum %result)
{
	if (!(ignoreCase ? s_caseMap->TryGetValue(value, result) : s_nameMap->TryGetValue(value, result)))
		return ThrowOrDefaultEnum(throwOnFail);
	return true;
}

GenericNumericEnumCoreMethod(List<TEnum>^) ToList() 
{ 
	return gcnew List<TEnum>(s_nameMap->Values); 
}

GenericNumericEnumCoreMethod(array<String^>^) GetNames()
{
	return Enumerable::ToArray(s_nameMap->Keys);
}

GenericNumericEnumCoreMethod(List<TEnum>^) ToList(TEnum value)
{
	List<TEnum>^ retVal = gcnew List<TEnum>();
	for each(TEnum item in s_nameMap->Values)
	{
		if (item == s_defaultValue)
			continue;

		if (GenericEnumMinimal<TEnum>::IsFlagSet(value, item))
			retVal->Add(item);
	}

	return retVal;
}

GenericNumericEnumCoreMethod(array<TEnum>^) ToArray()
{
	array<TEnum>^ result = (array<TEnum>^)Array::CreateInstance(TEnum::typeid, s_values->Length);
	int i = 0;
	for each(auto val in s_nameMap->Values) {
		result[i] = val;
		i++;
	}
	return result;
}

GenericNumericEnumCoreMethod(Boolean) ParseEnum(String ^value, Boolean ignoreCase, Boolean throwOnFail, [Out] TEnum %result)
{
	if (!value->Contains(","))
		return GetValueFromString(value, ignoreCase, throwOnFail, result);

	array<String^> ^parts = value->Split(Util::s_Split, StringSplitOptions::RemoveEmptyEntries);

	int i = parts->Length;

	SwitchOnType(s_kind, ParseEnumPart)

	throw gcnew Exception("Underlying Kind is not supported");
}

GenericNumericEnumCoreMethod(Boolean) ThrowOrDefaultEnum(Boolean throwException)
{
	if (throwException)
		throw gcnew ArgumentException("There is no key matching provided value", "value");
	return false;
}

GenericEnumType static Diagonactic::GenericNumericEnumCore<TEnum>::GenericNumericEnumCore()
{
	Int32 len = s_length;
	array<String^>^ names = Enum::GetNames(s_type);
	auto enumValues = s_values;

	SwitchOnType(s_kind, AssignStaticMapField);

	len = s_length;
}
