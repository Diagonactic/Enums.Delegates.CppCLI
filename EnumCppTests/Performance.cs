using System;
using System.Runtime.CompilerServices;
using EnumCppTests.Attributes;
using Diagonactic;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace DiagonacticTests
{
    [TestClass]
    public class Performance
    {
        [TestMethod, PerformanceTest, MethodImpl(MethodImplOptions.NoOptimization)]
        public void FlagSmallEnumParsePerformance()
        {
            LongFlags one, two, three;
            for (var i = 0; i < ParseRuns; i++)
            {
                one = Enums.Parse<LongFlags>("One, Two");
                two = Enums.Parse<LongFlags>("Seven, Four");
                three = Enums.Parse<LongFlags>("Nine, Ten");
            }
        }

        [TestMethod, PerformanceTest, MethodImpl(MethodImplOptions.NoOptimization)]
        public void FlagSmallEnumManyValuesParsePerformance()
        {
            LongFlags one, two, three;
            for (var i = 0; i < ParseRuns; i++)
            {
                one = Enums.Parse<LongFlags>("One, Two, Three, Four, Five");
                two = Enums.Parse<LongFlags>("Onea, Twoa, Threea, Foura");
                three = Enums.Parse<LongFlags>("One, Two, Three, Four, Five, Six, Seven, Eight, Nine");
            }
        }

        [TestMethod, BaselineTest, MethodImpl(MethodImplOptions.NoOptimization)]
        public void FlagSmallEnumManyValuesParseNativePerformance()
        {
            LongFlags one, two, three;
            for (var i = 0; i < ParseRuns; i++)
            {
                one = (LongFlags)Enum.Parse(typeof(LongFlags), "One, Two, Three, Four, Five");
                two = (LongFlags)Enum.Parse(typeof(LongFlags), "Onea, Twoa, Threea, Foura");
                three = (LongFlags)Enum.Parse(typeof(LongFlags), "One, Two, Three, Four, Five, Six, Seven, Eight, Nine");
            }
        }


        [TestMethod, PerformanceTest, MethodImpl(MethodImplOptions.NoOptimization)]
        public void FlagSmallEnumSpacelessParsePerformance()
        {
            LongFlags one, two, three;
            for (var i = 0; i < ParseRuns; i++)
            {
                one = Enums.Parse<LongFlags>("One,Two");
                two = Enums.Parse<LongFlags>("Seven,Four");
                three = Enums.Parse<LongFlags>("Nine,Ten");
            }
        }

        [TestMethod, PerformanceTest, MethodImpl(MethodImplOptions.NoOptimization)]
        public void FlagSmallEnumAsStringPerformance()
        {
            string one, two, three;
            for (var i = 0; i < Runs; i++)
            {
                one = (LongFlags.One | LongFlags.Eight).AsString();
                two = (LongFlags.Seven | LongFlags.Ten).AsString();
                three = (LongFlags.Zero | LongFlags.Two).AsString();
            }
        }

        [TestMethod, BaselineTest, MethodImpl(MethodImplOptions.NoOptimization)]
        public void FlagSmallEnumParseNativePerformance()
        {
            LongFlags one, two, three;
            for (var i = 0; i < ParseRuns; i++)
            {
                one = (LongFlags)Enum.Parse(typeof(LongFlags), "One, Two");
                two = (LongFlags)Enum.Parse(typeof(LongFlags), "Seven, Four");
                three = (LongFlags)Enum.Parse(typeof(LongFlags), "Nine , Ten");
            }
        }

        [TestMethod, PerformanceTest, MethodImpl(MethodImplOptions.NoOptimization)]
        public void FlagSmallEnumSingleEnumValueAsStringPerformance()
        {
            string one, two, three;
            for (var i = 0; i < Runs; i++)
            {
                one = (LongFlags.One).AsString();
                two = (LongFlags.Seven).AsString();
                three = (LongFlags.Zero).AsString();
            }
        }

        [TestMethod, BaselineTest, MethodImpl(MethodImplOptions.NoOptimization)]
        public void FlagSmallEnumSingleEnumValueAsStringNativePerformance()
        {
            string one, two, three;
            for (var i = 0; i < Runs; i++)
            {
                one = (LongFlags.One).AsString();
                two = (LongFlags.Seven).AsString();
                three = (LongFlags.Zero).AsString();
            }
        }

        [TestMethod, BaselineTest, MethodImpl(MethodImplOptions.NoOptimization)]
        public void FlagSmallEnumAsStringNativePerformance()
        {
            string one, two, three;
            for (var i = 0; i < Runs; i++)
            {
                one = (LongFlags.One | LongFlags.Eight).ToString();
                two = (LongFlags.Seven | LongFlags.Ten).ToString();
                three = (LongFlags.Zero | LongFlags.Two).ToString();
            }
        }

        [TestMethod, PerformanceTest, MethodImpl(MethodImplOptions.NoOptimization)]
        public void SmallEnumAsStringPerformance()
        {
            string one, seven, five;
            for (var i = 0; i < Runs; i++)
            {
                one = SmallNonFlags.One.AsString();
                seven = SmallNonFlags.Seven.AsString();
                five = SmallNonFlags.Five.AsString();
            }
        }

        [TestMethod, BaselineTest, MethodImpl(MethodImplOptions.NoOptimization)]
        public void SmallEnumAsStringNativePerformance()
        {
            string one, seven, five;
            for (var i = 0; i < Runs; i++)
            {
                one = SmallNonFlags.One.ToString();
                seven = SmallNonFlags.Seven.ToString();
                five = SmallNonFlags.Five.AsString();
            }
        }

        private const int Runs = 1000000;
        private const int ParseRuns = 300000;
    }
}