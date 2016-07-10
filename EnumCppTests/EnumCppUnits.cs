using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;
using EnumCppTests.Attributes;
using Diagonactic;
using FluentAssertions;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using static Diagonactic.Enums.Flag;

namespace DiagonacticTests
{
    
    [Flags]
    public enum LongFlags : long
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
    public enum ULongFlags : ulong
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

    public enum DescriptionNonFlags
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

    public enum SmallNonFlags
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
    enum SByteFlags : sbyte
    {
        Five = (sbyte)F1,
        Six = (sbyte)F2,
        Seven = (sbyte)F3
    }
    

    [TestClass]
    public class EnumUnitTests
    {
        [TestMethod, EnumTest]
        public void TestCanExecuteExactMatch()
        {
            var fm = new EnumDelegateMap<LongFlags, int>();
            fm.AssignToExactValue(LongFlags.Eight, (f) =>
                                  {
                                      f.ShouldBeEquivalentTo(LongFlags.Eight);
                                      return 9;
                                  });
            fm.ExecuteExactMatch(LongFlags.Eight).ShouldBeEquivalentTo(9);
            fm.AssignToExactValue(LongFlags.Eight | LongFlags.Five, (f) => 10);
            fm.ExecuteExactMatch(LongFlags.Eight | LongFlags.Five).ShouldBeEquivalentTo(10);
            fm.ExecuteExactMatch(LongFlags.Four).ShouldBeEquivalentTo(default(LongFlags));
            fm = new EnumDelegateMap<LongFlags, int>();
            fm.AssignToEachFlag(LongFlags.Eight | LongFlags.Five, (f) => 42);
            fm.ExecuteExactMatch(LongFlags.Eight).ShouldBeEquivalentTo(42);
            fm.ExecuteExactMatch(LongFlags.Five).ShouldBeEquivalentTo(42);
            fm.ExecuteExactMatch(LongFlags.Eight | LongFlags.Five).ShouldBeEquivalentTo(default(LongFlags));
            fm = new EnumDelegateMap<LongFlags, int>();
            fm.AssignToEachFlag(LongFlags.Eight | LongFlags.Five, (f) =>
                                {
                                    return 42;
                                });
            fm.ExecuteExactMatch(LongFlags.Eight | LongFlags.Five).ShouldBeEquivalentTo(default(LongFlags));
        }

        [TestMethod, EnumTest]
        public void TestCanExecuteExactMatchWithDefault()
        {
            var fm = new EnumDelegateMap<LongFlags, int>((f) => 11);
            fm.ExecuteExactMatch(LongFlags.Nine).ShouldBeEquivalentTo(11);
            fm.AssignToExactValue(LongFlags.Nine, (f) => 10);
            fm.ExecuteExactMatch(LongFlags.Nine).ShouldBeEquivalentTo(10);
            fm.ExecuteExactMatch(LongFlags.Five).ShouldBeEquivalentTo(11);
            fm.ExecuteExactMatch(LongFlags.Nine, (f) => 12).ShouldBeEquivalentTo(10);
            fm.ExecuteExactMatch(LongFlags.One, (f) => 13).ShouldBeEquivalentTo(13);
        }
        
        [TestMethod, EnumTest]
        public void TestCanExecuteFlags()
        {
            var fm = new EnumDelegateMap<LongFlags, int>();

            fm.AssignToEachFlag(LongFlags.Eight | LongFlags.Five, (f) => 42);

            var dic = fm.ExecuteFlagsMatches(LongFlags.Five);
            dic.Count.ShouldBeEquivalentTo(1);
            dic[LongFlags.Five].ShouldBeEquivalentTo(42);
            dic = fm.ExecuteFlagsMatches(LongFlags.Eight | LongFlags.Five);
            dic.Count.ShouldBeEquivalentTo(2);
            dic[LongFlags.Five].ShouldBeEquivalentTo(42);
            dic[LongFlags.Eight].ShouldBeEquivalentTo(42);

            LongFlags.Nine.EqualsAny(LongFlags.Five, LongFlags.Eight).Should().BeFalse();
            fm.AssignToExactValue(LongFlags.Nine, (f) =>
                                  {
                                      f.ShouldBeEquivalentTo(LongFlags.Eight | LongFlags.Five | LongFlags.Nine);
                                      return 41;
                                  });
            dic = fm.ExecuteFlagsMatches(LongFlags.Eight | LongFlags.Five | LongFlags.Nine);
            dic.Count.ShouldBeEquivalentTo(3);
            dic[LongFlags.Five].ShouldBeEquivalentTo(42);
            dic[LongFlags.Eight].ShouldBeEquivalentTo(42);
            dic[LongFlags.Nine].ShouldBeEquivalentTo(41);
            fm.ExecuteExactMatch(LongFlags.Four).ShouldBeEquivalentTo(default(LongFlags));
        }

