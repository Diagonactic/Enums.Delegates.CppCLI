// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently,
// but are changed infrequently

#pragma once
#include "Util.h"
#include "MsilConvert.h"

#using <C:\Src\EnumCpp\External Dependencies\JetBrains.Annotations.PCL328.dll>
#using <C:\Program Files (x86)\Reference Assemblies\Microsoft\Framework\.NETCore\v4.5\System.Linq.Dll>

#define GenericEnumTypeConstraint(name) where name : IComparable, IFormattable, IConvertible, System::Enum, value class
#define GenericEnumTypeName(name) generic <typename name> GenericEnumTypeConstraint(name)
#define GenericEnumType GenericEnumTypeName(TEnum)