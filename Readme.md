Enums and Delegates in C++/CLI
==============================

This project provides a set of highly performant generic methods for interacting with Enums.

As of C# version 6.0, there is no support for generic enum or delegate constraints.  This 
eliminates a lot of opportunities to make enums easier to work with and use.  

Enums are very performant but their real benefit is providing greater readability to code
that would normally result in flags elements stored with integer/byte values.  Unfortunately,
many of the built-in components for working with Enum values are *not* performant, incurring
boxing penalties, such as when casting to/from underlying values, converting to string, or
using an enum as a key in a Dictionary or within a HashSet.

Readability also suffer when bit operations are used on enums.  Many programmers quickly recognize
the pipe, tilde and amp patterns involved in these operations, but it adds cognitive overhead
since they're not as common or required as they were in C-based languages (indeed, you rarely
see them used *outside* of enum operations in C#).  

This library aims to solve this problem with several generic extension methods and static/instance
helpers hand-tuned and micro-optimised to take away any excuse for performance critical code
to avoid using enums.

Installing
==========

The easiest way to get the application is via NuGet.

```
Install-Package DiagonacticEnumsExtensions
```


Library Design Principals
=========================

C# and VB.Net have always been able to handle a generic constraint for enums and
delegates, they just can't generate a method or class with one attached.  IL and C++/CLI do not
have this limitation, as a result, this library was written in C++/CLI.

It emits an IL-only .dll targeting "AnyCPU" for maximum compatibility and is compiled targetting
.Net Framework 4.5 (prior versions may work, but I haven't tested).

Testing / Benchmarking
----------------------

Due to unsafe operations being performed within the library to eliminate unboxing, the code is
heavily unit tested to validate (when appropriate) proper functioning with enums of every underlying
type at the full boundaries of that type (to uncover incorrect casts such as long->int->long that
could overload).

Performance Characteristics
---------------------------

For full detals, including benchmarks, see performance.md.  When the choice was a memory or speed
trade-off, speed was chosen (the memory trade-off is very small as it is).  Memory usage aims to be
very conservative by ensuring that if a method does not need certain values, memory for those values
is not allocated.

Unsafe Casts: In release mode, all casts are "blind casts" that incur the most minimal cost.

Dictionaries: For each type, Dictionary objects are maintained with the string and description values and
allocated per enum when a method is called requesting the string value (or string mapped to enum value).
Though there's a performance cost to the initial loading of these dictionaries, in most cases the
penalty is less than a single call to the equivalent .Net method.  Subsequent calls can be many
thousands of times faster than these calls.  The dictionaries are also optimised to use an EqualityComparer
that does not incur boxing penalties (and is available for your own use in Enums.EqualityComparer<TEnum>()).

Underlying Values: The application works entirely with the underlying values of the enums throughout
nearly every part of the code using unsafe casts from and to the original enum value.

The only parts of this library that do not perform to the level of the alternatives they replace are
the flag modification operations.  There's just simply no way to beat a logical boolean operation.  However,
if you've gotten used to using HasFlag(), this library's IsFlagSet() method is many times faster than HasFlag
implemented in .Net 4.5+ (as of this writing).

Examples - How To Use
=====================

There is a documentation project included with this library that contains complete documentation.  In addition,
XML-doc comments were used heavily to make usage easy within an intellisense capable environment.

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

Enum Execute Delegate on Match
------------------------------

The EnumDelegateMap method provides a facility to execute a delegate based on an enum value.

Many thanks to Piotr Gankiewicz (piotrgankiewicz.com/2016/07/04/get-rid-of-switchcaseif/) for the
idea to add this to the library.

```c#
var fm = new EnumDelegateMap<LongFlags, int>(); // Declares that a match will allow assignment of functions that return int values
fm.AssignToExactValue(LongFlags.Eight, (f) => 9); // When Eight is matched, return the value 9 (the "f" parameter is assigned to whatever the value is that's passed in on execution, not the matching value)
Console.WriteLine(fm.ExecuteExactMatch(LongFlags.Eight)); // Writes 9

var fm = new EnumDelegateMap<LongFlags, int>((f) => -1); // Declares that a match will allow assignment of functions that return int values. When no match is found, return -1
fm.AssignToExactValue(LongFlags.Eight, (f) => 9); // When Eight is matched, return the value 9
Console.WriteLine(fm.ExecuteExactMatch(LongFlags.Five)); // Writes -1

// Advanced Usage

var fm = new EnumDelegateMap<LongFlags, int>((f) => -1); // Declares that a match will allow assignment of functions that return int values. When no match is found, return -1
fm.AssignToEachFlag(LongFlags.Eight | LongFlags.Five, (f) => 42); // Assign 42 to both Eight and Five
fm.AssignToEactValue(LongFlags.Eight | LongFlags.Five, (f) => 69); // Assigns 69 to the value of Eight combined with Five in a flags enum
Console.WriteLine(fm.ExecuteExactMatch(LongFlags.Five)); // Writes 42
Console.WriteLine(fm.ExecuteExactMatch(LongFlags.Eight)); // Writes 42
Console.WriteLine(fm.ExecuteExactMatch(LongFlags.Five | LongFlags.Eight)); // Writes 69
Console.WriteLine(fm.ExecuteExactMatch(LongFlags.Nine)); // Writes -1

Dictionary<LongFlags, int> results = fm.ExecuteFlagsMatches(LongFlags.Five | LongFlags.Eight);
Console.WriteLine(results.Count) // Writes 3 because we've assigned a method to Five, Eight and Eight|Five
Console.WriteLine(results[LongFlags.Five]) // Writes 42
Console.WriteLine(results[LongFlags.Eight]) // Writes 42
Console.WriteLine(results[LongFlags.Five | LongFlags.Eight]) // Writes 69
```

Enum Performance Tools
----------------------
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


Compiling
---------

Simply grab the repo via git, open in Visual Studio 2015, and run Build.  Visual Studio will
build the C++ project last and execute the MSIL conversion after build (in release mode only) to
add in the blind casts.  If you wish to work with the library without the MSIL conversion, 
either switch to the Debug build or remove the post-build command from the Release mode.  The
code replaced by the MSIL rewriting tool is written using the standard .Net "safe" casts.  Elsewhere
in code, blind casts are used (when they're legal in C++/CLI) -- those will be emitted regardless
of the build type.

Note that the C++/CLI project claims to be in "x64" configuration.  C++/CLI has no "AnyCPU"
built-in mode so this is acheived by using specific build settings that result in an MSIL
"AnyCPU" .dll with no 32-bit preference applied.

Documentation
-------------

The library is well documented using XML docs and SandCastle (which produces a CHM, and web site).