        [TestMethod, EnumTest]
        public void TestDescription()
        {
            SmallNonFlags.One.GetDescription().ShouldBeEquivalentTo("The Number One");
            SmallNonFlags.Five.GetDescription().ShouldBeEquivalentTo("The Number Five");
            SmallNonFlags result;
            Enums.TryGetFromDescription("The Number One", out result).Should().BeTrue();
            Enums.TryGetFromDescription("Foo", out result).Should().BeFalse();
            result.ShouldBeEquivalentTo(default(SmallNonFlags));
            DescriptionNonFlags.FooBarBaz.GetDescription().ShouldBeEquivalentTo("Foo Bar Baz");
            DescriptionNonFlags.FooBarBaz.GetDescription().ShouldBeEquivalentTo("Foo Bar Baz");
            DescriptionNonFlags.Foo_Bar_FORTY_Two.GetDescription().ShouldBeEquivalentTo("Foo Bar Forty Two");
            DescriptionNonFlags.LifeUniverseEVERYTHING.GetDescription().ShouldBeEquivalentTo("Life Universe EVERYTHING");
            DescriptionNonFlags.restaurant_end_of_universe.GetDescription().ShouldBeEquivalentTo("Restaurant End Of Universe");
        }

        [TestMethod, EnumTest]
        public void TestParameterised()
        {
            var fm = new ParameterizedEnumDelegateMap<LongFlags, string, int>();
            fm.AssignToExactValue(LongFlags.Two, (f, s) =>
                                  {
                                      s.ShouldBeEquivalentTo("testString");
                                      f.ShouldBeEquivalentTo(LongFlags.Two);
                                      return 42;
                                  });
            fm.ExecuteExactMatch(LongFlags.Two, "testString").ShouldBeEquivalentTo(42);
            fm.ExecuteExactMatch(LongFlags.Three, "noTestString").ShouldBeEquivalentTo(default(int));
        }

        [TestMethod, EnumTest]
        public void TestParameterisedWithDefaults()
        {
            var fm = new ParameterizedEnumDelegateMap<LongFlags, string, int>((f, s) =>
                                                                              {
                                                                                  s.ShouldBeEquivalentTo("noTestString");
                                                                                  f.ShouldBeEquivalentTo(LongFlags.Three);
                                                                                  return 1;
                                                                              });
            fm.AssignToExactValue(LongFlags.Two, (f, s) =>
                                  {
                                      s.ShouldBeEquivalentTo("testString");
                                      f.ShouldBeEquivalentTo(LongFlags.Two);
                                      return 42;
                                  });
            fm.ExecuteExactMatch(LongFlags.Two, "testString").ShouldBeEquivalentTo(42);
            fm.ExecuteExactMatch(LongFlags.Three, "noTestString").ShouldBeEquivalentTo(1);
        }

        [TestMethod, EnumTest]
        public void TestParameterisedCanExecuteFlags()
        {
            var fm = new ParameterizedEnumDelegateMap<LongFlags, string, int>();

            fm.AssignToEachFlag(LongFlags.Eight | LongFlags.Five, (f, s) =>
                                {
                                    s.ShouldBeEquivalentTo("testString");
                                    return 42;
                                });

            var dic = fm.ExecuteFlagsMatches(LongFlags.Five, "testString");
            dic.Count.ShouldBeEquivalentTo(1);
            dic[LongFlags.Five].ShouldBeEquivalentTo(42);
            dic = fm.ExecuteFlagsMatches(LongFlags.Eight | LongFlags.Five, "testString");
            dic.Count.ShouldBeEquivalentTo(2);
            dic[LongFlags.Five].ShouldBeEquivalentTo(42);
            dic[LongFlags.Eight].ShouldBeEquivalentTo(42);

            LongFlags.Nine.EqualsAny(LongFlags.Five, LongFlags.Eight).Should().BeFalse();
            fm.AssignToExactValue(LongFlags.Nine, (f,s) =>
                                  {
                                      f.ShouldBeEquivalentTo(LongFlags.Eight | LongFlags.Five | LongFlags.Nine);
                                      s.ShouldBeEquivalentTo("testString");
                                      return 41;
                                  });
            dic = fm.ExecuteFlagsMatches(LongFlags.Eight | LongFlags.Five | LongFlags.Nine, "testString");
            dic.Count.ShouldBeEquivalentTo(3);
            dic[LongFlags.Five].ShouldBeEquivalentTo(42);
            dic[LongFlags.Eight].ShouldBeEquivalentTo(42);
            dic[LongFlags.Nine].ShouldBeEquivalentTo(41);
            fm.ExecuteExactMatch(LongFlags.Four, "testString").ShouldBeEquivalentTo(default(LongFlags));
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
            ULongFlags.Eight.Format("G").ShouldBeEquivalentTo("Eight");
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
            SmallNonFlags.Eight.AsString().ShouldBeEquivalentTo(SmallNonFlags.Eight.ToString());
        }

