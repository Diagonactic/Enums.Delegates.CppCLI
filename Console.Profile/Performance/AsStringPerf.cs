using BenchmarkDotNet;
using BenchmarkDotNet.Tasks;
using Diagonactic;
using DiagonacticTests;

namespace Console.Profile.Performance
{
    [BenchmarkTask(1, BenchmarkMode.Throughput, BenchmarkPlatform.X64, BenchmarkJitVersion.RyuJit,
        BenchmarkFramework.V452, 5, 5)]
    public class AsStringPerf
    {
        const FlagsLongEnum TwoFlags = FlagsLongEnum.One | FlagsLongEnum.Two;
        const FlagsLongEnum OneFlag = FlagsLongEnum.One;

        [Benchmark("One long Flag AsString")]
        public void OneFlagAsString() => OneFlag.AsString();

        [Benchmark("Two long Flags AsString")]
        public void TwoFlagsAsString() => TwoFlags.AsString();
    }

    [BenchmarkTask(1, BenchmarkMode.Throughput, BenchmarkPlatform.X64, BenchmarkJitVersion.RyuJit,
        BenchmarkFramework.V452, 5, 5)]
    public class AsStringComp
    {
        const FlagsLongEnum TwoFlags = FlagsLongEnum.One | FlagsLongEnum.Two;
        const FlagsLongEnum OneFlag = FlagsLongEnum.One;

        [Benchmark("One long Flag AsString")]
        public void OneFlagAsString() => OneFlag.AsString();

        [Benchmark("Two long Flags AsString")]
        public void TwoFlagsAsString() => TwoFlags.AsString();

        [Benchmark("One long Flag ToString (Native)")]
        public void OneFlagToString() => OneFlag.ToString();

        [Benchmark("Two long Flags ToString (Native)")]
        public void TwoFlagsToString() => TwoFlags.ToString();
    }
}