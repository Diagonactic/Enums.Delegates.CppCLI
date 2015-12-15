#pragma once
#include "GenericEnumCoreDescriptions.h"

using namespace JetBrains::Annotations;

namespace Diagonactic {

	/// <summary>
	/// Extension methods for Enum generics
	/// </summary>
	[Extension]
	public ref class EnumExtensions abstract sealed
	{
	public:
		generic <typename TEnum> where TEnum : IComparable, IFormattable, IConvertible, System::Enum, value class
			[Extension] static Boolean AreAllFlagsSet(TEnum source, ...array<TEnum>^ flagsToTest);
		
		generic <typename TEnum> where TEnum : IComparable, IFormattable, IConvertible, System::Enum, value class
			[Extension] static Boolean AreAnyFlagsSet(TEnum source, ...array<TEnum>^ flagsToTest);

		generic <typename TEnum> where TEnum : IComparable, IFormattable, IConvertible, System::Enum, value class
			[Extension] static Boolean EqualsAny(TEnum source, ...array<TEnum>^ valuesToTest);
		
		generic <typename TEnum> where TEnum : IComparable, IFormattable, IConvertible, System::Enum, value class
			[Extension, NotNull] static List<TEnum>^ ToList(TEnum source);

		generic <typename TEnum> where TEnum : IComparable, IFormattable, IConvertible, System::Enum, value class
			[Extension, CanBeNull]	static String^ GetDescription(TEnum source);

		generic <typename TEnum> where TEnum : IComparable, IFormattable, IConvertible, System::Enum, value class
			[Extension]	static TEnum RemoveFlag(TEnum source, TEnum flagToRemove);

		generic <typename TEnum> where TEnum : IComparable, IFormattable, IConvertible, System::Enum, value class
			[Extension]	static TEnum ModifyFlag(TEnum source, TEnum flagToRemove, Func<bool>^ condition);

		generic <typename TEnum> where TEnum : IComparable, IFormattable, IConvertible, System::Enum, value class
			[Extension]	static TEnum ModifyFlag(TEnum source, TEnum flagToRemove, [NotNull] Predicate<TEnum>^ condition);

		generic <typename TEnum> where TEnum : IComparable, IFormattable, IConvertible, System::Enum, value class
			[Extension]	static TEnum ModifyFlag(TEnum source, TEnum flagToRemove, bool condition);

		generic <typename TEnum> where TEnum : IComparable, IFormattable, IConvertible, System::Enum, value class
			[Extension]	static TEnum RemoveFlagIf(TEnum source, TEnum flagToRemove, [NotNull] Func<bool>^ condition);

		generic <typename TEnum> where TEnum : IComparable, IFormattable, IConvertible, System::Enum, value class
			[Extension]	static TEnum RemoveFlagIf(TEnum source, TEnum flagToRemove, [NotNull] Predicate<TEnum>^ condition);

		generic <typename TEnum> where TEnum : IComparable, IFormattable, IConvertible, System::Enum, value class
			[Extension]	static TEnum RemoveFlagIf(TEnum source, TEnum flagToRemove, bool condition);
		
		generic <typename TEnum> where TEnum : IComparable, IFormattable, IConvertible, System::Enum, value class
			[Extension]	static TEnum AddFlags(TEnum source, array<TEnum>^ flagsToAdd);
	
		generic <typename TEnum> where TEnum : IComparable, IFormattable, IConvertible, System::Enum, value class
			[Extension]	static TEnum RemoveFlags(TEnum source, [NotNull]  ...array<TEnum>^ flagsToRemove);

		generic <typename TEnum> where TEnum : IComparable, IFormattable, IConvertible, System::Enum, value class
			[Extension, NotNull]	static String^ AsString(TEnum source);

		generic <typename TEnum> where TEnum : IComparable, IFormattable, IConvertible, System::Enum, value class
			[Extension, NotNull]	static String^ Format(TEnum source, [NotNull] String^ format);

		generic <typename TEnum> where TEnum : IComparable, IFormattable, IConvertible, System::Enum, value class
			[Extension, NotNull]	static Object^ AsObject(TEnum value);

		generic <typename TEnum> where TEnum : IComparable, IFormattable, IConvertible, System::Enum, value class
			[Extension]	static Boolean IsFlagSet(TEnum source, TEnum flagToTest);

		generic <typename TEnum> where TEnum : IComparable, IFormattable, IConvertible, System::Enum, value class
			[Extension]	static TEnum AddFlag(TEnum source, TEnum flagToSet);

		generic <typename TEnum> where TEnum : IComparable, IFormattable, IConvertible, System::Enum, value class
			[Extension]	static TEnum AddFlagIf(TEnum source, TEnum flagToSet, [NotNull] Func<bool>^ condition);

		generic <typename TEnum> where TEnum : IComparable, IFormattable, IConvertible, System::Enum, value class
			[Extension]	static TEnum AddFlagIf(TEnum source, TEnum flagToSet, [NotNull] Predicate<TEnum>^ condition);

		generic <typename TEnum> where TEnum : IComparable, IFormattable, IConvertible, System::Enum, value class
			[Extension]	static TEnum AddFlagIf(TEnum source, TEnum flagToSet, bool condition);;
	};

}