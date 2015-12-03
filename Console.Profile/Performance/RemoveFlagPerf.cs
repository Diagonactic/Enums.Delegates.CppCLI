using BenchmarkDotNet;
using BenchmarkDotNet.Tasks;
using Diagonactic;
using DiagonacticTests;

namespace Console.Profile.Performance
{
    [BenchmarkTask(1, BenchmarkMode.Throughput, BenchmarkPlatform.X64, BenchmarkJitVersion.RyuJit, BenchmarkFramework.V452, 5, 5)]
    public class RemoveFlagPerf
    {
        const FlagsLongEnum TwoFlags = FlagsLongEnum.One | FlagsLongEnum.Two;

        [Benchmark]
        public void RemoveFlag() => TwoFlags.RemoveFlag(FlagsLongEnum.One);

        [Benchmark]
        public void RemoveFlags() => TwoFlags.RemoveFlags(FlagsLongEnum.One, FlagsLongEnum.Two);
    }
}