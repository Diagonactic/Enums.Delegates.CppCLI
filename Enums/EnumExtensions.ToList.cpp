#pragma once
#include "stdafx.h"
#include "GenericNumericEnumCore.h"
#include "EnumExtensions.h"

ref class GenericEnumMinimal;

using namespace System;

namespace Diagonactic {

	/// <summary>Convert <paramref name="source"/> to a list</summary>
	/// <param name="source">A flags enum to convert to a list</param>
	/// <typeparam name="TEnum">An enum.</typeparam>
	/// <returns>Returns a list containing all of the flags contained in <paramref name="source"/></returns>
	generic <typename TEnum> where TEnum : IComparable, IFormattable, IConvertible, System::Enum, value class
		List<TEnum>^ EnumExtensions::ToList(TEnum source)
	{
		return Diagonactic::GenericNumericEnumCore<TEnum>::ToList(source);
	}
}