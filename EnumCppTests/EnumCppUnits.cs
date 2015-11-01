using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;
using EnumCppTests.Attributes;
using Diagonactic;
using FluentAssertions;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using static Diagonactic.Enums.Flags;

namespace DiagonacticTests
{
    
    [Flags]
    public enum FlagsLongEnum : long
    {
        Oned   = F32,
        Twod   = F33,
        Threed = F34,
        Fourd  = F35,
        Onec   = F36,
        Twoc   = F37,
        Threec = F38,
        Fourc  = F39,
        Oneb   = F40,
        Twob   = F41,
        Threeb = F42,
        Fourb  = F43,
        Onea   = F44,
        Twoa   = F45,
        Threea = F46,
        Foura  = F47,
        Zero   = F48,
        One  =  F49,
        Two  =  F50,
        Three = F51,
        Four  = F52,
        Five  = F53,
        Six   = F54,
        Seven = F55,
        Eight = F56,
        Nine  = F57,
        Ten   = F58
    }

    [Flags]
    public enum FlagsULongEnum : ulong
    {
        Oned = F8,
        Twod = F40,
        Threed = F41,
        Fourd = F42,
        Onec = F43,
        Twoc = F44,
        Threec = F45,
        Fourc = F46,
        Oneb = F47,
        Twob = F48,
        Threeb = F49,
        Fourb = F50,
        Onea = F51,
        Twoa = F52,
        Threea = F53,
        Foura = F54,
        Zero = F55,
        One = F56,
        Two = F57,
        Three = F58,
        Four = F59,
        Five = F60,
        Six = F61,
        Seven = F62,
        Eight = F63
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
        Five = (sbyte)Enums.Flags.F1,
        Six = (sbyte)Enums.Flags.F2,
        Seven = (sbyte)Enums.Flags.F3
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
            var asArray = Enums.GetNamesArray<FlagsSByteEnum>();
            asArray.Length.ShouldBeEquivalentTo(3);
            asArray.First().ShouldBeEquivalentTo("Five");
            asArray.Last().ShouldBeEquivalentTo("Seven");
            asArray.Any(x => x == "Six").Should().BeTrue();
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
            var asArray = Enums.GetValuesArray<FlagsSByteEnum>();
            asArray.Length.ShouldBeEquivalentTo(3);
            asArray.First().ShouldBeEquivalentTo(FlagsSByteEnum.Five);
            asArray.Last().ShouldBeEquivalentTo(FlagsSByteEnum.Seven);
            names.Any(x => x == FlagsSByteEnum.Six).Should().BeTrue();
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