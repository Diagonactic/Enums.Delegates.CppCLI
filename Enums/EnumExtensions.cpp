#include "Stdafx.h"
#include "GenericEnumMinimal.h"
#include "GenericNumericEnumCore.h"
#include "EnumExtensions.h"
#include "GenericEnumCoreDescriptions.h"

ref class GenericNumericEnumCore;


ref class GenericEnumCoreDescriptions;
using namespace System;

namespace Diagonactic {



	/// <summary>
	/// Selectively sets all flags representing a single bit defined on <typeparam name="TEnum"/> (and only those flags), ignoring values that set multiple bits, no bits and all negative values on enums with signed types. Much slower than setting all bits directly (i.e. with <code><see langword="unchecked"/>((type)~0)</code>). See remarks.
	/// </summary>
	/// <remarks>
	/// This method sets all flags defined on <typeparam name="TEnum"/> by evaluating TEnum for all options and adding the flags.  It will only work reliably on 
	/// flags enums that contain legal flag values and evaluates them from top to bottom. If a flag value contains a positive non-flag value, it will be |ed with the combined flag
	/// value and the results will likely not be what you were trying to accomplish
	/// </remarks>
	/// <param name="source"></param>
	/// <returns></returns>
	GenericEnumType	TEnum EnumExtensions::AddAllDefinedFlags(TEnum source) 
	{
		auto allFlags = Diagonactic::GenericNumericEnumCore<TEnum>::ToArray();
		return Diagonactic::GenericNumericEnumCore<TEnum>::AddFlagsSpecial(allFlags, source);
	}

	/// <summary>
	/// Converts an <typeparamref name="TEnum"/> to a string.
	/// </summary>
	/// <param name="source"></param>
	/// <typeparam name="TEnum">An <see langword="enum"/> (<see cref="System::Enum"/>)</typeparam>
	/// <returns>Comma separated string version of <typeparamref name="TEnum"/></returns>
	GenericEnumType String^ EnumExtensions::AsString(TEnum source)
	{
		return Diagonactic::GenericNumericEnumCore<TEnum>::AsString(source);
	}

	/// <summary>Converts <paramref name="value"/> to an <see cref="System::Object"/></summary>
	/// <param name="value">The value to convert to <see cref="System::Object"/></param>
	/// <returns>An <see cref="System::Object"/> of <paramref name="value"/>.</returns>
	/// <typeparam name="TEnum">An <see langword="enum"/> (<see cref="System::Enum"/>)</typeparam>
	GenericEnumType	Object^ EnumExtensions::AsObject(TEnum value)
	{
		return Enum::ToObject(TEnum::typeid, value);
	}

	/// <summary>Gets the value of the <c>DescriptionAttribute</c> attribute associated with <paramref name="source"/>. If no description attribute is present, attempts to return a friendly name based on parsing for camelhumps or underscores and reformatting.</summary>
	/// <remarks>Requires a single, constant value. This will not parse flags for compound values.</remarks>
	/// <param name="source">The enum to get the description attribute from</param>
	/// <typeparam name="TEnum">An <see langword="enum"/> (<see cref="System::Enum"/>)</typeparam>
	/// <returns>The value of the description, or <see langword="null"/> if the value was not found.</returns>
	GenericEnumType	String^ EnumExtensions::GetDescription(TEnum source)
	{
		return GenericEnumCoreDescriptions<TEnum>::TryGetDescription(source);
	}

	/// <summary>A generic version of <c>Enum.Format</c>.</summary>
	/// <remarks>This is also the equivalent of <c>Enum.ToString()</c> with all of the performance penalities associated.</remarks>
	/// <param name="source">The enum to format</param>		
	/// <param name="format">A format string to apply</param>
	/// <typeparam name="TEnum">An <see langword="enum"/> (<see cref="System::Enum"/>)</typeparam>
	/// <returns>A formatted representation of <paramref name="source"/></returns>
	GenericEnumType	String^ EnumExtensions::Format(TEnum source, String^ format)
	{
		return Enum::Format(TEnum::typeid, source, format);
	}

