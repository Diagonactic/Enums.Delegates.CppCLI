```ini
BenchmarkDotNet=v0.7.8.0
OS=Microsoft Windows NT 6.2.9200.0
Processor=Intel(R) Core(TM) i7-4710HQ CPU @ 2.50GHz, ProcessorCount=8
HostCLR=MS.NET 4.0.30319.42000, Arch=32-bit
Type=AddFlagPerf  Mode=Throughput  Platform=X64  Jit=RyuJit  .NET=V452
```

Method Calls
============

   Method                |   AvrTime   |    StdDev |           op/s |          
------------------------ |------------ |---------- |--------------- |          
 AddFlag                 | 4.0943 ns   | 0.0057 ns | 244,243,822.93 |          
 AddFlags                | 9.8576 ns   | 0.0318 ns | 101,444,869.44 |
 IsFlagSetFalse          | 4.1315 ns   | 0.0073 ns | 242,043,883.49 |
 IsFlagSetTrue           | 4.4992 ns   | 0.0164 ns | 222,262,764.27 |
 EqualsAnyFalse          | 8.7521 ns   | 0.0150 ns | 114,257,675.77 |
 EqualsAnyTrue           | 7.3554 ns   | 0.0271 ns | 135,954,063.73 |
 RemoveFlag              | 4.4423 ns   | 0.0186 ns | 225,106,491.39 |       
 RemoveFlags             | 10.5982 ns  | 0.0975 ns |  94,355,337.44 |
 AreAllFlagsSetFalse     | 8.0664 ns   | 0.0450 ns | 123,971,023.97 |
 AreAllFlagsSetTrue      | 9.5706 ns   | 0.0292 ns | 104,486,763.65 |
 AreAnyFlagsSetFalse     | 8.3757 ns   | 0.0085 ns | 119,393,244.10 |
 AreAnyFlagsSetTrue      | 7.3773 ns   | 0.0137 ns | 135,550,237.90 |
 ParseOneValue           | 101.7826 ns | 0.2447 ns |   9,824,866.26 |
 ParseTwoValues          | 265.1160 ns | 0.9024 ns |   3,771,933.09 |
 ParseOneCaseInsensitive | 131.3235 ns | 0.3311 ns |   7,614,782.85 |
 ParseTwoCaseInsensitive | 357.9641 ns | 1.8378 ns |   2,793,576.01 | 
 OneFlagAsString         |  15.9344 ns | 0.0240 ns |  62,757,210.13 |
 TwoFlagsAsString        | 222.4333 ns | 0.3344 ns |   4,495,729.76 | 

Native Methods
==============

   Method             |   AvrTime     |    StdDev |           op/s |          
--------------------- |-------------- |---------- |--------------- |          
 Enum.HasFlag         | 22.0760 ns    | 0.0296 ns |  45,298,142.13 |
 OneFlagToString      | 1,223.5774 ns | 3.1401 ns |    817,275.63  |
 TwoFlagsToString     | 1,290.8826 ns | 2.7503 ns |    774,663.79  |
 ParseOneValueNative  | 332.4816 ns   | 0.6586 ns | 3,007,685.08   |
 ParseTwoValuesNative | 520.0306 ns   | 1.5211 ns | 1,922,963.66   |

