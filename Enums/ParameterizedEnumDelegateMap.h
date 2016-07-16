#pragma once
#define FlagsMachesReturn IDictionary<TEnum, TReturn>^

#define GenericEnumDelegateMap 	generic<typename TEnum, typename TReturn> GenericEnumTypeConstraint(TEnum)		
#define GenericEnumDelegateMapParameters(numberOfParameters) generic<typename TEnum, TParameterTypenameDeclaration(numberOfParameters), typename TReturn> GenericEnumTypeConstraint(TEnum)
#define FuncTEnumTParametersTReturn(numberOfParameters) Func<TEnum, TParameterDeclaration(numberOfParameters), TReturn>^
#define DictionaryTEnumFunc(numberOfParameters) Dictionary<TEnum, FuncTEnumTParametersTReturn(numberOfParameters)>
#define IDictionaryTEnumFunc(numberOfParameters) IDictionary<TEnum, FuncTEnumTParametersTReturn(numberOfParameters)>^
#define EnumDelegateMapPrivatePropertiesParams(numberOfParameters) \
	Dictionary<TEnum, FuncTEnumTParametersTReturn(numberOfParameters)>^ s_functionMap = gcnew DictionaryTEnumFunc(numberOfParameters)(s_comparer); \
	FuncTEnumTParametersTReturn(numberOfParameters) s_default = nullptr;

namespace Diagonactic {

