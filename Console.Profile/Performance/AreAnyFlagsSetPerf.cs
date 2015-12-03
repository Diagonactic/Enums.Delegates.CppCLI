using BenchmarkDotNet;
using BenchmarkDotNet.Tasks;
using Diagonactic;
using DiagonacticTests;

namespace Console.Profile.Performance
{
    [BenchmarkTask(1, BenchmarkMode.Throughput, BenchmarkPlatform.X64, BenchmarkJitVersion.RyuJit, BenchmarkFramework.V452, 5, 5)]
    public class AreAnyFlagsSetPerf
    {
        const FlagsLongEnum Compare = FlagsLongEnum.Eight | FlagsLongEnum.Five;

        [Benchmark]
        public void AreAnyFlagsSetTrue() => Compare.AreAnyFlagsSet(FlagsLongEnum.Five, FlagsLongEnum.Eight);

        [Benchmark]
        public void AreAnyFlagsSetFalse() => Compare.AreAnyFlagsSet(FlagsLongEnum.Five, FlagsLongEnum.Four);
    }
}