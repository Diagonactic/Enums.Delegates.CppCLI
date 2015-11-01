#pragma once
#include "stdafx.h"
#include "EnumExtensions.h"

ref class GenericEnumMinimal;

using namespace System;

namespace Diagonactic {

	/// <summary>
	///		Adds <paramref name="flagsToAdd"/> to <paramref name="source"/> flags enum using a binary math operation applied to the underlying 
	///		type of <typeparamref name="TEnum"/>.
	/// </summary>
	/// <param name="source">The value to apply the add operation to.</param>
	/// <param name="flagsToAdd">The flag to add to <paramref name="source"/></param>
	/// <typeparam name="TEnum">An <see langword="enum"/> (<see cref="System::Enum"/>)</typeparam>
	/// <returns><paramref name="source"/> with <paramref name="flagsToAdd"/> added.</returns>
	generic <typename TEnum> where TEnum: IComparable, IFormattable, IConvertible, System::Enum
		TEnum EnumExtensions::AddFlags(TEnum source, ...array<TEnum>^ flagsToAdd)
	{
		return GenericEnumMinimal<TEnum>::AddFlags(flagsToAdd, source);
	}
}