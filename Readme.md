Enums and Delegates in C++/CLI
==============================

Enums and Delegates are a fundimental component of .Net, however, as of version 6.0 of the
C# language, there's no way to (directly) constrain a generic parameter to System.Enum or 
System.Delegate.  There's so many reasons to want to do so, not the least of which is the 
set of kludgy static methods on Enum and Delegate that would really benefit from generic
implementations.

Enum Methods
------------
Unfortunately, some of the instance and static methods provided to us by Microsoft are *slow*.
Fixing them in code would easily be considered a premature optimisation, but for the rare
occasion that one needs to eek out a few more ms of performance, the options available are
somewhat ugly.  ToString() is the biggest offender and the fix for it is often a switch
statement with string literals.  This is easy to write for small enums, but in a program
that's constantly changing, keeping your string version in sync with your enum is an
extra step you're going to forget.  Alternatively, you could use a Dictionary (and, in
fact, that's what this library does).  It's not so bad, but you'll likely discover after
implementing it for one of your enum types that a generic implementation would be really
useful, only to run into the fact that C# doesn't allow you to do it "correctly".  So you
create a generic implementation using struct, IFormattable, IClonable, and such and cast
away.

The CLR perfectly supports a generic constraint on System.Enum and System.Delegate.  C#
does not (yet ... it will likely appear in C# v7.0 if the issue log is followed).  C# has
no problem consuming a method that has generic constraints on these types, and C++/CLI has 
no problem creating a method or class constrained in this manner.  So that's what I did.

The methods for enum are fully covered by tests and perform very well.  In the case of 
"AsString()", the replacement for ToString(), the performance is anywhere from 2 to 8
times faster after cache initialization (and even with init, it's still slightly faster).

There is a memory penality paid for that performance, though it's small enough and in my
cases, the trade-off was necessary.  You can get descriptions from attribute (or it will
autogenerate descriptions based on the name parsed for camel humps or underscores), 
turn an enum into a string value, parse a string value for the enum, use simple methods
like AddFlags, RemoveFlags, HasFlags to check values of flag enums.  All of the check
and modify methods use direct binary math against the underlying type and all underlying
types are supported on every method.  All casts are done directly (and safely) and all
of the methods are unit tested with 100% code coverage (for code that can actually
execute) and are tested in ways designed -- where possible -- to use the underlying type 
in ways that would be unique to its type.  Boxing during the processing of the method is
avoided everywhere it can be (and might be able to be avoided in the one place it still
happens -- next version!).

Parse, AsString, and HasFlag are functionally equivalent implementations to the Enum 
statics but perform faster than each after cache init.  AsString performs faster for most 
average sized enums of any base type on first call.  Parse and HasFlags are a little
slower on first call.  Each share parts or all of the cache (Parse/AsString share, Descrpition
methods will also initialize everything with the addition of the description information, 
HasFlags and the other methods that are not direct calls to the Enum static initialize part
of the cache).  Following that guidance, for example, a call to Parse will make calls to
AsString run at full speed and vice versa.  I tried to minimize the impact of init and
share everywhere possible.

The slowest perfoming method is GetDescription.  As expected, it uses reflection to get
the DescriptionAttribute's Description value.

AddFlags and RemoveFlags are not as fast as doing it directly but the cost is lower than
you'd expect.  If the enum has already used one of the other methods, it's *very* close,
adding in only the cost of a couple of casts that are done directly to the underlying
type (inexpensive) and one call to a static method on Enum to convert back to the Enum
(a cost which I think I can remove in a future version).

Delegates
---------
I just started this implementation, as such, some of the methods are not fully covered,
though they're simply generic wrappers for the statics on Delegate.  The ones you're
likely to use, like Combine/Remove are covered, but there may be changes here which is
why this project is still beta at the moment.

A Note From the Author on the Code
----------------------------------
A seasoned C++ developer I am not.  I've got a lot of history with C++. Unfortunately, 
it's history.  I stopped developing in that language around 1998.  Recently I started
playing with embedded systems with tiny processors and memory constraints.  Sure, 
there's still support for scripting languages, but the difference in performance is
stark on these platforms, so I decided to brush up on C++.  I'm 6 books and about
10,000 pages in at this point, including two on C++/CLI.  Between C++11 (and later) and
C++/CLI, there's very little from my past experience with C++ that applies.

This is my first *real* project in C++/CLI and the code will likely (hopefully not) make
that point obvious.  It's not nearly as DRY as I would like, mainly due to the need to
use .Net Generics which preclude me from using C++ templates in areas I that they would
really be useful.

You'll notice, in the places I have used C++ templates, that many of the parameters are
void* types.  Those are the generic TEnum, pinned for safety, passed in to the template
to DRY up the code.

There are three real DRY problems: AddFlag used by Parse, ClobberTo's Non-template
implementations and the switch statements used in several places.  The first two I had
converted to templates and then converted back after it adversely affected performance.
I will probably create a text template to generate these methods to meet the goals of
DRY code in spirit if not perfectly.

The problem lies in the fact that the GC does not guarantee a pointer will always point
to the same place in memory.  To get around this, .Net allows you to pin a pointer, which
I am doing on each call to the void* parameterized templates.  I've found pinning to be
far less expensive than it's generally believed to be, however, when I pinned the values
on the Parse method, my profiling showed a 20% decrease in performance over the native
call.

I will probably leave these alone since I'm not sure I can find a way to get them above
the call to .Net's native statics.

The case statements I will refactor when I have time.  It'll likely be pulled into one or
two methods that take a function pointer to perform the operation.  Provided it doesn't
similarly murder performance, I'll refactor it across the 5 or so methods that use it.

For now, to get around that, I've organized them in a precise way to make it easy to 
visually verify that the copy-code is correct (and covered them in unit tests to 
[hopefully] catch them if they are not).

Notes about Compiling
---------------------
C++/CLI does not directly support "AnyCPU".  I've used a work-around to achieve this.
The code is compiled as CLR:Safe and only one profile exists for the Enums project:
x64.  The x64 version *is* AnyCPU (run corflags Enums.dll for proof).  The solution
is compiled to an MSIL only version and PE32 because *most* of what I work with are
.Net applications that are compiled Any CPU.  Unfortunately, I have discovered this
comes at a cost.  I have only done a few quick benchmarks on the x64 and x86 native
versions, but I was seeing between 10% and 400% improvements in speed swiching it to
/clr with a IJW binary and optimisations configured to target the platform I'm directly
running on.  It doesn't make a *ton* of sense to me, so I'm chocking it up to my
profiling at the moment, but I am going to revisit this and see if it would make more
sense to use a side-by-side .dll with a proxy to pick the right version at runtime.

NuGet Package
-------------
I didn't have time this weekend to finish the NuGet package.  Maybe next weekend?  For
now the project is there, but it's not doing anything.

Documentation
-------------
It's well documented using XML docs and SandCastle (which produces a CHM, and web site).