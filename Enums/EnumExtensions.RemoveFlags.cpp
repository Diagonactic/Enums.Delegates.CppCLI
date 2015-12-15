#pragma once
#include "stdafx.h"
#include "EnumExtensions.h"

ref class GenericEnumMinimal;

using namespace System;

namespace Diagonactic {
	/// <summary>
	///		Removes <paramref name="flagsToRemove"/> from <paramref name="source"/> flags enum using a binary math operation applied to the
	///		underlying type of <typeparamref name="TEnum"/>.
	/// </summary>
	/// <param name="source">The value to apply the remove operation to.</param>
	/// <param name="flagsToRemove">The flag to remove from <paramref name="source"/></param>
	/// <typeparam name="TEnum">An <see langword="enum"/> (<see cref="System::Enum"/>)</typeparam>
	/// <returns>The <paramref name="source"/> with <paramref name="flagsToRemove"/> removed.</returns>
	generic <typename TEnum> where TEnum : IComparable, IFormattable, IConvertible, System::Enum, value class
		TEnum EnumExtensions::RemoveFlags(TEnum source, [NotNull] ...array<TEnum>^ flagsToRemove)
	{
		// Ok, so if this stupid damn method is moved to the EnumExtensions.h file below AddFlags, it won't compile (put it above and AddFlags won't compile).
 		// So this is a kludge and it's driving me crazy.
		return GenericEnumMinimal<TEnum>::RemoveFlags(source, flagsToRemove);
	};
}