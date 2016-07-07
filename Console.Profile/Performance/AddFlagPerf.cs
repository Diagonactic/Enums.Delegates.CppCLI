using BenchmarkDotNet;
using BenchmarkDotNet.Tasks;
using Diagonactic;
using DiagonacticTests;

namespace Console.Profile.Performance
{
    [BenchmarkTask(1, BenchmarkMode.Throughput, BenchmarkPlatform.X64, BenchmarkJitVersion.RyuJit, BenchmarkFramework.V452, 5, 5)]
    public class AddFlagPerf
    {
        const LongFlags TwoFlags = LongFlags.One | LongFlags.Two;

        [Benchmark]
        public void AddFlag() => TwoFlags.AddFlag(LongFlags.Four);

        [Benchmark]
        public void AddFlags() => TwoFlags.AddFlags(LongFlags.Eight, LongFlags.Five);
    }
}