	/// <summary>Determines if <paramref name="source"/> has the <paramref name="flagToTest"/></summary>	
	/// <remarks>A flag value of "0" is considered "None", therefore a flag will not be considered set unless <paramref name="source"/> is 0.</remarks>
	/// <param name="source">The value to test for a flag being set</param>
	/// <param name="flagToTest"></param>
	/// <typeparam name="TEnum">An <see langword="enum"/> (<see cref="System::Enum"/>)</typeparam>
	/// <returns><see langword="true"/> if <paramref name="source"/> contains <paramref name="flagToTest"/></returns>
	GenericEnumType	Boolean EnumExtensions::IsFlagSet(TEnum source, TEnum flagToTest)
	{
		return Diagonactic::GenericEnumMinimal<TEnum>::IsFlagSet(source, flagToTest);
	}

	/// <summary>
	///		Adds <paramref name="flagToSet"/> to <paramref name="source"/> flags enum using a binary math operation applied to the underlying 
	///		type of <typeparamref name="TEnum"/>.
	/// </summary>
	/// <param name="source">The value to apply the add operation to.</param>
	/// <param name="flagToSet">The flag to add to <paramref name="source"/></param>
	/// <typeparam name="TEnum">An <see langword="enum"/> (<see cref="System::Enum"/>)</typeparam>
	/// <returns><paramref name="source"/> with <paramref name="flagToSet"/> added.</returns>
	GenericEnumType	TEnum EnumExtensions::AddFlag(TEnum source, TEnum flagToSet)
	{
		return Diagonactic::GenericEnumMinimal<TEnum>::AddFlag(source, flagToSet);
	}

	/// <summary>
	///		Adds <paramref name="flagToSet"/> to <paramref name="source"/> flags enum if condition evaluates to true.
	/// </summary>
	/// <param name="source">The value to apply the add operation to.</param>
	/// <param name="flagToSet">The flag to add to <paramref name="source"/></param>
	/// <param name="condition">A delegate to evaluate to determine if <paramref name="flagToSet"/> should be set.</param>
	/// <typeparam name="TEnum">An <see langword="enum"/> (<see cref="System::Enum"/>)</typeparam>
	/// <exception cref="ArgumentNullException"><paramref name="condition"/> cannot be <see langword="null"/></exception>
	/// <returns>If <paramref name="condition"/> evaluates to true, <paramref name="source"/> with <paramref name="flagToSet"/> added; otherwise <paramref name="source"/> is returned.</returns>
	GenericEnumType	TEnum EnumExtensions::AddFlagIf(TEnum source, TEnum flagToSet, Func<bool>^ condition)
	{
		if (condition == nullptr) throw gcnew ArgumentNullException("condition");
		if (!condition())
			return source;

		return EnumExtensions::AddFlag(source, flagToSet);
	}

	/// <summary>
	///		Adds <paramref name="flagToSet"/> to <paramref name="source"/> flags enum if condition evaluates to true.
	/// </summary>
	/// <param name="source">The value to apply the add operation to.</param>
	/// <param name="flagToSet">The flag to add to <paramref name="source"/></param>
	/// <param name="condition">A delegate to evaluate to determine if <paramref name="flagToSet"/> should be set.</param>
	/// <remarks>Delegate receives <paramref name="source"/> before modification as its parameter</remarks>
	/// <typeparam name="TEnum">An <see langword="enum"/> (<see cref="System::Enum"/>)</typeparam>
	/// <exception cref="ArgumentNullException"><paramref name="condition"/> cannot be <see langword="null"/></exception>
	/// <returns>If <paramref name="condition"/> evaluates to true, <paramref name="source"/> with <paramref name="flagToSet"/> added; otherwise <paramref name="source"/> is returned.</returns>
	GenericEnumType	TEnum EnumExtensions::AddFlagIf(TEnum source, TEnum flagToSet, Predicate<TEnum>^ condition)
	{
		if (condition == nullptr) throw gcnew ArgumentNullException("condition");
		if (!condition(source))
			return source;

		return EnumExtensions::AddFlag(source, flagToSet);
	}


	/// <summary>
	///		Adds <paramref name="flagToSet"/> to <paramref name="source"/> flags enum if condition is true.
	/// </summary>
	/// <param name="source">The value to apply the add operation to.</param>
	/// <param name="flagToSet">The flag to add to <paramref name="source"/></param>
	/// <param name="condition">A delegate to evaluate to determine if <paramref name="flagToSet"/> should be set.</param>
	/// <typeparam name="TEnum">An <see langword="enum"/> (<see cref="System::Enum"/>)</typeparam>
	/// <returns>If <paramref name="condition"/> evaluates to true, <paramref name="source"/> with <paramref name="flagToSet"/> added; otherwise <paramref name="source"/> is returned.</returns>
	GenericEnumType	TEnum EnumExtensions::AddFlagIf(TEnum source, TEnum flagToSet, bool condition)
	{
		if (!condition)
			return source;

		return EnumExtensions::AddFlag(source, flagToSet);
	}

