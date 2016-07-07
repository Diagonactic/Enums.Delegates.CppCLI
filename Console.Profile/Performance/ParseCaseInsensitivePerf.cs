using BenchmarkDotNet;
using BenchmarkDotNet.Tasks;
using Diagonactic;
using DiagonacticTests;

namespace Console.Profile.Performance
{
    [BenchmarkTask(1, BenchmarkMode.Throughput, BenchmarkPlatform.X64, BenchmarkJitVersion.RyuJit, BenchmarkFramework.V452, 5, 5)]
    public class ParseCaseInsensitivePerf {
        [Benchmark]
        public void ParseOneCaseInsensitive() => Enums.Parse<LongFlags>("one", true);

        [Benchmark]
        public void ParseTwoCaseInsensitive() => Enums.Parse<LongFlags>("one, two", true);
        
    }
}