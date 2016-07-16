#include "Stdafx.h"
#include "Enums.h"
#include "EqualityComparers.h"
#include "EnumExtensions.h"
#include "ParameterizedEnumDelegateMap.h"

#define GenericParameterizedDelegateMap(numberOfParameters) generic <typename TEnum, TParameterTypenameDeclaration(numberOfParameters), typename TReturn> GenericEnumTypeConstraint(TEnum)
#define ParameterizedDelegateMapCtor(numberOfParameters) GenericParameterizedDelegateMap(numberOfParameters) Diagonactic::ParameterizedEnumDelegateMap##numberOfParameters<TEnum, TParameterDeclaration(numberOfParameters), TReturn>::
#define ParameterizedDelegateMapMethod(numberOfParameters, returnType) GenericParameterizedDelegateMap(numberOfParameters) returnType Diagonactic::ParameterizedEnumDelegateMap##numberOfParameters<TEnum, TParameterDeclaration(numberOfParameters), TReturn>::
#define FlagsMachesReturn IDictionary<TEnum, TReturn>^

#define CallParameterisedDelegate(numberOfParameters, methodCallCode, enumValueName) methodCallCode(enumValueName, TParameterIdentifierNames(numberOfParameters)) 

#define ParameterizedDelegateMapImplementation(numberOfParameters)																													\
ParameterizedDelegateMapCtor(numberOfParameters) ParameterizedEnumDelegateMap##numberOfParameters(FuncTEnumTParametersTReturn(numberOfParameters) defaultDelegate)					\
{																																													\
	s_default = defaultDelegate;																																					\
}																																													\
																																													\
ParameterizedDelegateMapCtor(numberOfParameters) ParameterizedEnumDelegateMap##numberOfParameters() { }																				\
																																													\
ParameterizedDelegateMapCtor(numberOfParameters) ParameterizedEnumDelegateMap##numberOfParameters(IDictionaryTEnumFunc(numberOfParameters) delegateMatches) {						\
	s_functionMap = gcnew DictionaryTEnumFunc(numberOfParameters)(delegateMatches, s_comparer);																						\
}																																													\
																																													\
ParameterizedDelegateMapCtor(numberOfParameters) ParameterizedEnumDelegateMap##numberOfParameters(IDictionaryTEnumFunc(numberOfParameters) delegateMatches, FuncTEnumTParametersTReturn(numberOfParameters) defaultDelegate) { \
	s_functionMap = gcnew DictionaryTEnumFunc(numberOfParameters)(delegateMatches, s_comparer);																						\
	s_default = defaultDelegate;																																					\
}																																													\
ParameterizedDelegateMapMethod(numberOfParameters, void) AssignToExactValue(TEnum value, FuncTEnumTParametersTReturn(numberOfParameters) delegateFunction)							\
{																																													\
	if (delegateFunction == nullptr) throw gcnew ArgumentNullException("delegateFunction");																							\
	if (s_functionMap->ContainsKey(value)) throw gcnew ArgumentException("A method is already assigned to provided value of " + EnumExtensions::AsString(value), "value");			\
																																													\
	s_functionMap->Add(value, delegateFunction);																																	\
}																																													\
																																													\
ParameterizedDelegateMapMethod(numberOfParameters, void) AssignToEachFlag(TEnum value, FuncTEnumTParametersTReturn(numberOfParameters) delegateFunction)							\
{																																													\
	array<TEnum>^ values = (array<TEnum>^)Enum::GetValues(TEnum::typeid);																											\
																																													\
	if (values == nullptr || values->Length == 0)																																	\
		return;																																										\
																																													\
	for each(auto val in values) {																																					\
		if (EnumExtensions::IsFlagSet(value, val)) {																																\
			if (s_functionMap->ContainsKey(val)) throw gcnew ArgumentException("The flag value " + EnumExtensions::AsString(val) + " already has a delegate assigned.");			\
			AssignToExactValue(val, delegateFunction);																																\
		}																																											\
	}																																												\
}																																													\
																																													\
ParameterizedDelegateMapMethod(numberOfParameters, FlagsMachesReturn) ExecuteFlagsMatches(TEnum value, TParameterMethodParameters(numberOfParameters)) {							\
		auto retVal = gcnew Dictionary<TEnum, TReturn>(s_comparer);																													\
																																													\
		if (s_functionMap->ContainsKey(value)) {																																	\
			retVal->Add(value, CallParameterisedDelegate(numberOfParameters, s_functionMap[value], value));																			\
		}																																											\
																																													\
		auto containedValues = (array<TEnum>^)Enum::GetValues(TEnum::typeid);																										\
																																													\
		for (int i=0; i < containedValues->Length; i++)	{																															\
			if (containedValues[i] != value && EnumExtensions::IsFlagSet(value, containedValues[i]) && s_functionMap->ContainsKey(containedValues[i])) {							\
					retVal->Add(containedValues[i], CallParameterisedDelegate(numberOfParameters, s_functionMap[containedValues[i]], value));										\
			}																																										\
		}																																											\
		return retVal;																																								\
}																																													\
																																													\
ParameterizedDelegateMapMethod(numberOfParameters, TReturn) ExecuteExactMatch(TEnum value, TParameterMethodParameters(numberOfParameters)) {										\
	return ExecuteExactMatch(value, TParameterIdentifierNames(numberOfParameters), true);																							\
}																																													\
																																													\
ParameterizedDelegateMapMethod(numberOfParameters, TReturn) ExecuteExactMatch(TEnum value, TParameterMethodParameters(numberOfParameters), bool useDefault) {						\
	return ExecuteExactMatch(value, TParameterIdentifierNames(numberOfParameters), useDefault ? s_default : nullptr);																\
}																																													\
																																													\
ParameterizedDelegateMapMethod(numberOfParameters, TReturn) ExecuteExactMatch(TEnum value, TParameterMethodParameters(numberOfParameters), FuncTEnumTParametersTReturn(numberOfParameters) defaultDelegate)\
{																																													\
	if (!s_functionMap->ContainsKey(value) && defaultDelegate == nullptr)																											\
		return TReturn();																																							\
																																													\
	if (s_functionMap->ContainsKey(value)) {																																		\
		return CallParameterisedDelegate(numberOfParameters, s_functionMap[value], value);																							\
	}																																												\
																																													\
	return CallParameterisedDelegate(numberOfParameters, defaultDelegate, value);																									\
}

ParameterizedDelegateMapImplementation(0)
ParameterizedDelegateMapImplementation(1)
ParameterizedDelegateMapImplementation(2)
ParameterizedDelegateMapImplementation(3)