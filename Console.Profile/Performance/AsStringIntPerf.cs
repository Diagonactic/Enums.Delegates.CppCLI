using BenchmarkDotNet;
using BenchmarkDotNet.Tasks;
using Diagonactic;

namespace Console.Profile.Performance
{
    public enum FlagsIntEnum : int
    {
        One = Enums.Flag.F1,
        Two = Enums.Flag.F2
    }

    [BenchmarkTask(1, BenchmarkMode.Throughput, BenchmarkPlatform.X64, BenchmarkJitVersion.RyuJit,
        BenchmarkFramework.V452, 5, 5)]
    public class AsStringIntPerf
    {
        const FlagsIntEnum TwoFlags = FlagsIntEnum.One | FlagsIntEnum.Two;
        const FlagsIntEnum OneFlag = FlagsIntEnum.One;
        [Benchmark("One int Flag AsString")]
        public void OneFlagAsString() => OneFlag.AsString();

        [Benchmark("Two int Flags AsString")]
        public void TwoFlagsAsString() => TwoFlags.AsString();
    }
}