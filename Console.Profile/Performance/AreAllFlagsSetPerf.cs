using BenchmarkDotNet;
using BenchmarkDotNet.Tasks;
using Diagonactic;
using DiagonacticTests;

namespace Console.Profile.Performance
{
    [BenchmarkTask(1, BenchmarkMode.Throughput, BenchmarkPlatform.X64, BenchmarkJitVersion.RyuJit, BenchmarkFramework.V452, 5, 5)]
    public class AreAllFlagsSetPerf
    {
        const LongFlags Compare = LongFlags.Eight | LongFlags.Five;

        [Benchmark]
        public void AreAllFlagsSetTrue() => Compare.AreAllFlagsSet(LongFlags.Five, LongFlags.Eight);

        [Benchmark]
        public void AreAllFlagsSetFalse() => Compare.AreAllFlagsSet(LongFlags.Five, LongFlags.Four);
    }
}