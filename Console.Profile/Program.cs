using System.Linq;
using System.Reflection;
using BenchmarkDotNet;

namespace Console.Profile
{
    class Program
    {
        static void Main(string[] args)
        {
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
