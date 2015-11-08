Enums and Delegates in C++/CLI
==============================

Enums and Delegates are a fundimental component of .Net, however, as of version 6.0 of the
C# language, there's no way to (directly) constrain a generic parameter to System.Enum or 
System.Delegate.  There's so many reasons to want to do so, not the least of which is the 
set of kludgy static methods on Enum and Delegate that would really benefit from generic
implementations.  This project does just that with a series of helpful static and extension
methods that can be consumed by any .Net Language.

Delegate support at this time should be considered "beta". Enum support is quite solid.

A great deal of care was taken to ensure that this implementation is extremely fast.  Where
trade-offs between memory and speed were possible, speed was preferred. Enums are small and
the memory used is "per type" not per instance.  In addition to using high-performing casts,
an MSIL project is included which rewrites the generic methods that convert from numeric
values back to the generic TEnum in a "blind cast" sort of manner.

See "Methodology.md" for more information

Installing
----------
The easiest way to get the application is via NuGet.

```
Install-Package DiagonacticEnumsExtensions
```

Enum Methods
------------
Convert an enum to a string (with caching; see Methodology.md). Performs anywhere from 1.5-10 
times faster than ToString() with greatest performance on single enum values (16 times faster 
in unrealistic unit tests provided):
```c#
MyEnum.MyEnumValue.AsString();
```

Parses a string value or comma-separated string values to the enum type provided:
```c#
Enums.Parse<MyEnum>("MyEnumValue");
```

Flag manipulation:
```c#
var result = MyEnum.Val1.AddFlag(MyEnum.Val2);  // MyEnum.Val1 | MyEnum.Val2
result.AddFlags(MyEnum.Val3, MyEnum.Val4); // MyEnum.Val1 | MyEnum.Val2 | MyEnum.Val3 | MyEnum.Val4
result.AddFlagIf(MyEnum.Val3, () => true); // MyEnum.Val1 | MyEnum.Val2 | MyEnum.Val3
result.AddFlagIf(MyEnum.Val3, (s) => s.IsFlagSet(MyEnum.Val1)); // MyEnum.Val1 | MyEnum.Val2 | MyEnum.Val3
result.AddFlagIf(MyEnum.Val3, true); // MyEnum.Val1 | MyEnum.Val2 | MyEnum.Val3
result.AddFlagIf(MyEnum.Val3, false); // MyEnum.Val1 | MyEnum.Val2 | MyEnum.Val3
result.RemoveFlagIf(MyEnum.Val1, false); // MyEnum.Val1 | MyEnum.Val2
result.RemoveFlagIf(MyEnum.Val1, () => true); // MyEnum.Val2
result.ModifyFlag(MyEnum.Val2, true); // MyEnum.Val1 | MyEnum.Val2 (sets if true, removes if false -- Delegate removal overload available, too)
result.RemoveFlag(MyEnum.Val3); // MyEnum.Val1 | MyEnum.Val2 | MyEnum.Val4
result.RemoveFlags(MyEnum.Val1, MyEnum.Val4); // MyEnum.Val2
var isSet = result.IsFlagSet(MyEnum.Val3); // false
```

Get the value of the DescriptionAttribute.Description or convert MyEnumValue to "My Enum Value"
if DescriptionAttribute is missing:
```c#
MyEnum.MyEnumValue.GetDescription();
```

Convert an underlying type (numeric) value to the enum type:
```c#
Enums.ToEnum(1); // MyEnum.Val1
Enums.ToEnum(3); // MyEnum.Val1 | mMynum.Val2
```

Define a flags enum conveniently (C# 6.0):
```c#
using static Enums.Flag

[Flags]
enum FlagsEnum : byte
{
	FirstFlag = F1,
	SecondFlag = F2,
	ThirdFlag = F3,
	// ... types encoded from byte to Int64 for (near) universal usage ...
}
```

Each of the conditional types (AddFlagIf/RemoveFlagIf/ModifyFlag) can be called with a boolean, a
function that returns a boolean or a Predicate delegate which will have its original value passed in
as the parameter.
Compiling
---------

Simply grab the repo via git, open in Visual Studio 2015, and run Build.  Visual Studio will
build the C++ project last and execute the MSIL conversion after build.  If you wish to work
with the library without the MSIL conversion, either switch to the Debug build or 
remove the post-build command from the Release mode.

Note that the C++/CLI project claims to be in "x64" configuration.  It's not accurate; the
project compiles in "AnyCPU" mode with no 32-bit preference applied.  C++/CLI has no "AnyCPU"
built-in mode but with the right settings in the project, one can be created when the library
code can be fully represented in MSIL.  Yay! No Side-by-Side nonsense.

Documentation
-------------
It's well documented using XML docs and SandCastle (which produces a CHM, and web site).