	/// <summary>
	///		Removes <paramref name="flagToRemove"/> from <paramref name="source"/> flags enum if condition evaluates to true.
	/// </summary>
	/// <param name="source">The value to apply the add operation to.</param>
	/// <param name="flagToRemove">The flag to remove from <paramref name="source"/></param>
	/// <param name="condition">A delegate to evaluate to determine if <paramref name="flagToSet"/> should be set.</param>
	/// <typeparam name="TEnum">An <see langword="enum"/> (<see cref="System::Enum"/>)</typeparam>
	/// <exception cref="ArgumentNullException"><paramref name="condition"/> cannot be <see langword="null"/></exception>
	/// <returns>If <paramref name="condition"/> evaluates to true, <paramref name="source"/> with <paramref name="flagToRemove"/> removed; otherwise <paramref name="source"/> is returned.</returns>
	GenericEnumType	TEnum EnumExtensions::RemoveFlagIf(TEnum source, TEnum flagToRemove, Func<bool>^ condition)
	{
		if (condition == nullptr) throw gcnew ArgumentNullException("condition");

		return EnumExtensions::RemoveFlagIf(source, flagToRemove, condition());
	}

	/// <summary>
	///		Removes <paramref name="flagToRemove"/> from <paramref name="source"/> flags enum if condition evaluates to true.
	/// </summary>
	/// <param name="source">The value to apply the add operation to.</param>
	/// <param name="flagToRemove">The flag to remove from <paramref name="source"/></param>
	/// <param name="condition">A delegate to evaluate to determine if <paramref name="flagToSet"/> should be set.</param>
	/// <remarks>Delegate receives <paramref name="source"/> before modification as its parameter</remarks>
	/// <typeparam name="TEnum">An <see langword="enum"/> (<see cref="System::Enum"/>)</typeparam>
	/// <exception cref="ArgumentNullException"><paramref name="condition"/> cannot be <see langword="null"/></exception>
	/// <returns>If <paramref name="condition"/> evaluates to true, <paramref name="source"/> with <paramref name="flagToRemove"/> removed; otherwise <paramref name="source"/> is returned.</returns>
	GenericEnumType	TEnum EnumExtensions::RemoveFlagIf(TEnum source, TEnum flagToRemove, Predicate<TEnum>^ condition)
	{
		if (condition == nullptr) throw gcnew ArgumentNullException("condition");
		
		return EnumExtensions::RemoveFlagIf(source, flagToRemove, condition(source));
	}

	/// <summary>
	///		Removes <paramref name="flagToRemove"/> from <paramref name="source"/> flags enum if condition is true.
	/// </summary>
	/// <param name="source">The value to apply the add operation to.</param>
	/// <param name="flagToRemove">The flag to remove from <paramref name="source"/></param>
	/// <param name="condition">A delegate to evaluate to determine if <paramref name="flagToSet"/> should be set.</param>
	/// <typeparam name="TEnum">An <see langword="enum"/> (<see cref="System::Enum"/>)</typeparam>
	/// <returns>If <paramref name="condition"/> evaluates to true, <paramref name="source"/> with <paramref name="flagToRemove"/> removed; otherwise <paramref name="source"/> is returned.</returns>
	GenericEnumType	TEnum EnumExtensions::RemoveFlagIf(TEnum source, TEnum flagToRemove, bool condition)
	{
		if (!condition)
			return source;

		return EnumExtensions::RemoveFlag(source, flagToRemove);
	}

	/// <summary>
	///		Modifies <paramref name="source"/> with <paramref name="flagToModify"/> set if <paramref name="condition"/> evaluates to <see langword="true"/>; otherwise, <paramref name="flagToModify"/> will be removed from <paramref name="source"/>.	
	/// </summary>
	/// <param name="source">The value to apply the add operation to.</param>
	/// <param name="flagToModify">The flag to remove from <paramref name="source"/></param>
	/// <param name="condition">A delegate to evaluate to determine if <paramref name="flagToSet"/> should be set.</param>
	/// <typeparam name="TEnum">An <see langword="enum"/> (<see cref="System::Enum"/>)</typeparam>
	/// <exception cref="ArgumentNullException"><paramref name="condition"/> cannot be <see langword="null"/></exception>
	/// <returns>If <paramref name="condition"/> evaluates to true, <paramref name="source"/> with <paramref name="flagToRemove"/> removed; otherwise <paramref name="source"/> is returned.</returns>
	GenericEnumType	TEnum EnumExtensions::ModifyFlag(TEnum source, TEnum flagToModify, Func<bool>^ condition)
	{
		if (condition == nullptr) throw gcnew ArgumentNullException("condition");		
		
		return EnumExtensions::ModifyFlag(source, flagToModify, condition());
	}

