using BenchmarkDotNet;
using BenchmarkDotNet.Tasks;
using Diagonactic;
using DiagonacticTests;

namespace Console.Profile.Performance
{
    [BenchmarkTask(1, BenchmarkMode.Throughput, BenchmarkPlatform.X64, BenchmarkJitVersion.RyuJit, BenchmarkFramework.V452, 5, 5)]
    public class AddFlagComp
    {
        private static readonly FlagsLongEnum TwoFlags = Enums.Parse<FlagsLongEnum>("One");

        [Benchmark("One flag via AddFlag")]
        public void AddFlag() => TwoFlags.AddFlag(FlagsLongEnum.Eight);

        [Benchmark("Two flags via AddFlags")]
        public void AddFlags() => TwoFlags.AddFlags(FlagsLongEnum.Eight, FlagsLongEnum.Five);

        [Benchmark("One flag via Binary Math")]
        public FlagsLongEnum AddFlagNative() => TwoFlags | FlagsLongEnum.Eight;

        [Benchmark("Two flag via Binary Math")]
        public FlagsLongEnum AddFlagsNative() => TwoFlags | FlagsLongEnum.Eight | FlagsLongEnum.Five;
    }
}