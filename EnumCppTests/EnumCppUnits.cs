using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;
using EnumCppTests.Attributes;
using Diagonactic;
using FluentAssertions;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace DiagonacticTests
{
    
    [Flags]
    public enum FlagsLongEnum : long
    {
        Oned   = 0x10000000,
        Twod   = 0x20000000,
        Threed = 0x40000000,
        Fourd  = 0x80000000,
        Onec   = 0x100000000,
        Twoc   = 0x200000000,
        Threec = 0x400000000,
        Fourc  = 0x800000000,
        Oneb   = 0x1000000000,
        Twob   = 0x2000000000,
        Threeb = 0x4000000000,
        Fourb  = 0x8000000000,
        Onea   = 0x100000000000,
        Twoa   = 0x200000000000,
        Threea = 0x400000000000,
        Foura  = 0x800000000000,
        Zero   = 0x8000000000000,
        One  =  0x10000000000000,
        Two  =  0x20000000000000,
        Three = 0x40000000000000,
        Four  = 0x80000000000000,
        Five  = 0x100000000000000,
        Six   = 0x200000000000000,
        Seven = 0x400000000000000,
        Eight = 0x800000000000000,
        Nine  = 0x1000000000000000,
        Ten   = 0x2000000000000000
    }

    [Flags]
    public enum FlagsULongEnum : ulong
    {
        Oned = 0x100000000,
        Twod = 0x200000000,
        Threed = 0x400000000,
        Fourd = 0x800000000,
        Onec = 0x1000000000,
        Twoc = 0x2000000000,
        Threec = 0x4000000000,
        Fourc = 0x8000000000,
        Oneb = 0x10000000000,
        Twob = 0x20000000000,
        Threeb = 0x40000000000,
        Fourb = 0x80000000000,
        Onea = 0x1000000000000,
        Twoa = 0x2000000000000,
        Threea = 0x4000000000000,
        Foura = 0x8000000000000,
        Zero = 0x80000000000000,
        One = 0x100000000000000,
        Two = 0x200000000000000,
        Three = 0x400000000000000,
        Four = 0x800000000000000,
        Five = 0x1000000000000000,
        Six = 0x2000000000000000,
        Seven = 0x4000000000000000,
        Eight = 0x8000000000000000
    }

    public enum DescriptionEnum
    {
        FooBarBaz,
        [System.ComponentModel.Description("The Number One")]
        One,
        Foo_Bar_Baz,
        Foo_Bar_FORTY_Two,
        LifeUniverseEVERYTHING,
        restaurant_end_of_universe,
        Three,
        Four,
        [System.ComponentModel.Description("The Number Five")]
        Five,
        Six,
        Seven,
        Eight,
        Nine,
        Ten
    }

    public enum SmallEnum
    {
        Zero,
        [System.ComponentModel.Description("The Number One")]
        One,
        Two,
        Three,
        Four,
        [System.ComponentModel.Description("The Number Five")]
        Five,
        Six,
        Seven,
        Eight,
        Nine,
        Ten
    }
    

    [Flags]
    enum FlagsSByteEnum : sbyte
    {
        Five = 0x1,
        Six = 0x2,
        Seven = 0x4
    }
    

    [TestClass]
    public class EnumUnitTests
    {
        [TestMethod, EnumTest]
        public void TestDescription()
        {
            SmallEnum.One.GetDescription().ShouldBeEquivalentTo("The Number One");
            SmallEnum.Five.GetDescription().ShouldBeEquivalentTo("The Number Five");
            SmallEnum result;
            Enums.TryGetFromDescription("The Number One", out result).Should().BeTrue();
            Enums.TryGetFromDescription("Foo", out result).Should().BeFalse();
            result.ShouldBeEquivalentTo(default(SmallEnum));
            DescriptionEnum.FooBarBaz.GetDescription().ShouldBeEquivalentTo("Foo Bar Baz");
            DescriptionEnum.FooBarBaz.GetDescription().ShouldBeEquivalentTo("Foo Bar Baz");
            DescriptionEnum.Foo_Bar_FORTY_Two.GetDescription().ShouldBeEquivalentTo("Foo Bar Forty Two");
            DescriptionEnum.LifeUniverseEVERYTHING.GetDescription().ShouldBeEquivalentTo("Life Universe EVERYTHING");
            DescriptionEnum.restaurant_end_of_universe.GetDescription().ShouldBeEquivalentTo("Restaurant End Of Universe");
        }

        [TestMethod, EnumTest]
        public void TestParse()
        {
            TestParseSmallEnum("Eight");
            TestParseSmallEnum("eight", true);
        }

        [TestMethod, EnumTest]
        public void TestFormat()
        {
            FlagsULongEnum.Eight.Format("G").ShouldBeEquivalentTo("Eight");
        }
        [TestMethod, EnumTest]
        public void TestTryParse()
        {
            TestTryParseSmallEnum("Eight", true);
            TestTryParseSmallEnum("eight", true, true);
            TestTryParseFlagsEnum("Twoc, Four", true);
            TestTryParseFlagsEnum("Eight, four", true, true);
            TestTryParseSmallEnum("E", false);
            TestTryParseSmallEnum("e", false);
            TestTryParseSmallEnum("e", false, true);
            TestTryParseFlagsEnum("E, F", false);
            TestTryParseFlagsEnum("E, f", false);
        }

        
        [TestMethod, EnumTest, ExpectedException(typeof(ArgumentException))]
        public void TestParseFailureFlags()
        {
            TestParseFlagsEnum("eight");
        }

        [TestMethod, EnumTest, ExpectedException(typeof(ArgumentException))]
        public void TestParseFailure()
        {
            TestParseSmallEnum("eight");
        }

        [TestMethod, EnumTest]
        public void TestAsString()
        {
            SmallEnum.Eight.AsString().ShouldBeEquivalentTo(SmallEnum.Eight.ToString());
        }

        [TestMethod, EnumTest]
        public void TestGetNames()
        {
            IReadOnlyCollection<string> names = Enums.GetNames<FlagsSByteEnum>();
            names.Count.ShouldBeEquivalentTo(3);
            names.First().ShouldBeEquivalentTo("Five");
            names.Last().ShouldBeEquivalentTo("Seven");
            names.Any(x => x == "Six").Should().BeTrue();
        }

        [TestMethod, EnumTest]
        public void TestGetValuesAsArray()
        {
            /*
            FlagsSByteEnum[] values = Enums.GetValuesAsArray<FlagsSByteEnum>();
            values.Length.ShouldBeEquivalentTo(3);
            values.First().ShouldBeEquivalentTo(FlagsSByteEnum.Five);
            values.Last().ShouldBeEquivalentTo(FlagsSByteEnum.Seven);
            values.Any(x => x == FlagsSByteEnum.Six).Should().BeTrue();
            */
        }

        [TestMethod, EnumTest]
        public void TestGetValues()
        {
            IReadOnlyCollection<FlagsSByteEnum> names = Enums.GetValues<FlagsSByteEnum>();
            names.Count.ShouldBeEquivalentTo(3);
            names.First().ShouldBeEquivalentTo(FlagsSByteEnum.Five);
            names.Last().ShouldBeEquivalentTo(FlagsSByteEnum.Seven);
            names.Any(x => x == FlagsSByteEnum.Six).Should().BeTrue();
        }

        [TestMethod, EnumTest]
        public void TestGetNamesAsArray()
        {
            var names = Enums.GetNames<FlagsSByteEnum>();
            names.Count.ShouldBeEquivalentTo(3);
            names.First().ShouldBeEquivalentTo("Five");
            names.Last().ShouldBeEquivalentTo("Seven");
            names.Any(x => x == "Six").Should().BeTrue();
        }


        [TestMethod, EnumTest]
        public void TestAddFlag()
        {
            FlagsLongEnum.Eight.AddFlag(FlagsLongEnum.One).ShouldBeEquivalentTo(FlagsLongEnum.Eight | FlagsLongEnum.One);
        }

        [TestMethod, EnumTest]
        public void TestRemoveFlag()
        {
            (FlagsLongEnum.Five | FlagsLongEnum.Two).RemoveFlag(FlagsLongEnum.Five).ShouldBeEquivalentTo(FlagsLongEnum.Two);
        }

        [TestMethod, EnumTest]
        public void TestFlagsAsString()
        {
            FlagsLongEnum flagVal = FlagsLongEnum.Eight | FlagsLongEnum.Five;

            flagVal.AsString().ShouldBeEquivalentTo(flagVal.ToString());
        }

        [TestMethod,EnumTest]
        public void TestParseFlags()
        {
            TestParseFlagsEnum("Eight, Five");
            TestParseFlagsEnum("Foura ,Five");
            TestParseFlagsEnum("Eight , Foura");
        }

        public void TestParseFlagsEnum(string enumVal, bool ignoreCase = false)
        {
            FlagsLongEnum ourResult = !ignoreCase ? Enums.Parse<FlagsLongEnum>(enumVal) : Enums.Parse<FlagsLongEnum>(enumVal, true);

            var theirResult = (FlagsLongEnum)Enum.Parse(typeof(FlagsLongEnum), enumVal);

            ourResult.ShouldBeEquivalentTo(theirResult);
        }

        public void TestParseSmallEnum(string enumVal, bool ignoreCase = false)
        {
            SmallEnum ourResult = !ignoreCase ? Enums.Parse<SmallEnum>(enumVal) : Enums.Parse<SmallEnum>(enumVal, true);
            SmallEnum theirResult = (SmallEnum)Enum.Parse(typeof(SmallEnum), enumVal, ignoreCase);

            ourResult.ShouldBeEquivalentTo(theirResult);
        }

        public void TestTryParseFlagsEnum(string enumVal, bool expectedValue, bool ignoreCase = false)
        {
            FlagsLongEnum ourResult;
            if (!ignoreCase)
                Enums.TryParse(enumVal, out ourResult).ShouldBeEquivalentTo(expectedValue);
            else
                Enums.TryParse(enumVal, true, out ourResult).ShouldBeEquivalentTo(expectedValue);

            FlagsLongEnum theirResult;
            Enum.TryParse(enumVal, ignoreCase, out theirResult);

            if (expectedValue)
                ourResult.ShouldBeEquivalentTo(theirResult);
        }

        public void TestTryParseSmallEnum(string enumVal, bool expectedResult, bool ignoreCase = false)
        {
            SmallEnum ourResult;
            if (!ignoreCase)
                Enums.TryParse(enumVal, out ourResult).ShouldBeEquivalentTo(expectedResult);
            else
                Enums.TryParse(enumVal, true, out ourResult).ShouldBeEquivalentTo(expectedResult);

            SmallEnum theirResult;
            Enum.TryParse(enumVal, ignoreCase, out theirResult);
            
            if (expectedResult)
                ourResult.ShouldBeEquivalentTo(theirResult);
        }
    }
}