        [TestMethod, EnumTest]
        public void TestGetNames()
        {
            IReadOnlyCollection<string> names = Enums.GetNames<SByteFlags>();
            names.Count.ShouldBeEquivalentTo(3);
            names.First().ShouldBeEquivalentTo("Five");
            names.Last().ShouldBeEquivalentTo("Seven");
            names.Any(x => x == "Six").Should().BeTrue();
            var asArray = Enums.GetNamesArray<SByteFlags>();
            asArray.Length.ShouldBeEquivalentTo(3);
            asArray.First().ShouldBeEquivalentTo("Five");
            asArray.Last().ShouldBeEquivalentTo("Seven");
            asArray.Any(x => x == "Six").Should().BeTrue();
        }

        [TestMethod, EnumTest]
        public void TestGetValuesAsArray()
        {
            /*
            SByteFlags[] values = Enums.GetValuesAsArray<SByteFlags>();
            values.Length.ShouldBeEquivalentTo(3);
            values.First().ShouldBeEquivalentTo(SByteFlags.Five);
            values.Last().ShouldBeEquivalentTo(SByteFlags.Seven);
            values.Any(x => x == SByteFlags.Six).Should().BeTrue();
            */
        }

        [TestMethod, EnumTest]
        public void TestGetValues()
        {
            IReadOnlyCollection<SByteFlags> names = Enums.GetValues<SByteFlags>();
            names.Count.ShouldBeEquivalentTo(3);
            names.First().ShouldBeEquivalentTo(SByteFlags.Five);
            names.Last().ShouldBeEquivalentTo(SByteFlags.Seven);
            names.Any(x => x == SByteFlags.Six).Should().BeTrue();
            var asArray = Enums.GetValuesArray<SByteFlags>();
            asArray.Length.ShouldBeEquivalentTo(3);
            asArray.First().ShouldBeEquivalentTo(SByteFlags.Five);
            asArray.Last().ShouldBeEquivalentTo(SByteFlags.Seven);
            names.Any(x => x == SByteFlags.Six).Should().BeTrue();
        }

        
        [TestMethod, EnumTest]
        public void TestAddFlag()
        {
            LongFlags.Eight.AddFlag(LongFlags.One).ShouldBeEquivalentTo(LongFlags.Eight | LongFlags.One);
        }

        [TestMethod, EnumTest]
        public void TestRemoveFlag()
        {
            (LongFlags.Five | LongFlags.Two).RemoveFlag(LongFlags.Five).ShouldBeEquivalentTo(LongFlags.Two);
        }

        [TestMethod, EnumTest]
        public void TestFlagsAsString()
        {
            LongFlags longFlagVal = LongFlags.Eight | LongFlags.Five;

            longFlagVal.AsString().ShouldBeEquivalentTo(longFlagVal.ToString());
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
            LongFlags ourResult = !ignoreCase ? Enums.Parse<LongFlags>(enumVal) : Enums.Parse<LongFlags>(enumVal, true);

            var theirResult = (LongFlags)Enum.Parse(typeof(LongFlags), enumVal);

            ourResult.ShouldBeEquivalentTo(theirResult);
        }

        public void TestParseSmallEnum(string enumVal, bool ignoreCase = false)
        {
            SmallNonFlags ourResult = !ignoreCase ? Enums.Parse<SmallNonFlags>(enumVal) : Enums.Parse<SmallNonFlags>(enumVal, true);
            SmallNonFlags theirResult = (SmallNonFlags)Enum.Parse(typeof(SmallNonFlags), enumVal, ignoreCase);

            ourResult.ShouldBeEquivalentTo(theirResult);
        }

        public void TestTryParseFlagsEnum(string enumVal, bool expectedValue, bool ignoreCase = false)
        {
            LongFlags ourResult;
            if (!ignoreCase)
                Enums.TryParse(enumVal, out ourResult).ShouldBeEquivalentTo(expectedValue);
            else
                Enums.TryParse(enumVal, true, out ourResult).ShouldBeEquivalentTo(expectedValue);

            LongFlags theirResult;
            Enum.TryParse(enumVal, ignoreCase, out theirResult);

            if (expectedValue)
                ourResult.ShouldBeEquivalentTo(theirResult);
        }

        public void TestTryParseSmallEnum(string enumVal, bool expectedResult, bool ignoreCase = false)
        {
            SmallNonFlags ourResult;
            if (!ignoreCase)
                Enums.TryParse(enumVal, out ourResult).ShouldBeEquivalentTo(expectedResult);
            else
                Enums.TryParse(enumVal, true, out ourResult).ShouldBeEquivalentTo(expectedResult);

            SmallNonFlags theirResult;
            Enum.TryParse(enumVal, ignoreCase, out theirResult);
            
            if (expectedResult)
                ourResult.ShouldBeEquivalentTo(theirResult);
        }
    }
}