Caching Implementation
----------------------
The first call of AsString and Parse have a penality per type of enum as a result of 
initializing the underlying object that manages the type and it's cached values.  The 
penality for Parse will result in it performing more slowly than native depending on 
the number of elements in the enum (single digit percents in most cases I've tested, 
but I need to do more profiling to get an accurate benchmark).

Calls share cache, so calling Parse followed by AsString results in one "first call penalty",
GetDescription also handles this first call penalty.

Parts of the cache are initialized for the "Flags" methods as well, so if you're doing a few
different Enum operations in extremely performance sensitive code, rest easy.
If speeding up enum operatinos would be a premature optimization (i.e. you wouldn't dream of 
rewriting your code to eliminate Enum.ToString() calls), rest easy in knowing this implementation 
is very performant.

Parse, AsString, and HasFlag are functionally equivalent implementations to the Enum 
statics but perform faster than each after cache init.  

For even somewhat large flags enums, AsString performs better than ToString even on first
call.  AsString can perform dramatically faster if it's used on the same type several times
within an application, especially looped.  There's some very unrealistic tests under the
"Performance" and "Baseline" category that illustrate the speedup.  For single value AsString()
vs ToString(), AsString is 2100% faster (completes in 58ms where the same code calling ToString() 
takes 1241ms -- average over 100 runs with current Runs iterations on three calls) on my Core i7 
laptop.

The tests are unrealsitic.  They were designed to intentionally exaggerate the results so that
small changes made to the runtime would be visible after several tests run with averages. You
can control the number of iterations by changing the "Runs" and "ParseRuns" constants.  You
can run the application under profiler via the Console.Profile project (which takes a parameter
for the number of runs and parse runs).

Parse is about 60% faster in those same unrealistic tests. Internally, .Net's Parse function
is already well performing. Using Parse in this library has the side-effect of initializing
cache, and that's really the only reason I took the time to implement it.

The slowest perfoming method is GetDescription.  As expected, it uses reflection to get
the DescriptionAttribute's Description value.  It's a dog.

AddFlags and RemoveFlags are not as fast as doing it directly but the cost is lower than
you'd expect.  If the enum has already used one of the other methods, it's as close as you
can get.  All conversions are done with blind casts and all operations are binary math,
rather than the internal .Net options (if available).  

MSIL Rewriter
-------------
Unfortunately, there no way (that I could find) to convert from the numeric value back to
the generic TEnum value without an expensive call to Enum::ToObject in "just C++/CLI code".
It's completely possible to do. If you have a valid numeric value that maps to an enum value
or a group of enum flag values, you can simply perform a blind cast (effectively telling the
runtime "Disregard that the incoming value was actually an Int/Int32/UInt, etc, just pretend
I sent you a TEnum and return it as one").

Casts from TEnum to numeric values were already being done this way (in the opposite), but casts 
back were forced to use ToObject in the C++/CLI implementation.  To get rid of this, I created
the MSIL project.  It simply takes the expensive calls in MsilConvert that use ToObject and
rewrites them as blind casts.  You're welcome to profile the speed difference. Simply build
without the post-build step in Release mode and you'll get the "pure" version.  Both are compatible,
the former is a bit slower.  Since enums are a fundimental feature of .Net and I have some
extremely performance sensitive code that makes liberal use of them, I wanted to eliminate any
of *my own* excuses to not use this library since it increases readability of the resulting code
quite dramatically.


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

I've been doing C# since .Net version 1.0 and MSIL almost as long (don't hand me a
pseudo-assembly language and tell me not to look, it'll never happen). But his is my first 
*real* project in C++/CLI and the code will likely (hopefully not) make that point obvious.  
It's not nearly as DRY as I would like, mainly due to the need to use .Net Generics which 
preclude me from using C++ templates in areas I that they would really be useful.

You'll notice, in the places I have used C++ templates, that many of the parameters are
void* types.  Those are the generic TEnum, pinned for safety, passed in to the template
to DRY up the code.

There are three real DRY problems: AddFlag used by Parse, ClobberTo's Non-template (MSIL
or not) implementations and the switch statements used in several places.  The first two 
I had converted to templates and then converted back after it adversely affected 
performance.  I will probably create a text template to generate these methods to meet 
the goals of DRY code in spirit if not perfectly.

The case statements I will refactor when I have time.  It'll likely be pulled into one or
two methods that take a function pointer to perform the operation.  

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