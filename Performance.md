```ini
BenchmarkDotNet=v0.7.8.0
OS=Microsoft Windows NT 6.2.9200.0
Processor=Intel(R) Core(TM) i7-4710HQ CPU @ 2.50GHz, ProcessorCount=8
HostCLR=MS.NET 4.0.30319.42000, Arch=32-bit
Type=AddFlagPerf  Mode=Throughput  Platform=X64  Jit=RyuJit  .NET=V452
```

After Optimization
==================

   Method             |   AvrTime   |    StdDev |           op/s |          
--------------------- |------------ |---------- |--------------- |          
 AddFlag Macros       | 4.0943 ns   | 0.0057 ns | 244,243,822.93 |          
 AddFlags Macros      | 9.8576 ns   | 0.0318 ns | 101,444,869.44 |          
 IsFlagSetFalse       | 4.1315 ns   | 0.0073 ns | 242,043,883.49 |
 IsFlagSetTrue        | 4.4992 ns   | 0.0164 ns | 222,262,764.27 |
 EqualsAnyFalse       | 8.7521 ns   | 0.0150 ns | 114,257,675.77 |
 EqualsAnyTrue        | 7.3554 ns   | 0.0271 ns | 135,954,063.73 |
 RemoveFlag           | 4.4423 ns   | 0.0186 ns | 225,106,491.39 |       
 RemoveFlags          | 10.5982 ns  | 0.0975 ns |  94,355,337.44 |
 AreAllFlagsSetFalse  | 8.0664 ns   | 0.0450 ns | 123,971,023.97 |
 AreAllFlagsSetTrue   | 9.5706 ns   | 0.0292 ns | 104,486,763.65 |
 AreAnyFlagsSetFalse  | 8.3757 ns   | 0.0085 ns | 119,393,244.10 |
 AreAnyFlagsSetTrue   | 7.3773 ns   | 0.0137 ns | 135,550,237.90 |
 ParseOneValue        | 105.3243 ns | 0.1368 ns | 9,494,484.03   |
 ParseTwoValues       | 277.1396 ns | 0.4245 ns | 3,608,290.22   |
 OneFlagAsString      |  15.6660 ns | 0.0435 ns | 63,832,603.64  |
 TwoFlagsAsString     | 257.0831 ns | 2.2237 ns |  3,889,792.23  |

Before Optimization
===================

   Method             |   AvrTime     |    StdDev |           op/s |          
--------------------- |-------------- |---------- |--------------- |          
 AddFlags no Macros   | 12.9396 ns    | 0.0518 ns |  77,282,048.64 |
 EqualsAnyFalse       | 11.8377 ns    | 0.0986 ns | 84,475,963.73  |
 EqualsAnyTrue        | 10.8384 ns    | 0.0257 ns | 92,264,830.62  |
 RemoveFlags          | 12.7292 ns    | 0.0500 ns |  78,559,553.50 |
 AreAnyFlagsSetFalse  | 10.0771 ns    | 0.0393 ns |  99,235,114.91 |     
 AreAnyFlagsSetTrue   |  9.9164 ns    | 0.0476 ns | 100,843,283.64 |                                                                     

Native Methods
==============

   Method             |   AvrTime     |    StdDev |           op/s |          
--------------------- |-------------- |---------- |--------------- |          
 Enum.HasFlag         | 22.0760 ns    | 0.0296 ns |  45,298,142.13 |
 OneFlagToString      | 1,223.5774 ns | 3.1401 ns |    817,275.63  |
 TwoFlagsToString     | 1,290.8826 ns | 2.7503 ns |    774,663.79  |
 ParseOneValueNative  | 332.4816 ns   | 0.6586 ns | 3,007,685.08   |
 ParseTwoValuesNative | 520.0306 ns   | 1.5211 ns | 1,922,963.66   |

