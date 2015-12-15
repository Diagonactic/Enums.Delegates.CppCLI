using System.Linq;
using System.Reflection;
using BenchmarkDotNet;
using Console.Profile.Performance;

namespace Console.Profile
{
    class Program
    {
        static void Main(string[] args)
        {
            if (args.Length > 0 && args[0] == "ProfilerAttached")
            {
                var parsePerf = new ParsePerf();
                for (int i = 0; i < 100000; i++)
                {
                    parsePerf.ParseOneValue();
                    parsePerf.ParseTwoValues();
                }
                return;
            }
            var benchmarks = Assembly.GetExecutingAssembly().GetTypes()
                .Where(t => t.GetMethods(BindingFlags.Instance | BindingFlags.Public)
                             .Any(m => m.GetCustomAttributes(typeof(BenchmarkAttribute), false).Any()))
                .OrderBy(t => t.Namespace)
                .ThenBy(t => t.Name)
                .ToArray();
            var compSwitch = new BenchmarkCompetitionSwitch(benchmarks);
            compSwitch.Run(args);
        }
    }
}