	/// <summary>A utility class that Allows for assigning/executing delegates based on <typeparamref name="TEnum"/>.</summary>
	/// <typeparam name="TEnum">The enum class that will be used to evaluate values</typeparam>
	/// <typeparam name="TParameter0">A parameter to pass into each delegate</typeparam>
	/// <typeparam name="TReturn">The return value of the delegate</typeparam>
	GenericEnumDelegateMapParameters(0) public ref class ParameterizedEnumDelegateMap0
	{																																								
	private:																																						
		static IEqualityComparer<TEnum>^ s_comparer = Enums::EqualityComparer<TEnum>();																				
		EnumDelegateMapPrivatePropertiesParams(0)																									
	public:
		/// <summary>Creates a new instance without a default delegate.</summary>
		ParameterizedEnumDelegateMap0();
		/// <summary>Creates a new instance with <paramref name="defaultDelegate"/> that will execute when a match is not found.</summary>
		/// <param name="defaultDelegate">The default delegate to execute when a match is not found</param>
		ParameterizedEnumDelegateMap0(FuncTEnumTParametersTReturn(0) defaultDelegate);
		/// <summary>Creates a new instance with <paramref name="delegateMatches"/> that will call the delegate assigned to the value field when a key match occurs</summary>
		/// <param name="delegateMatches">A dictionary containing enum values and their matching delegates to execute</param>
		ParameterizedEnumDelegateMap0(IDictionaryTEnumFunc(0) delegateMatches);

		/// <summary>Creates a new instance with <paramref name="delegateMatches"/> that will call the delegate assigned to the value field when a key match occurs and a <paramref name="defaultDelegate"/> that will execute when a match is not found.</summary>
		/// <param name="delegateMatches">A dictionary containing enum values and their matching delegates to execute</param>
		/// <param name="defaultDelegate">The default delegate to execute when a match is not found</param>
		ParameterizedEnumDelegateMap0(IDictionaryTEnumFunc(0) delegateMatches, FuncTEnumTParametersTReturn(0) defaultDelegate); 
		/// <summary>Assigns the <paramref name="delegateFunction"/> to a match <paramref name="value"/></summary>
		/// <remarks>The match must either be an exact match (if ExecuteExactMatch is called) or match one of the flags passed in to ExecuteFlagsMatches.  If the value contains more than one flag, it will only execute if
		/// the call matches the flags exactly or a call to ExecuteFlagsMatches contains at least the flags provided.</remarks>
		/// <param name="value">The value to match (see remarks)</param>
		/// <param name="delegateFunction">The method to execute on a successful match</param>		
		void AssignToExactValue(TEnum value, FuncTEnumTParametersTReturn(0) delegateFunction);														
		/// <summary>
		/// Assigns the <paramref name="delegateFunction"/> individually to each flag of <paramref name="value"/>
		/// </summary>
		/// <remarks>The match must either be an exact match of the individual flag (if ExecuteExactMatch is called) or match one of the flags passed in to ExecuteFlagsMatches.</remarks>
		/// <param name="value">The value to match (see remarks)</param>
		/// <param name="delegateFunction">The method to execute on a successful match</param>
		void AssignToEachFlag(TEnum value, FuncTEnumTParametersTReturn(0) delegateFunction);
		/// <summary>Executes the method if it exactly matches an assigned value or if one of the flags of <paramref name="value"/> matches a value assigned to a method.  Does not execute the default delegate if no matches are found.</summary>
		/// <param name="value">The flags value to look for assigned delegates</param>
		/// <param name="param">The first parameter to pass into the delegate for execution.</param>
		/// <returns>A dictionary containing the matched flag and the value the delegate returned.</returns>
		FlagsMachesReturn ExecuteFlagsMatches(TEnum value, TParameterMethodParameters(0));
		/// <summary>
		/// Executes the delegate assigned to <paramref name="value"/> or the default delegate if one is assigned to this instance.  This will not execute delegates that match parts of a flag value.
		/// </summary>
		/// <param name="value">The value to evaluate for an exact match</param>
		/// <param name="param">The parameter to pass into the delegate</param>
		/// <returns>The result of the matched delegate or the result of the default delegate if one is assigned to this instance; otherwise the default value of TReturn</returns>
		TReturn ExecuteExactMatch(TEnum value, TParameterMethodParameters(0));
		/// <summary>Executes the delegate assigned to the exact value of <paramref name="value"/> or <paramref name="defaultDelegate"/> if it is not <see langword="null"/>.</summary>
		/// <remarks>This method will not execute delegates assigned to a flag component of <paramref name="value"/></remarks>
		/// <param name="value">The value to look for assigned delegates</param>
		/// <param name="param">The first parameter to pass into the delegate</param>
		/// <param name="defaultDelegate">The default delegate to execute if a match is not found</param>
		/// <returns>The result of the matched delegate or the result of <paramref name="defaultDelegate"/> if not <see langword="null"/>; otherwise the default value of <typeparamref name="TReturn"/></returns>
		TReturn ExecuteExactMatch(TEnum value, TParameterMethodParameters(0), FuncTEnumTParametersTReturn(0) defaultDelegate);
		/// <summary>Executes the delegate assigned to the exact value of <paramref name="value"/> or the assigned default delegate if <paramref name="useDefaultIfNotFound"/> is <see langword="true"/>.</summary>
		/// <remarks>This method will not execute delegates assigned to a flag component of <paramref name="value"/></remarks>
		/// <param name="value">The value to look for assigned delegates</param>
		/// <param name="param">The first parameter to pass into the delegate</param>
		/// <param name="useDefaultIfNotFound">If <see langword="true"/>, executes The default delegate if one is assigned to this instance.</param>
		/// <returns>The result of the matched delegate or the result of the default if <paramref name="useDefaultIfNotFound"/> is <see langword="true"/>; otherwise the default value of <typeparamref name="TReturn"/></returns>
		TReturn ExecuteExactMatch(TEnum value, TParameterMethodParameters(0), bool useDefaultIfNotFound);											
	};
	/// <summary>A utility class that Allows for assigning/executing delegates based on <typeparamref name="TEnum"/>.</summary>
	/// <typeparam name="TEnum">The enum class that will be used to evaluate values</typeparam>
	/// <typeparam name="TParameter0">The first parameter to pass into each delegate</typeparam>
	/// <typeparam name="TParameter1">The second parameter to pass into each delegate</typeparam>
	/// <typeparam name="TReturn">The return value of the delegate</typeparam>
	GenericEnumDelegateMapParameters(1) public ref class ParameterizedEnumDelegateMap1
	{																																								
	private:																																						
		static IEqualityComparer<TEnum>^ s_comparer = Enums::EqualityComparer<TEnum>();																				
		EnumDelegateMapPrivatePropertiesParams(1)																									
	public:
		/// <summary>Creates a new instance without a default delegate.</summary>
		ParameterizedEnumDelegateMap1();
		/// <summary>Creates a new instance with <paramref name="defaultDelegate"/> that will execute when a match is not found.</summary>
		/// <param name="defaultDelegate">The default delegate to execute when a match is not found</param>		
		ParameterizedEnumDelegateMap1(FuncTEnumTParametersTReturn(1) defaultDelegate);											
		/// <summary>Creates a new instance with <paramref name="delegateMatches"/> that will call the delegate assigned to the value field when a key match occurs.</summary>
		/// <param name="delegateMatches">A dictionary containing enum values and their matching delegates to execute</param>
		ParameterizedEnumDelegateMap1(IDictionaryTEnumFunc(1) delegateMatches);													
		/// <summary>Creates a new instance with <paramref name="delegateMatches"/> that will call the delegate assigned to the value field when a key match occurs and a <paramref name="defaultDelegate"/> that will execute when a match is not found.</summary>
		/// <param name="delegateMatches">A dictionary containing enum values and their matching delegates to execute</param>
		/// <param name="defaultDelegate">The default delegate to execute when a match is not found</param>		
		ParameterizedEnumDelegateMap1(IDictionaryTEnumFunc(1) delegateMatches, FuncTEnumTParametersTReturn(1) defaultDelegate); 
		/// <summary>Assigns the <paramref name="delegateFunction"/> to a match <paramref name="value"/></summary>
		/// <remarks>The match must either be an exact match (if ExecuteExactMatch is called) or match one of the flags passed in to ExecuteFlagsMatches.  If the value contains more than one flag, it will only execute if
		/// the call matches the flags exactly or a call to ExecuteFlagsMatches contains at least the flags provided.</remarks>
		/// <param name="value">The value to match (see remarks)</param>
		/// <param name="delegateFunction">The method to execute on a successful match</param>		
		void AssignToExactValue(TEnum value, FuncTEnumTParametersTReturn(1) delegateFunction);														
		/// <summary>
		/// Assigns the <paramref name="delegateFunction"/> individually to each flag of <paramref name="value"/>
		/// </summary>
		/// <remarks>The match must either be an exact match of the individual flag (if ExecuteExactMatch is called) or match one of the flags passed in to ExecuteFlagsMatches.</remarks>
		/// <param name="value">The value to match (see remarks)</param>
		/// <param name="delegateFunction">The method to execute on a successful match</param>
		void AssignToEachFlag(TEnum value, FuncTEnumTParametersTReturn(1) delegateFunction);
		/// <summary>Executes the method if it exactly matches an assigned value or if one of the flags of <paramref name="value"/> matches a value assigned to a method.  Does not execute the default delegate if no matches are found.</summary>
		/// <param name="value">The flags value to look for assigned delegates</param>
		/// <param name="param">The first parameter to pass into the delegate for execution.</param>
		/// <param name="param1">The second parameter to pass into the delegate for execution.</param>
		/// /// <returns>A dictionary containing the matched flag and the value the delegate returned.</returns>
		FlagsMachesReturn ExecuteFlagsMatches(TEnum value, TParameterMethodParameters(1));
		/// <summary>Executes the method if it exactly matches an assigned value or if one of the flags of <paramref name="value"/> matches a value assigned to a method.  Does not execute the default delegate if no matches are found.</summary>
		/// <param name="value">The flags value to look for assigned delegates</param>
		/// <param name="param">The first parameter to pass into the delegate for execution.</param>
		/// <param name="param1">The second parameter to pass into the delegate for execution.</param>
		/// <returns>A dictionary containing the matched flag and the value the delegate returned.</returns>
		TReturn ExecuteExactMatch(TEnum value, TParameterMethodParameters(1));
		/// <summary>Executes the delegate assigned to the exact value of <paramref name="value"/> or <paramref name="defaultDelegate"/> if it is not <see langword="null"/>.</summary>
		/// <remarks>This method will not execute delegates assigned to a flag component of <paramref name="value"/></remarks>
		/// <param name="value">The value to look for assigned delegates</param>
		/// <param name="param">The first parameter to pass into the delegate</param>
		/// <param name="param1">The second parameter to pass into the delegate</param>
		/// <param name="defaultDelegate">The default delegate to execute if a match is not found</param>
		/// <returns>The result of the matched delegate or the result of <paramref name="defaultDelegate"/> if not <see langword="null"/>; otherwise the default value of <typeparamref name="TReturn"/></returns>
		TReturn ExecuteExactMatch(TEnum value, TParameterMethodParameters(1), FuncTEnumTParametersTReturn(1) defaultDelegate);	
		/// <summary>Executes the delegate assigned to the exact value of <paramref name="value"/> or the assigned default delegate if <paramref name="useDefaultIfNotFound"/> is <see langword="true"/>.</summary>
		/// <remarks>This method will not execute delegates assigned to a flag component of <paramref name="value"/></remarks>
		/// <param name="value">The value to look for assigned delegates</param>
		/// <param name="param">The first parameter to pass into the delegate</param>
		/// <param name="param1">The second parameter to pass into the delegate</param>
		/// <param name="useDefaultIfNotFound">If <see langword="true"/>, executes The default delegate if one is assigned to this instance.</param>
		/// <returns>The result of the matched delegate or the result of the default if <paramref name="useDefaultIfNotFound"/> is <see langword="true"/>; otherwise the default value of <typeparamref name="TReturn"/></returns>
		TReturn ExecuteExactMatch(TEnum value, TParameterMethodParameters(1), bool useDefaultIfNotFound);											
	};

