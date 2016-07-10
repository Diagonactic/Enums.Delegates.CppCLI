#include "Stdafx.h"
#include "GenericNumericEnumCore.h"
#include "EnumExtensions.h"
#include "GenericEnumCoreDescriptions.h"

ref class GenericEnumMinimal;

using namespace System;

namespace Diagonactic {

	/// <summary>
	///		Checks if <paramref name="flagsToTest"/> are all set on <paramref name="source"/> flags enum using a binary math operation applied to the underlying 
	///		type of <typeparamref name="TEnum"/>.
	/// </summary>
	/// <remarks>A flag value of "0" is considered "None", therefore a flag will not be considered set unless <paramref name="source"/> is 0.</remarks>
	/// <param name="source">The value to check for flags.</param>
	/// <param name="flagsToTest">The flags to check against <paramref name="source"/></param>
	/// <typeparam name="TEnum">An <see langword="enum"/> (<see cref="System::Enum"/>)</typeparam>
	/// <returns><see langword="true"/> if all flags in <paramref name="flagsToTest"/> are set in <paramref name="source"/>.</returns>
	GenericEnumType	Boolean EnumExtensions::AreAllFlagsSet(TEnum source, ...array<TEnum>^ flagsToTest)
	{
		return GenericEnumMinimal<TEnum>::AreAllFlagsSet(flagsToTest, source);
	}
}