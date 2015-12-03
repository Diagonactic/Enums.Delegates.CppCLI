using BenchmarkDotNet;
using BenchmarkDotNet.Tasks;
using Diagonactic;
using DiagonacticTests;

namespace Console.Profile.Performance
{
    [BenchmarkTask(1, BenchmarkMode.Throughput, BenchmarkPlatform.X64, BenchmarkJitVersion.RyuJit, BenchmarkFramework.V452, 5, 5)]
    public class EqualsAnyPerf
    {
        const FlagsLongEnum Compare = FlagsLongEnum.Eight;

        [Benchmark]
        public void EqualsAnyTrue() => Compare.EqualsAny(FlagsLongEnum.Five, FlagsLongEnum.Eight);

        [Benchmark]
        public void EqualsAnyFalse() => Compare.EqualsAny(FlagsLongEnum.Five, FlagsLongEnum.Four);
    }
}