	GenericEnumDelegateMapParameters(2) public ref class ParameterizedEnumDelegateMap2
	{																																								
	private:																																						
		static IEqualityComparer<TEnum>^ s_comparer = Enums::EqualityComparer<TEnum>();																				
		EnumDelegateMapPrivatePropertiesParams(2)																									
	public:
		/// <summary>Creates a new instance without a default delegate.</summary>
		ParameterizedEnumDelegateMap2();																											
		/// <summary>Creates a new instance with <paramref name="defaultDelegate"/> that will execute when a match is not found.</summary>
		/// <param name="defaultDelegate">The default delegate to execute when a match is not found</param>		
		ParameterizedEnumDelegateMap2(FuncTEnumTParametersTReturn(2) defaultDelegate);											
		/// <summary>Creates a new instance with <paramref name="delegateMatches"/> that will call the delegate assigned to the value field when a key match occurs.</summary>
		/// <param name="delegateMatches">A dictionary containing enum values and their matching delegates to execute</param>
		ParameterizedEnumDelegateMap2(IDictionaryTEnumFunc(2) delegateMatches);													
		/// <summary>Creates a new instance with <paramref name="delegateMatches"/> that will call the delegate assigned to the value field when a key match occurs and a <paramref name="defaultDelegate"/> that will execute when a match is not found.</summary>
		/// <param name="delegateMatches">A dictionary containing enum values and their matching delegates to execute</param>
		/// <param name="defaultDelegate">The default delegate to execute when a match is not found</param>		
		ParameterizedEnumDelegateMap2(IDictionaryTEnumFunc(2) delegateMatches, FuncTEnumTParametersTReturn(2) defaultDelegate); 
		/// <summary>Assigns the <paramref name="delegateFunction"/> to a match <paramref name="value"/></summary>
		/// <remarks>The match must either be an exact match (if ExecuteExactMatch is called) or match one of the flags passed in to ExecuteFlagsMatches.  If the value contains more than one flag, it will only execute if
		/// the call matches the flags exactly or a call to ExecuteFlagsMatches contains at least the flags provided.</remarks>
		/// <param name="value">The value to match (see remarks)</param>
		/// <param name="delegateFunction">The method to execute on a successful match</param>		
		void AssignToExactValue(TEnum value, FuncTEnumTParametersTReturn(2) delegateFunction);														
		/// <summary>
		/// Assigns the <paramref name="delegateFunction"/> individually to each flag of <paramref name="value"/>
		/// </summary>
		/// <remarks>The match must either be an exact match of the individual flag (if ExecuteExactMatch is called) or match one of the flags passed in to ExecuteFlagsMatches.</remarks>
		/// <param name="value">The value to match (see remarks)</param>
		/// <param name="delegateFunction">The method to execute on a successful match</param>
		void AssignToEachFlag(TEnum value, FuncTEnumTParametersTReturn(2) delegateFunction);														
		/// <summary>Executes the method if it exactly matches an assigned value or if one of the flags of <paramref name="value"/> matches a value assigned to a method.  Does not execute the default delegate if no matches are found.</summary>
		/// <param name="value">The flags value to look for assigned delegates</param>
		/// <param name="param">The first parameter to pass into the delegate for execution.</param>
		/// <param name="param1">The second parameter to pass into the delegate for execution.</param>
		/// <param name="param2">The third parameter to pass into the delegate</param>
		/// <returns>A dictionary containing the matched flag and the value the delegate returned.</returns>
		FlagsMachesReturn ExecuteFlagsMatches(TEnum value, TParameterMethodParameters(2));															
		/// <summary>Executes the method if it exactly matches an assigned value or if one of the flags of <paramref name="value"/> matches a value assigned to a method.  Does not execute the default delegate if no matches are found.</summary>
		/// <param name="value">The flags value to look for assigned delegates</param>
		/// <param name="param">The first parameter to pass into the delegate for execution.</param>
		/// <param name="param1">The second parameter to pass into the delegate for execution.</param>
		/// <param name="param2">The third parameter to pass into the delegate</param>
		/// <returns>A dictionary containing the matched flag and the value the delegate returned.</returns>
		TReturn ExecuteExactMatch(TEnum value, TParameterMethodParameters(2));																		
		/// <summary>Executes the delegate assigned to the exact value of <paramref name="value"/> or <paramref name="defaultDelegate"/> if it is not <see langword="null"/>.</summary>
		/// <remarks>This method will not execute delegates assigned to a flag component of <paramref name="value"/></remarks>
		/// <param name="value">The value to look for assigned delegates</param>
		/// <param name="param">The first parameter to pass into the delegate</param>
		/// <param name="param1">The second parameter to pass into the delegate</param>
		/// <param name="param2">The third parameter to pass into the delegate</param>
		/// <param name="defaultDelegate">The default delegate to execute if a match is not found</param>
		/// <returns>The result of the matched delegate or the result of <paramref name="defaultDelegate"/> if not <see langword="null"/>; otherwise the default value of <typeparamref name="TReturn"/></returns>
		TReturn ExecuteExactMatch(TEnum value, TParameterMethodParameters(2), FuncTEnumTParametersTReturn(2) defaultDelegate);	
		/// <summary>Executes the delegate assigned to the exact value of <paramref name="value"/> or the assigned default delegate if <paramref name="useDefaultIfNotFound"/> is <see langword="true"/>.</summary>
		/// <remarks>This method will not execute delegates assigned to a flag component of <paramref name="value"/></remarks>
		/// <param name="value">The value to look for assigned delegates</param>
		/// <param name="param">The first parameter to pass into the delegate</param>
		/// <param name="param1">The second parameter to pass into the delegate</param>
		/// <param name="param2">The third parameter to pass into the delegate</param>
		/// <param name="useDefaultIfNotFound">If <see langword="true"/>, executes The default delegate if one is assigned to this instance.</param>
		/// <returns>The result of the matched delegate or the result of the default if <paramref name="useDefaultIfNotFound"/> is <see langword="true"/>; otherwise the default value of <typeparamref name="TReturn"/></returns>
		TReturn ExecuteExactMatch(TEnum value, TParameterMethodParameters(2), bool useDefaultIfNotFound);											
	};

