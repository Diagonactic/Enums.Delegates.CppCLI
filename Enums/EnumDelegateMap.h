#pragma once

ref class Enums;
ref class EnumExtensions;

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Text;
using namespace System::Runtime::InteropServices;
using namespace System::Runtime::CompilerServices;
using namespace System::Diagnostics;
using namespace System::Collections::ObjectModel;
using namespace System::Linq;

#define GenericEnumDelegateMap \
	generic<typename TEnum, typename TReturn> GenericEnumTypeConstraint(TEnum)											

#define EnumDelegateMapFuncParameter Func<TEnum, TReturn>^
#define EnumDelegateMapFuncParameterParams(num) Func<TEnum, num, TReturn>^

#define EnumDelegateMapPrivateProperties \
	Dictionary<TEnum, EnumDelegateMapFuncParameter>^ s_functionMap = gcnew Dictionary<TEnum, EnumDelegateMapFuncParameter>(s_comparer); \
	EnumDelegateMapFuncParameter s_default = nullptr;

#define EnumDelegateMapPrivatePropertiesParams(typenameParameters) \
	Dictionary<TEnum, EnumDelegateMapFuncParameterParams(typenameParameters)>^ s_functionMap = gcnew Dictionary<TEnum, EnumDelegateMapFuncParameterParams(typenameParameters)>(s_comparer); \
	EnumDelegateMapFuncParameterParams(typenameParameters) s_default = nullptr;

#define EnumDelegateMap_ExecuteFlagsMatches(typenameParametersWithNames, parameterNames)						\
	IDictionary<TEnum, TReturn>^ ExecuteFlagsMatches(TEnum value, typenameParametersWithNames) {				\
		auto retVal = gcnew Dictionary<TEnum, TReturn>(s_comparer);												\
																												\
		if (s_functionMap->ContainsKey(value)) {																\
			retVal->Add(value, s_functionMap[value](value, parameterNames));									\
		}																										\
																												\
		auto containedValues = (array<TEnum>^)Enum::GetValues(TEnum::typeid);									\
																												\
		for each (TEnum val in containedValues) {																\
			if (val != value && EnumExtensions::IsFlagSet(value, val) && s_functionMap->ContainsKey(val)) {		\
					retVal->Add(val, s_functionMap[val](value, parameterNames));								\
				}																								\
			}																									\
		return retVal;																							\
	}

#define EnumDelegateMap_ExecuteExactMatchDelegate(typenameParametersWithNames, typenameParameters, parameterNames)							\
		TReturn ExecuteExactMatch(TEnum value, typenameParametersWithNames, EnumDelegateMapFuncParameterParams(typenameParameters) defaultDelegate) {	\
			if (!s_functionMap->ContainsKey(value) && defaultDelegate == nullptr)															\
				return TReturn();																											\
																																			\
			if (s_functionMap->ContainsKey(value)) {																						\
				return s_functionMap[value](value, parameterNames);																			\
			}																																\
																																			\
			return defaultDelegate(value, parameterNames);																					\
		}

#define EnumDelegateMap_ExecuteExactMatch(typenameParametersWithNames, parameterNames)	\
		TReturn ExecuteExactMatch(TEnum value, typenameParametersWithNames) {								\
			return ExecuteExactMatch(value, parameterNames, true);											\
		}

#define EnumDelegateMap_ExecuteExactMatchBool(typenameParametersWithNames, parameterNames)					\
TReturn ExecuteExactMatch(TEnum value,typenameParametersWithNames, bool useDefaultIfNotFound) {				\
			return ExecuteExactMatch(value, parameterNames, useDefaultIfNotFound ? s_default : nullptr);	\
		}

namespace Diagonactic {
	
