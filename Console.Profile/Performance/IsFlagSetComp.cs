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
        public bool IsFlagSetFalse() => FlagsLongEnum.One.IsFlagSet(FlagsLongEnum.Eight);
        [Benchmark]
        public bool IsFlagSetTrue() => FlagsLongEnum.One.IsFlagSet(FlagsLongEnum.One);
        [Benchmark]
        public bool HasFlag() => FlagsLongEnum.One.HasFlag(FlagsLongEnum.One);
    }
}