#pragma once
#include "stdafx.h"
#include "EnumExtensions.h"

ref class GenericEnumMinimal;

using namespace System;

namespace Diagonactic {

	/// <summary>
	///		Checks if any <paramref name="valuesToTest"/> are equal to <paramref name="source"/> enum.
	/// </summary>
	/// <param name="source">The value to check for flags.</param>
	/// <param name="valuesToTest">The values to check against <paramref name="source"/></param>
	/// <typeparam name="TEnum">An <see langword="enum"/> (<see cref="System::Enum"/>)</typeparam>
	/// <returns><see langword="true"/> if <paramref name="source"/> is equal to any of the <paramref name="valuesToTest"/>; <see langword="false"/> none are equal.</returns>
	generic <typename TEnum> where TEnum: IComparable, IFormattable, IConvertible, System::Enum
		Boolean EnumExtensions::EqualsAny(TEnum source, ...array<TEnum>^ valuesToTest)
	{
		return GenericEnumMinimal<TEnum>::EqualsAny(valuesToTest, source);
	}
}