	generic<typename TEnum, typename TParameter, typename TReturn> GenericEnumTypeConstraint(TEnum)
	public ref class ParameterizedEnumDelegateMap
	{
	private:
		static IEqualityComparer<TEnum>^ s_comparer = Enums::EqualityComparer<TEnum>();
		EnumDelegateMapPrivatePropertiesParams(TParameter)

	public:
		
		ParameterizedEnumDelegateMap() {

		}

		ParameterizedEnumDelegateMap(EnumDelegateMapFuncParameterParams(TParameter) defaultDelegate) {
			s_default = defaultDelegate;
		}


		
		/// <summary>
		/// Assigns a <paramrf name="delegateFunction"/> to the exact value of <paramref name="value"/>
		/// </summary>
		/// <remarks>It's possible to use flags values with this method.  In the case of <see cref="ExecuteExactMatch"/>, that value will execute. For <see cref="ExecuteFlagsMatches"/>, the value will execute if it's an exact match in addition to other flags matches.</remarks>
		/// <param name="value">The value to assign <paramref name="delegateFunction/>.</param>
		/// <param name="delegateFunction">The function to assign to the exact value of <paramref name="value"/>.</param>
		/// <exception cref="ArgumentNullException"><paramref name="delegateFunction"/> is null</exception>
		/// <exception cref="ArgumentException"><paramref name="value"/> already has a method assigned.</exception>
		void AssignToExactValue(TEnum value, EnumDelegateMapFuncParameterParams(TParameter) delegateFunction) {
			if (delegateFunction == nullptr) throw gcnew ArgumentNullException("delegateFunction");
			if (s_functionMap->ContainsKey(value)) throw gcnew ArgumentException("A method is already assigned to provided value of " + EnumExtensions::AsString(value), "value");

			s_functionMap->Add(value, delegateFunction);
		}

		
		/// <summary>
		/// Assigns <paramref name="delegateFunction"/> to each flag value in <paramref name="value"/>.
		/// </summary>
		/// <param name="value">The value to assign <paramref name="delegateFunction"/> to each flag value.</param>
		/// <param name="delegateFunction">The delegate to assign to each <paramref name="delegateFunction"/>.</param>
		/// <exception cref="ArgumentNullException"><paramref name="delegateFunction"/> is null.</exception>
		/// <exception cref="ArgumentException">A flag value in <paramref name="value"/> already has a method assigned.</exception>
		void AssignToEachFlag(TEnum value, EnumDelegateMapFuncParameterParams(TParameter) delegateFunction) {
			array<TEnum>^ values = (array<TEnum>^)Enum::GetValues(TEnum::typeid);

			if (values == nullptr || values->Length == 0)
				return;

			for each(auto val in values) {
				if (EnumExtensions::IsFlagSet(value, val)) {
					if (s_functionMap->ContainsKey(val)) throw gcnew ArgumentException("The flag value " + EnumExtensions::AsString(val) + " already has a delegate assigned.");
					AssignToExactValue(val, delegateFunction);
				}				
			}
		}
		
		/// <summary>
		/// Executes assigned delegates for each flag assigned to <paramref name="value"/> and any exact matches assigned to the value.
		/// </summary>
		/// <remarks>
		/// For flags matches, this will execute each matched flags along with any values that match the exact value of <paramref name="value"/>.  It will also pass in the value passed into the method, not the matched value.
		/// </remarks>
		/// <param name="value">The flags enum value to search for delegates to execute</param>
		/// <returns>A dictionary containing a mapping of enums to delegates</returns>
		EnumDelegateMap_ExecuteFlagsMatches(TParameter p0, p0)

		/// <summary>
		/// Executes the delegate assigned to the exact value of the <typeparamref name="TEnum"/>, running the default delegate if no match is found.
		/// </summary>
		/// <param name="value">The value of the enum to search for a <see langword="delegate"/> to execute.</param>		
		/// <returns>The value returned from the matched <see langword="Func{TReturn}"/>, the result of the default delegate, or <see langword="default"/>(<typeparamref name="TReturn"/>).</returns>
		EnumDelegateMap_ExecuteExactMatch(TParameter p0, p0)
		

		/// <summary>
		/// Executes the delegate assigned to the exact value of the <typeparamref name="TEnum"/>, running <paramref name="defaultDelegate"/> if no match is found.
		/// </summary>
		/// <param name="value">The value of the enum to search for a <see langword="delegate"/> to execute.</param>
		/// <param name="defaultDelegate">The default delegate to execute if a match is not found (ignors assigned default)</param>
		/// <returns>The value returned from the matched <see cref="Func{TReturn}"/>, the result of <paramref name="defualtDelegate"/> if parameter is not <see langword="null"/>, or <see langword="default"/>(<typeparamref name="TReturn"/>).</returns>
		EnumDelegateMap_ExecuteExactMatchDelegate(TParameter p0, TParameter, p0)
		
		
		/// <summary>
		/// Executes the delegate assigned to the exact value of the <typeparamref name="TEnum"/>.
		/// </summary>
		/// <param name="value">The value of the enum to search for a <see langword="delegate"/> to execute.</param>
		/// <param name="useDefaultIfNotFound">When <see langword="true"/>, executes the default when <paramref name="value"/> is not found; otherwise returns <see langword="default"/>(<typeparamref name="TReturn"/>).</param>
		/// <returns>The value returned from the matched <see langword="Func{TReturn}"/>, the result of the default delegate if <paramref name="useDefaulIfNotFound"/> is <see langword="true"/>, or <see langword="default"/>(<typeparamref name="TReturn"/>).</returns>
		EnumDelegateMap_ExecuteExactMatchBool(TParameter p0, p0)
		
	};
	

