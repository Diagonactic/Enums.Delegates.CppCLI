using BenchmarkDotNet;
using BenchmarkDotNet.Tasks;
using Diagonactic;
using DiagonacticTests;

namespace Console.Profile.Performance
{
    [BenchmarkTask(1, BenchmarkMode.Throughput, BenchmarkPlatform.X64, BenchmarkJitVersion.RyuJit, BenchmarkFramework.V452, 5, 5)]
    public class EqualsAnyPerf
    {
        const LongFlags Compare = LongFlags.Eight;

        [Benchmark]
        public void EqualsAnyTrue() => Compare.EqualsAny(LongFlags.Five, LongFlags.Eight);

        [Benchmark]
        public void EqualsAnyFalse() => Compare.EqualsAny(LongFlags.Five, LongFlags.Four);
    }
}