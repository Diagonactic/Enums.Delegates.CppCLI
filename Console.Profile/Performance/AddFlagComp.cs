using BenchmarkDotNet;
using BenchmarkDotNet.Tasks;
using Diagonactic;
using DiagonacticTests;

namespace Console.Profile.Performance
{
    [BenchmarkTask(1, BenchmarkMode.Throughput, BenchmarkPlatform.X64, BenchmarkJitVersion.RyuJit, BenchmarkFramework.V452, 5, 5)]
    public class AddFlagComp
    {
        private static readonly LongFlags s_TwoLongFlags = Enums.Parse<LongFlags>("One");

        [Benchmark("One flag via AddFlag")]
        public void AddFlag() => s_TwoLongFlags.AddFlag(LongFlags.Eight);

        [Benchmark("Two flags via AddFlags")]
        public void AddFlags() => s_TwoLongFlags.AddFlags(LongFlags.Eight, LongFlags.Five);

        [Benchmark("One flag via Binary Math")]
        public LongFlags AddFlagNative() => s_TwoLongFlags | LongFlags.Eight;

        [Benchmark("Two flag via Binary Math")]
        public LongFlags AddFlagsNative() => s_TwoLongFlags | LongFlags.Eight | LongFlags.Five;
    }
}