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
            FlagsLongEnum one, two, three;
            for (var i = 0; i < ParseRuns; i++)
            {
                one = Enums.Parse<FlagsLongEnum>("One, Two");
                two = Enums.Parse<FlagsLongEnum>("Seven, Four");
                three = Enums.Parse<FlagsLongEnum>("Nine, Ten");
            }
        }

        [TestMethod, PerformanceTest, MethodImpl(MethodImplOptions.NoOptimization)]
        public void FlagSmallEnumManyValuesParsePerformance()
        {
            FlagsLongEnum one, two, three;
            for (var i = 0; i < ParseRuns; i++)
            {
                one = Enums.Parse<FlagsLongEnum>("One, Two, Three, Four, Five");
                two = Enums.Parse<FlagsLongEnum>("Onea, Twoa, Threea, Foura");
                three = Enums.Parse<FlagsLongEnum>("One, Two, Three, Four, Five, Six, Seven, Eight, Nine");
            }
        }

        [TestMethod, BaselineTest, MethodImpl(MethodImplOptions.NoOptimization)]
        public void FlagSmallEnumManyValuesParseNativePerformance()
        {
            FlagsLongEnum one, two, three;
            for (var i = 0; i < ParseRuns; i++)
            {
                one = (FlagsLongEnum)Enum.Parse(typeof(FlagsLongEnum), "One, Two, Three, Four, Five");
                two = (FlagsLongEnum)Enum.Parse(typeof(FlagsLongEnum), "Onea, Twoa, Threea, Foura");
                three = (FlagsLongEnum)Enum.Parse(typeof(FlagsLongEnum), "One, Two, Three, Four, Five, Six, Seven, Eight, Nine");
            }
        }


        [TestMethod, PerformanceTest, MethodImpl(MethodImplOptions.NoOptimization)]
        public void FlagSmallEnumSpacelessParsePerformance()
        {
            FlagsLongEnum one, two, three;
            for (var i = 0; i < ParseRuns; i++)
            {
                one = Enums.Parse<FlagsLongEnum>("One,Two");
                two = Enums.Parse<FlagsLongEnum>("Seven,Four");
                three = Enums.Parse<FlagsLongEnum>("Nine,Ten");
            }
        }

        [TestMethod, PerformanceTest, MethodImpl(MethodImplOptions.NoOptimization)]
        public void FlagSmallEnumAsStringPerformance()
        {
            string one, two, three;
            for (var i = 0; i < Runs; i++)
            {
                one = (FlagsLongEnum.One | FlagsLongEnum.Eight).AsString();
                two = (FlagsLongEnum.Seven | FlagsLongEnum.Ten).AsString();
                three = (FlagsLongEnum.Zero | FlagsLongEnum.Two).AsString();
            }
        }

        [TestMethod, BaselineTest, MethodImpl(MethodImplOptions.NoOptimization)]
        public void FlagSmallEnumParseNativePerformance()
        {
            FlagsLongEnum one, two, three;
            for (var i = 0; i < ParseRuns; i++)
            {
                one = (FlagsLongEnum)Enum.Parse(typeof(FlagsLongEnum), "One, Two");
                two = (FlagsLongEnum)Enum.Parse(typeof(FlagsLongEnum), "Seven, Four");
                three = (FlagsLongEnum)Enum.Parse(typeof(FlagsLongEnum), "Nine , Ten");
            }
        }

        [TestMethod, PerformanceTest, MethodImpl(MethodImplOptions.NoOptimization)]
        public void FlagSmallEnumSingleEnumValueAsStringPerformance()
        {
            string one, two, three;
            for (var i = 0; i < Runs; i++)
            {
                one = (FlagsLongEnum.One).AsString();
                two = (FlagsLongEnum.Seven).AsString();
                three = (FlagsLongEnum.Zero).AsString();
            }
        }

        [TestMethod, BaselineTest, MethodImpl(MethodImplOptions.NoOptimization)]
        public void FlagSmallEnumSingleEnumValueAsStringNativePerformance()
        {
            string one, two, three;
            for (var i = 0; i < Runs; i++)
            {
                one = (FlagsLongEnum.One).AsString();
                two = (FlagsLongEnum.Seven).AsString();
                three = (FlagsLongEnum.Zero).AsString();
            }
        }

        [TestMethod, BaselineTest, MethodImpl(MethodImplOptions.NoOptimization)]
        public void FlagSmallEnumAsStringNativePerformance()
        {
            string one, two, three;
            for (var i = 0; i < Runs; i++)
            {
                one = (FlagsLongEnum.One | FlagsLongEnum.Eight).ToString();
                two = (FlagsLongEnum.Seven | FlagsLongEnum.Ten).ToString();
                three = (FlagsLongEnum.Zero | FlagsLongEnum.Two).ToString();
            }
        }

        [TestMethod, PerformanceTest, MethodImpl(MethodImplOptions.NoOptimization)]
        public void SmallEnumAsStringPerformance()
        {
            string one, seven, five;
            for (var i = 0; i < Runs; i++)
            {
                one = SmallEnum.One.AsString();
                seven = SmallEnum.Seven.AsString();
                five = SmallEnum.Five.AsString();
            }
        }

        [TestMethod, BaselineTest, MethodImpl(MethodImplOptions.NoOptimization)]
        public void SmallEnumAsStringNativePerformance()
        {
            string one, seven, five;
            for (var i = 0; i < Runs; i++)
            {
                one = SmallEnum.One.ToString();
                seven = SmallEnum.Seven.ToString();
                five = SmallEnum.Five.AsString();
            }
        }

        private const int Runs = 1000000;
        private const int ParseRuns = 300000;
    }
}