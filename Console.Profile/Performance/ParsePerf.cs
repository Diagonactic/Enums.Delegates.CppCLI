using System;
using BenchmarkDotNet;
using BenchmarkDotNet.Tasks;
using Diagonactic;
using DiagonacticTests;

namespace Console.Profile.Performance
{
    [BenchmarkTask(1, BenchmarkMode.Throughput, BenchmarkPlatform.X64, BenchmarkJitVersion.RyuJit, BenchmarkFramework.V452, 5, 5)]
    public class ParsePerf
    {
        [Benchmark]
        public void ParseOneValue() => Enums.Parse<LongFlags>("One");

        [Benchmark]
        public void ParseTwoValues() => Enums.Parse<LongFlags>("One, Two");
    }

    [BenchmarkTask(1, BenchmarkMode.Throughput, BenchmarkPlatform.X64, BenchmarkJitVersion.RyuJit, BenchmarkFramework.V452, 5, 5)]
    public class ParseComp
    {
        [Benchmark]
        public void ParseOneValue() => Enums.Parse<LongFlags>("One");

        [Benchmark]
        public void ParseTwoValues() => Enums.Parse<LongFlags>("One, Two");

        [Benchmark]
        public void ParseOneValueNative() => System.Enum.Parse(typeof (LongFlags), "One");

        [Benchmark]
        public void ParseTwoValuesNative() => System.Enum.Parse(typeof(LongFlags), "One, Two");
    }
}