	GenericEnumDelegateMapParameters(3) public ref class ParameterizedEnumDelegateMap3
	{																																								
	private:																																						
		static IEqualityComparer<TEnum>^ s_comparer = Enums::EqualityComparer<TEnum>();																				
		EnumDelegateMapPrivatePropertiesParams(3)																									
	public:
		/// <summary>Creates a new instance without a default delegate.</summary>
		ParameterizedEnumDelegateMap3();																											
		/// <summary>Creates a new instance with <paramref name="defaultDelegate"/> that will execute when a match is not found.</summary>
		/// <param name="defaultDelegate">The default delegate to execute when a match is not found</param>		
		ParameterizedEnumDelegateMap3(FuncTEnumTParametersTReturn(3) defaultDelegate);											
		/// <summary>Creates a new instance with <paramref name="delegateMatches"/> that will call the delegate assigned to the value field when a key match occurs.</summary>
		/// <param name="delegateMatches">A dictionary containing enum values and their matching delegates to execute</param>
		ParameterizedEnumDelegateMap3(IDictionaryTEnumFunc(3) delegateMatches);													
		/// <summary>Creates a new instance with <paramref name="delegateMatches"/> that will call the delegate assigned to the value field when a key match occurs and a <paramref name="defaultDelegate"/> that will execute when a match is not found.</summary>
		/// <param name="delegateMatches">A dictionary containing enum values and their matching delegates to execute</param>
		/// <param name="defaultDelegate">The default delegate to execute when a match is not found</param>		
		ParameterizedEnumDelegateMap3(IDictionaryTEnumFunc(3) delegateMatches, FuncTEnumTParametersTReturn(3) defaultDelegate); 
		/// <summary>Assigns the <paramref name="delegateFunction"/> to a match <paramref name="value"/></summary>
		/// <remarks>The match must either be an exact match (if ExecuteExactMatch is called) or match one of the flags passed in to ExecuteFlagsMatches.  If the value contains more than one flag, it will only execute if
		/// the call matches the flags exactly or a call to ExecuteFlagsMatches contains at least the flags provided.</remarks>
		/// <param name="value">The value to match (see remarks)</param>
		/// <param name="delegateFunction">The method to execute on a successful match</param>		
		void AssignToExactValue(TEnum value, FuncTEnumTParametersTReturn(3) delegateFunction);														
		/// <summary>
		/// Assigns the <paramref name="delegateFunction"/> individually to each flag of <paramref name="value"/>
		/// </summary>
		/// <remarks>The match must either be an exact match of the individual flag (if ExecuteExactMatch is called) or match one of the flags passed in to ExecuteFlagsMatches.</remarks>
		/// <param name="value">The value to match (see remarks)</param>
		/// <param name="delegateFunction">The method to execute on a successful match</param>
		void AssignToEachFlag(TEnum value, FuncTEnumTParametersTReturn(3) delegateFunction);														
		/// <summary>Executes the method if it exactly matches an assigned value or if one of the flags of <paramref name="value"/> matches a value assigned to a method.  Does not execute the default delegate if no matches are found.</summary>
		/// <param name="value">The flags value to look for assigned delegates</param>
		/// <param name="param">The first parameter to pass into the delegate for execution.</param>
		/// <param name="param1">The second parameter to pass into the delegate for execution.</param>
		/// <param name="param2">The third parameter to pass into the delegate</param>
		/// <param name="param3">The fourth parameter to pass into the delegate</param>
		/// <returns>A dictionary containing the matched flag and the value the delegate returned.</returns>
		FlagsMachesReturn ExecuteFlagsMatches(TEnum value, TParameterMethodParameters(3));															
		/// <summary>Executes the method if it exactly matches an assigned value or if one of the flags of <paramref name="value"/> matches a value assigned to a method.  Does not execute the default delegate if no matches are found.</summary>
		/// <param name="value">The flags value to look for assigned delegates</param>
		/// <param name="param">The first parameter to pass into the delegate for execution.</param>
		/// <param name="param1">The second parameter to pass into the delegate for execution.</param>
		/// <param name="param2">The third parameter to pass into the delegate</param>
		/// <param name="param3">The fourth parameter to pass into the delegate</param>
		/// <returns>A dictionary containing the matched flag and the value the delegate returned.</returns>
		TReturn ExecuteExactMatch(TEnum value, TParameterMethodParameters(3));																		
		/// <summary>Executes the delegate assigned to the exact value of <paramref name="value"/> or <paramref name="defaultDelegate"/> if it is not <see langword="null"/>.</summary>
		/// <remarks>This method will not execute delegates assigned to a flag component of <paramref name="value"/></remarks>
		/// <param name="value">The value to look for assigned delegates</param>
		/// <param name="param">The first parameter to pass into the delegate</param>
		/// <param name="param1">The second parameter to pass into the delegate</param>
		/// <param name="param2">The third parameter to pass into the delegate</param>
		/// <param name="param3">The fourth parameter to pass into the delegate</param>
		/// <param name="defaultDelegate">The default delegate to execute if a match is not found</param>
		/// <returns>The result of the matched delegate or the result of <paramref name="defaultDelegate"/> if not <see langword="null"/>; otherwise the default value of <typeparamref name="TReturn"/></returns>
		TReturn ExecuteExactMatch(TEnum value, TParameterMethodParameters(3), FuncTEnumTParametersTReturn(3) defaultDelegate);	
		/// <summary>Executes the delegate assigned to the exact value of <paramref name="value"/> or the assigned default delegate if <paramref name="useDefaultIfNotFound"/> is <see langword="true"/>.</summary>
		/// <remarks>This method will not execute delegates assigned to a flag component of <paramref name="value"/></remarks>
		/// <param name="value">The value to look for assigned delegates</param>
		/// <param name="param">The first parameter to pass into the delegate</param>
		/// <param name="param1">The second parameter to pass into the delegate</param>
		/// <param name="param2">The third parameter to pass into the delegate</param>
		/// <param name="param3">The fourth parameter to pass into the delegate</param>
		/// <param name="useDefaultIfNotFound">If <see langword="true"/>, executes The default delegate if one is assigned to this instance.</param>
		/// <returns>The result of the matched delegate or the result of the default if <paramref name="useDefaultIfNotFound"/> is <see langword="true"/>; otherwise the default value of <typeparamref name="TReturn"/></returns>
		TReturn ExecuteExactMatch(TEnum value, TParameterMethodParameters(3), bool useDefaultIfNotFound);											
	};
}