using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;
using DiagonacticTests;
using Diagonactic;

namespace ConsoleProfile.Profile
{
    class Program
    {
        [MethodImpl(MethodImplOptions.NoOptimization)]
        static void RunAsString(int runs)
        {
            string one = null, two = null, three = null;
            for (var i = 0; i < runs; i++)
            {
                one = (FlagsLongEnum.One | FlagsLongEnum.Eight).AsString();
                two = (FlagsLongEnum.Seven | FlagsLongEnum.Ten).AsString();
                three = (FlagsLongEnum.Eight | FlagsLongEnum.Two).AsString();
            }

            if (one != "One, Eight" || two != "Seven, Ten" || three != "Two, Eight")
                throw new Exception($"Result '{one}', '{two}', or '{three}' was not correct");
        }

        static void Parse(int runs)
        {
            FlagsLongEnum pone = default(FlagsLongEnum), ptwo = default(FlagsLongEnum), pthree = default(FlagsLongEnum);
            for (var i = 0; i < runs; i++)
            {
                pone = Enums.Parse<FlagsLongEnum>("One");
                ptwo = Enums.Parse<FlagsLongEnum>("Seven, Four");
                pthree = Enums.Parse<FlagsLongEnum>("Nine, Ten");
            }
            if (pone != FlagsLongEnum.One || (ptwo != (FlagsLongEnum.Seven|FlagsLongEnum.Four)) || pthree != (FlagsLongEnum.Nine|FlagsLongEnum.Ten))
                throw new Exception($"Result '{pone}', '{ptwo}', '{pthree}' was not correct");
        }

        static void ParseCaseInsensitive(int runs)
        {
            FlagsLongEnum pone = default(FlagsLongEnum), ptwo = default(FlagsLongEnum), pthree = default(FlagsLongEnum);
            for (var i = 0; i < runs; i++)
            {
                pone = Enums.Parse<FlagsLongEnum>("one", true);
                ptwo = Enums.Parse<FlagsLongEnum>("sEven, four", true);
                pthree = Enums.Parse<FlagsLongEnum>("nine, teN", true);
            }
            if (pone != FlagsLongEnum.One || (ptwo != (FlagsLongEnum.Seven | FlagsLongEnum.Four)) || pthree != (FlagsLongEnum.Nine | FlagsLongEnum.Ten))
                throw new Exception($"Result '{pone}', '{ptwo}', '{pthree}' was not correct");
        }

        static void AddFlags(int runs)
        {
            FlagsLongEnum one = FlagsLongEnum.One, two = FlagsLongEnum.Eight, three = FlagsLongEnum.Five, result = default(FlagsLongEnum);
            for (var i = 0; i < runs; i++)
            {
                result = one.AddFlags(two, three);
            }
        }


        delegate void TestDelegate();

        static event TestDelegate TestEvent;
        const int Runs = 500000;
        const int ParseRuns = 200000;
        static void Main(string[] args)
        {
            int runs = Runs;
            int parseRuns = ParseRuns;
            if (args.Length > 0)
                runs = int.Parse(args[0]);
            if (args.Length > 1)
                parseRuns = int.Parse(args[1]);

            TestDelegate a = () =>
            {
                int i = 0;
            };

            Console.WriteLine("Interfaces implemented by delegates");

            var interfaces = a.GetType().GetInterfaces();
            foreach (var iface in interfaces)
            {
                Console.WriteLine(iface.Name);
            }
            Program.TestEvent += a;

            Console.WriteLine("Interfaces implemented by events");

            Console.WriteLine(TestEvent.GetType().Name);
            foreach (var iface in Program.TestEvent.GetType().GetInterfaces())
            {
                Console.WriteLine(iface.Name);
            }
            RunAsString(runs);
            AddFlags(runs);
            ParseCaseInsensitive(parseRuns);
            Program.Parse(parseRuns);
            Console.ReadKey();
        }
    }
}
