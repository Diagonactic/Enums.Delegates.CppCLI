using BenchmarkDotNet;
using BenchmarkDotNet.Tasks;
using Diagonactic;
using DiagonacticTests;

namespace Console.Profile.Performance
{
    [BenchmarkTask(1, BenchmarkMode.Throughput, BenchmarkPlatform.X64, BenchmarkJitVersion.RyuJit, BenchmarkFramework.V452, 5, 5)]
    public class IsFlagSetComp
    {
        [Benchmark]
        public bool IsFlagSetFalse() => LongFlags.One.IsFlagSet(LongFlags.Eight);
        [Benchmark]
        public bool IsFlagSetTrue() => LongFlags.One.IsFlagSet(LongFlags.One);
        [Benchmark]
        public bool HasFlag() => LongFlags.One.HasFlag(LongFlags.One);
    }
}