	GenericEnumDelegateMap public ref class EnumDelegateMap
	{
	private:
		static IEqualityComparer<TEnum>^ s_comparer = Enums::EqualityComparer<TEnum>();
		EnumDelegateMapPrivateProperties

	public:

		EnumDelegateMap() {

		}

		EnumDelegateMap(EnumDelegateMapFuncParameter defaultDelegate) {
			s_default = defaultDelegate;
		}

		/// <summary>
		/// Assigns a <paramrf name="delegateFunction"/> to the exact value of <paramref name="value"/>
		/// </summary>
		/// <remarks>It's possible to use flags values with this method.  In the case of <see cref="ExecuteExactMatch"/>, that value will execute. For <see cref="ExecuteFlagsMatches"/>, the value will execute if it's an exact match in addition to other flags matches.</remarks>
		/// <param name="value">The value to assign <paramref name="delegateFunction/>.</param>
		/// <param name="delegateFunction">The function to assign to the exact value of <paramref name="value"/>.</param>
		/// <exception cref="ArgumentNullException"><paramref name="delegateFunction"/> is null</exception>
		/// <exception cref="ArgumentException"><paramref name="value"/> already has a method assigned.</exception>
		void AssignToExactValue(TEnum value, EnumDelegateMapFuncParameter delegateFunction) {
			if (delegateFunction == nullptr) throw gcnew ArgumentNullException("delegateFunction");
			if (s_functionMap->ContainsKey(value)) throw gcnew ArgumentException("A method is already assigned to provided value of " + EnumExtensions::AsString(value), "value");

			s_functionMap->Add(value, delegateFunction);
		}

		/// <summary>
		/// Assigns <paramref name="delegateFunction"/> to each flag value in <paramref name="value"/>.
		/// </summary>
		/// <param name="value">The value to assign <paramref name="delegateFunction"/> to each flag value.</param>
		/// <param name="delegateFunction">The delegate to assign to each <paramref name="delegateFunction"/>.</param>
		/// <exception cref="ArgumentNullException"><paramref name="delegateFunction"/> is null.</exception>
		/// <exception cref="ArgumentException">A flag value in <paramref name="value"/> already has a method assigned.</exception>
		void AssignToEachFlag(TEnum value, EnumDelegateMapFuncParameter delegateFunction) {
			array<TEnum>^ values = (array<TEnum>^)Enum::GetValues(TEnum::typeid);

			if (values == nullptr || values->Length == 0)
				return;

			for each(auto val in values) {
				if (EnumExtensions::IsFlagSet(value, val)) {
					if (s_functionMap->ContainsKey(val)) throw gcnew ArgumentException("The flag value " + EnumExtensions::AsString(val) + " already has a delegate assigned.");
					AssignToExactValue(val, delegateFunction);
				}
				
				
			}
		}
		
		/// <summary>
		/// Executes assigned delegates for each flag assigned to <paramref name="value"/> and any exact matches assigned to the value.
		/// </summary>
		/// <remarks>
		/// For flags matches, this will execute each matched flags along with any values that match the exact value of <paramref name="value"/>.  It will also pass in the value passed into the method, not the matched value.
		/// </remarks>
		/// <param name="value">The flags enum value to search for delegates to execute</param>
		/// <returns>A dictionary containing a mapping of enums to delegates</returns>
		IDictionary<TEnum, TReturn>^ ExecuteFlagsMatches(TEnum value) {
			auto retVal = gcnew Dictionary<TEnum, TReturn>(s_comparer);

			if (s_functionMap->ContainsKey(value)) {
				retVal->Add(value, s_functionMap[value](value));
			}
			
			auto containedValues = (array<TEnum>^)Enum::GetValues(TEnum::typeid);
			
			for each (TEnum val in containedValues) {

				if (val != value && EnumExtensions::IsFlagSet(value, val) && s_functionMap->ContainsKey(val)) {
					retVal->Add(val, s_functionMap[val](value));
				}
			}

			return retVal;
		}

		/// <summary>
		/// Executes the delegate assigned to the exact value of the <typeparamref name="TEnum"/>, running the default delegate if no match is found.
		/// </summary>
		/// <param name="value">The value of the enum to search for a <see langword="delegate"/> to execute.</param>		
		/// <returns>The value returned from the matched <see langword="Func{TReturn}"/>, the result of the default delegate, or <see langword="default"/>(<typeparamref name="TReturn"/>).</returns>
		TReturn ExecuteExactMatch(TEnum value) {
			return ExecuteExactMatch(value, true);
		}

		/// <summary>
		/// Executes the delegate assigned to the exact value of the <typeparamref name="TEnum"/>, running <paramref name="defaultDelegate"/> if no match is found.
		/// </summary>
		/// <param name="value">The value of the enum to search for a <see langword="delegate"/> to execute.</param>
		/// <param name="defaultDelegate">The default delegate to execute if a match is not found (ignors assigned default)</param>
		/// <returns>The value returned from the matched <see cref="Func{TReturn}"/>, the result of <paramref name="defualtDelegate"/> if parameter is not <see langword="null"/>, or <see langword="default"/>(<typeparamref name="TReturn"/>).</returns>
		TReturn ExecuteExactMatch(TEnum value, EnumDelegateMapFuncParameter defaultDelegate) {
			if (!s_functionMap->ContainsKey(value) && defaultDelegate == nullptr)
				return TReturn();

			if (s_functionMap->ContainsKey(value)) {
				return s_functionMap[value](value);
			}

			return defaultDelegate(value);
		}
		
		/// <summary>
		/// Executes the delegate assigned to the exact value of the <typeparamref name="TEnum"/>.
		/// </summary>
		/// <param name="value">The value of the enum to search for a <see langword="delegate"/> to execute.</param>
		/// <param name="useDefaultIfNotFound">When <see langword="true"/>, executes the default when <paramref name="value"/> is not found; otherwise returns <see langword="default"/>(<typeparamref name="TReturn"/>).</param>
		/// <returns>The value returned from the matched <see langword="Func{TReturn}"/>, the result of the default delegate if <paramref name="useDefaulIfNotFound"/> is <see langword="true"/>, or <see langword="default"/>(<typeparamref name="TReturn"/>).</returns>
		TReturn ExecuteExactMatch(TEnum value, bool useDefaultIfNotFound) {	
			return ExecuteExactMatch(value, useDefaultIfNotFound ? s_default : nullptr);
		}		
	};
}