	/// <summary>
	///		Modifies <paramref name="source"/> with <paramref name="flagToModify"/> set if <paramref name="condition"/> evaluates to <see langword="true"/>; otherwise, <paramref name="flagToModify"/> will be removed from <paramref name="source"/>.	
	/// </summary>
	/// <param name="source">The value to apply the add operation to.</param>
	/// <param name="flagToModify">The flag to remove from <paramref name="source"/></param>
	/// <param name="condition">A delegate to evaluate to determine if <paramref name="flagToSet"/> should be set.</param>
	/// <remarks>Delegate receives <paramref name="source"/> before modification as its parameter</remarks>
	/// <typeparam name="TEnum">An <see langword="enum"/> (<see cref="System::Enum"/>)</typeparam>
	/// <exception cref="ArgumentNullException"><paramref name="condition"/> cannot be <see langword="null"/></exception>
	/// <returns>If <paramref name="condition"/> evaluates to true, <paramref name="source"/> with <paramref name="flagToRemove"/> removed; otherwise <paramref name="source"/> is returned.</returns>
	GenericEnumType	TEnum EnumExtensions::ModifyFlag(TEnum source, TEnum flagToModify, Predicate<TEnum>^ condition)
	{
		if (condition == nullptr) throw gcnew ArgumentNullException("condition");

		return EnumExtensions::ModifyFlag(source, flagToModify, condition(source));
	}

	/// <summary>
	///		Modifies <paramref name="source"/> with <paramref name="flagToModify"/> set if <paramref name="condition"/> is <see langword="true"/>; otherwise, <paramref name="flagToModify"/> will be removed from <paramref name="source"/>.	
	/// </summary>
	/// <param name="source">The value to apply the add operation to.</param>
	/// <param name="flagToModify">The flag to remove from <paramref name="source"/></param>
	/// <param name="condition">A delegate to evaluate to determine if <paramref name="flagToSet"/> should be set.</param>
	/// <typeparam name="TEnum">An <see langword="enum"/> (<see cref="System::Enum"/>)</typeparam>
	/// <returns>If <paramref name="condition"/> evaluates to true, <paramref name="source"/> with <paramref name="flagToRemove"/> removed; otherwise <paramref name="source"/> is returned.</returns>
	GenericEnumType	TEnum EnumExtensions::ModifyFlag(TEnum source, TEnum flagToModify, bool condition)
	{
		if (condition)
			return EnumExtensions::AddFlag(source, flagToModify);
		else
			return EnumExtensions::RemoveFlag(source, flagToModify);
	}
	/// <summary>Removes <paramref name="flagToRemove"/> from <paramref name="source"/> flags enum using a binary math operation applied to the underlying type of <typeparamref name="TEnum"/>.</summary>
	/// <param name="source">The value to apply the add operation to.</param>
	/// <param name="flagToRemove">The flag to remove from <paramref name="source"/></param>
	/// <typeparam name="TEnum">An <see langword="enum"/> (<see cref="System::Enum"/>)</typeparam>
	/// <returns>The <paramref name="source"/> with <paramref name="flagToRemove"/> added.</returns>
	GenericEnumType	TEnum EnumExtensions::RemoveFlag(TEnum source, TEnum flagToRemove)
	{
		return Diagonactic::GenericEnumMinimal<TEnum>::RemoveFlag(source, flagToRemove);
	}

	/// <summary>Convert <paramref name="source"/> to a list</summary>
	/// <param name="source">A flags enum to convert to a list</param>
	/// <typeparam name="TEnum">An enum.</typeparam>
	/// <returns>Returns a list containing all of the flags contained in <paramref name="source"/></returns>
	GenericEnumType List<TEnum>^ EnumExtensions::ToList(TEnum source)
	{
		return Diagonactic::GenericNumericEnumCore<TEnum>::ToList(source);
	}
	
	

}