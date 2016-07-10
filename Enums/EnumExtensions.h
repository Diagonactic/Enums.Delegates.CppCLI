#pragma once


namespace Diagonactic {

	/// <summary>
	/// Extension methods for Enum generics
	/// </summary>
	[Extension]
	public ref class EnumExtensions abstract sealed
	{
	public:
		GenericEnumType [Extension] static TEnum AddAllDefinedFlags(TEnum source);

		GenericEnumType	[Extension] static Boolean AreAllFlagsSet(TEnum source, ...array<TEnum>^ flagsToTest);
		
		GenericEnumType	[Extension] static Boolean AreAnyFlagsSet(TEnum source, ...array<TEnum>^ flagsToTest);

		GenericEnumType	[Extension] static Boolean EqualsAny(TEnum source, ...array<TEnum>^ valuesToTest);
		
		GenericEnumType	[Extension] static List<TEnum>^ ToList(TEnum source);

		GenericEnumType	[Extension]	static String^ GetDescription(TEnum source);

		GenericEnumType	[Extension]	static TEnum RemoveFlag(TEnum source, TEnum flagToRemove);

		GenericEnumType	[Extension]	static TEnum ModifyFlag(TEnum source, TEnum flagToRemove, Func<bool>^ condition);

		GenericEnumType	[Extension]	static TEnum ModifyFlag(TEnum source, TEnum flagToRemove, Predicate<TEnum>^ condition);

		GenericEnumType	[Extension]	static TEnum ModifyFlag(TEnum source, TEnum flagToRemove, bool condition);

		GenericEnumType	[Extension]	static TEnum RemoveFlagIf(TEnum source, TEnum flagToRemove, Func<bool>^ condition);

		GenericEnumType	[Extension]	static TEnum RemoveFlagIf(TEnum source, TEnum flagToRemove, Predicate<TEnum>^ condition);

		GenericEnumType	[Extension]	static TEnum RemoveFlagIf(TEnum source, TEnum flagToRemove, bool condition);
		
		GenericEnumType	[Extension]	static TEnum AddFlags(TEnum source, array<TEnum>^ flagsToAdd);
	
		GenericEnumType	[Extension]	static TEnum RemoveFlags(TEnum source, ...array<TEnum>^ flagsToRemove);

		GenericEnumType	[Extension]	static String^ AsString(TEnum source);

		GenericEnumType	[Extension]	static String^ Format(TEnum source, String^ format);

		GenericEnumType	[Extension]	static Object^ AsObject(TEnum value);

		GenericEnumType	[Extension]	static Boolean IsFlagSet(TEnum source, TEnum flagToTest);

		GenericEnumType	[Extension]	static TEnum AddFlag(TEnum source, TEnum flagToSet);

		GenericEnumType	[Extension]	static TEnum AddFlagIf(TEnum source, TEnum flagToSet, Func<bool>^ condition);

		GenericEnumType	[Extension]	static TEnum AddFlagIf(TEnum source, TEnum flagToSet, Predicate<TEnum>^ condition);

		GenericEnumType	[Extension]	static TEnum AddFlagIf(TEnum source, TEnum flagToSet, bool condition);;
	};

}