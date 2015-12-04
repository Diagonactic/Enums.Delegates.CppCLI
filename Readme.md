Enums and Delegates in C++/CLI
==============================

This project provides a set of highly performant generic methods for interacting with Enums.

Enums and Delegates are a fundimental component of .Net, however, as of version 6.0 of the
C# language, there's no way to (directly) constrain a generic parameter to System.Enum or 
System.Delegate.  There's so many reasons to want to do so, not the least of which is the 
set of kludgy static methods on Enum and Delegate that would really benefit from generic
implementations.  This project does just that with a series of helpful static and extension
methods that can be consumed by any .Net Language.

Delegate support at this time should be considered "beta". Enum support is quite solid.

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
result.RemoveFlag(MyEnum.Val3); // MyEnum.Val1 | MyEnum.Val2 | MyEnum.Val4
result.RemoveFlags(MyEnum.Val1, MyEnum.Val4); // MyEnum.Val2

// AddFlagIf, RemoveFlagIf and ModifyFlag all have delegate and predicate overloads.
result = MyEnum.Val1 | MyEnum.Val2
result.AddFlagIf(MyEnum.Val3, () => true); // MyEnum.Val1 | MyEnum.Val2 | MyEnum.Val3
result.AddFlagIf(MyEnum.Val3, (s) => s.IsFlagSet(MyEnum.Val1)); // Val3 already added, same as above
result.AddFlagIf(MyEnum.Val4, true); // MyEnum.Val1 | MyEnum.Val2 | MyEnum.Val3 | MyEnum.Val4

result = MyEnum.Val1 | MyEnum.Val2
result.RemoveFlagIf(MyEnum.Val1, false); // MyEnum.Val1 | MyEnum.Val2
result.RemoveFlagIf(MyEnum.Val1, () => true); // MyEnum.Val2

result = MyEnum.Val1
result.ModifyFlag(MyEnum.Val2, true); // MyEnum.Val1 | MyEnum.Val2 (sets if true)
result.ModifyFlag(MyEnum.Val2, false); // MyEnum.Val1 (removes if false)

```

Testing enum values (AreAny/AreAll)
```c#
MyEnum.Val1.AreAnyFlagsSet(MyEnum.Val1, MyEnum.Val2, MyEnum.Val3); // true
MyEnum.Val1.EqualsAny(MyEnum.Val1, MyEnum.Val2, MyEnum.Val3); // true - like the above but for non-flags enums
MyEnum.Val1.AreAllFlagsSet(MyEnum.Val1, MyEnum.Val2, MyEnum.Val3); // false
MyEnum.Val1.IsFlagSet(MyEnum.Val1); // true - performs better than HasFlag
MyEnum.Val1.IsFlagSet(MyEnum.Val2); // false
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

Enum Tools
----------
_Enum Equality Comparer_ Unfortunately, when using an enum as a dictionary key or within a HashSet, lookups incur a boxing/unboxing penalty
due to System.Enum not implementing IEquatable.  This makes their use in a HashSet, where performance is often an
important factor, less than ideal.  Once again, the usual solution requires an enum generic constraint that isn't
available in C#.  The generic static method Enum.EqualityComparer() will return a suitable EqualityComparer for
any enum type.  Its implementation uses the underlying type for generating the HashCode.

```c#
var MyDictionary = new Dictionary<MyEnum, SomeOtherType>(Enums.EqualityComparer<MyEnum>());
```

_Flags Enum Definitions_ There are many ways to define a flags enum ranging from the messy decimal based integer to somewhat more
readable hex and shift notations.  With "using static Enums.Flag;" added to your using statement, there's now a third way that's
more readable than any of those.  Each is defined as a constant value using a type that makes them compatible with most of the
allowed underlying enum types.

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


Performance
-----------

Each of the conditional types (AddFlagIf/RemoveFlagIf/ModifyFlag) can be called with a boolean, a
function that returns a boolean or a Predicate delegate which will have its original value passed in
as the parameter.

The library is micro-optimized for execution speed. Where trade-offs between memory utilization
and performance existed, speed was preferred.  Enums are small and the memory used is "per enum type" 
not per instance.  In addition to using high-performing casts, an MSIL project is included which 
rewrites the generic methods that convert from numeric values back to the generic TEnum in a 
"blind cast" sort of manner.

Most of the static methods available in the System.Enum class were re-implemented and perform
significantly faster than the built-in implementations (orders of magnitude in some cases), especially
if a call is made to more than one of the methods in Diagonactic.Enums (there is a small initialization
penalty but it rarely results in the first call taking longer than any of the static calls on 
System.Enum).

The convenience methods, such as AddFlags, are very performant but will never be able to perform as
well (or even close to as well) as direct binary math due to call overhead.  If your code is extremely
sensitive to performance, using the binary math versions will be a better choice.

BenchmarkDotNet was used for performance profiling and the Console.Profile project includes the
tests used to assist in micro-optimization.

See "Performance.md" for the benchmark results and comparisons against identical calls using the static
method versions (where appropriate).

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
