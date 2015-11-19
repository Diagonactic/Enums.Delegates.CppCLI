#pragma once
#include "GenericEnumCoreDescriptions.h"

namespace Diagonactic {

	/// <summary>
	/// Extension methods for Enum generics
	/// </summary>
	[Extension]
	public ref class EnumExtensions abstract sealed
	{
	public:
		generic <typename TEnum> where TEnum : IComparable, IFormattable, IConvertible, System::Enum
			[Extension] static Boolean AreAllFlagsSet(TEnum source, ...array<TEnum>^ flagsToTest);
		
		generic <typename TEnum> where TEnum : IComparable, IFormattable, IConvertible, System::Enum
			[Extension] static Boolean AreAnyFlagsSet(TEnum source, ...array<TEnum>^ flagsToTest);

		generic <typename TEnum> where TEnum : IComparable, IFormattable, IConvertible, System::Enum
			[Extension] static Boolean EqualsAny(TEnum source, ...array<TEnum>^ valuesToTest);
		
		generic <typename TEnum> where TEnum : IComparable, IFormattable, IConvertible, System::Enum
			[Extension] static List<TEnum>^ ToList(TEnum source);

		generic <typename TEnum> where TEnum : IComparable, IFormattable, IConvertible, System::Enum
			[Extension]	static String^ GetDescription(TEnum source);

		generic <typename TEnum> where TEnum : IComparable, IFormattable, IConvertible, System::Enum
			[Extension]	static TEnum RemoveFlag(TEnum source, TEnum flagToRemove);

		generic <typename TEnum> where TEnum : IComparable, IFormattable, IConvertible, System::Enum
			[Extension]	static TEnum ModifyFlag(TEnum source, TEnum flagToRemove, Func<bool>^ condition);

		generic <typename TEnum> where TEnum : IComparable, IFormattable, IConvertible, System::Enum
			[Extension]	static TEnum ModifyFlag(TEnum source, TEnum flagToRemove, Predicate<TEnum>^ condition);

		generic <typename TEnum> where TEnum : IComparable, IFormattable, IConvertible, System::Enum
			[Extension]	static TEnum ModifyFlag(TEnum source, TEnum flagToRemove, bool condition);

		generic <typename TEnum> where TEnum : IComparable, IFormattable, IConvertible, System::Enum
			[Extension]	static TEnum RemoveFlagIf(TEnum source, TEnum flagToRemove, Func<bool>^ condition);

		generic <typename TEnum> where TEnum : IComparable, IFormattable, IConvertible, System::Enum
			[Extension]	static TEnum RemoveFlagIf(TEnum source, TEnum flagToRemove, Predicate<TEnum>^ condition);

		generic <typename TEnum> where TEnum : IComparable, IFormattable, IConvertible, System::Enum
			[Extension]	static TEnum RemoveFlagIf(TEnum source, TEnum flagToRemove, bool condition);
		
		generic <typename TEnum> where TEnum : IComparable, IFormattable, IConvertible, System::Enum
			[Extension]	static TEnum AddFlags(TEnum source, array<TEnum>^ flagsToAdd);
	
		generic <typename TEnum> where TEnum : IComparable, IFormattable, IConvertible, System::Enum
			[Extension]	static TEnum RemoveFlags(TEnum source, ...array<TEnum>^ flagsToRemove);

		generic <typename TEnum> where TEnum : IComparable, IFormattable, IConvertible, System::Enum
			[Extension]	static String^ AsString(TEnum source);

		generic <typename TEnum> where TEnum : IComparable, IFormattable, IConvertible, System::Enum
			[Extension]	static String^ Format(TEnum source, String^ format);

		generic <typename TEnum> where TEnum : IComparable, IFormattable, IConvertible, System::Enum
			[Extension]	static Object^ AsObject(TEnum value);

		generic <typename TEnum> where TEnum : IComparable, IFormattable, IConvertible, System::Enum
			[Extension]	static Boolean IsFlagSet(TEnum source, TEnum flagToTest);

		generic <typename TEnum> where TEnum : IComparable, IFormattable, IConvertible, System::Enum
			[Extension]	static TEnum AddFlag(TEnum source, TEnum flagToSet);

		generic <typename TEnum> where TEnum : IComparable, IFormattable, IConvertible, System::Enum
			[Extension]	static TEnum AddFlagIf(TEnum source, TEnum flagToSet, Func<bool>^ condition);

		generic <typename TEnum> where TEnum : IComparable, IFormattable, IConvertible, System::Enum
			[Extension]	static TEnum AddFlagIf(TEnum source, TEnum flagToSet, Predicate<TEnum>^ condition);

		generic <typename TEnum> where TEnum : IComparable, IFormattable, IConvertible, System::Enum
			[Extension]	static TEnum AddFlagIf(TEnum source, TEnum flagToSet, bool condition);;
	};

}