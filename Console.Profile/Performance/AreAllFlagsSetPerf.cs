using BenchmarkDotNet;
using BenchmarkDotNet.Tasks;
using Diagonactic;
using DiagonacticTests;

namespace Console.Profile.Performance
{
    [BenchmarkTask(1, BenchmarkMode.Throughput, BenchmarkPlatform.X64, BenchmarkJitVersion.RyuJit, BenchmarkFramework.V452, 5, 5)]
    public class AreAllFlagsSetPerf
    {
        const FlagsLongEnum Compare = FlagsLongEnum.Eight | FlagsLongEnum.Five;

        [Benchmark]
        public void AreAllFlagsSetTrue() => Compare.AreAllFlagsSet(FlagsLongEnum.Five, FlagsLongEnum.Eight);

        [Benchmark]
        public void AreAllFlagsSetFalse() => Compare.AreAllFlagsSet(FlagsLongEnum.Five, FlagsLongEnum.Four);
    }
}