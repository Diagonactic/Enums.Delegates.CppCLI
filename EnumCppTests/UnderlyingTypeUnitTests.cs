using System;
using System.Text;
using System.Collections.Generic;
using EnumCppTests.Attributes;
using DiagonacticTests;
using Diagonactic;
using FluentAssertions;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace EnumCppUnderlyingTypeTests
{
    /// <summary>
    /// Summary description for UnderlyingTypeUnitTests
    /// </summary>
    [TestClass]
    public class UnderlyingTypeUnitTests
    {
        [Flags]
        enum FlagsUInt16Enum : ushort
        {
            Five = 0x1,
            Six = 0x2,
            Seven = 0x4
        }

        [TestMethod, EnumTest]
        public void TestUInt16()
        {
            var flag1 = FlagsUInt16Enum.Five;
            var flag2 = FlagsUInt16Enum.Seven;
            var flag3 = FlagsUInt16Enum.Six;
            var flag1XorFlag2 = flag1 | flag2;
            var flag1NativeToString = flag1.ToString();
            var flag2NativeToString = flag2.ToString();
            flag1XorFlag2.HasFlag(flag1).Should().BeTrue();
            flag1XorFlag2.HasFlag(flag2).Should().BeTrue();
            flag1XorFlag2.HasFlag(flag3).Should().BeFalse();
            flag1XorFlag2.RemoveFlag(flag1).ShouldBeEquivalentTo(flag2);
            flag1.AsString().ShouldBeEquivalentTo(flag1NativeToString);
            flag1.AddFlag(flag2).ShouldBeEquivalentTo(flag1XorFlag2);
            var flagsAll = flag1 | flag2 | flag3;
            flag1.AddFlags(flag2, flag3).ShouldBeEquivalentTo(flagsAll);
            flagsAll.RemoveFlags(flag2, flag3).ShouldBeEquivalentTo(flag1);
            flag1XorFlag2.HasFlag(flag1).Should().BeTrue();
            flag1XorFlag2.HasFlag(flag3).Should().BeFalse();
            Enums.Parse<FlagsUInt16Enum>(flag1NativeToString).ShouldBeEquivalentTo(flag1);
            Enums.Parse<FlagsUInt16Enum>(flag2NativeToString).ShouldBeEquivalentTo(flag2);
            Enums.Parse<FlagsUInt16Enum>($"{flag1}, {flag2}").ShouldBeEquivalentTo(flag1XorFlag2);
            Enums.Parse<FlagsUInt16Enum>($"{flag2}, {flag1}").ShouldBeEquivalentTo(flag1XorFlag2);
        }

        [Flags]
        enum FlagsUIntEnum : uint
        {
            Five = 0x1,
            Six = 0x2,
            Seven = 0x4
        }

        [TestMethod, EnumTest]
        public void TestUInt32()
        {
            var flag1 = FlagsUIntEnum.Five;
            var flag2 = FlagsUIntEnum.Seven;
            var flag3 = FlagsUIntEnum.Six;
            var flag1XorFlag2 = flag1 | flag2;
            var flag1NativeToString = flag1.ToString();
            var flag2NativeToString = flag2.ToString();
            flag1.AsString().ShouldBeEquivalentTo(flag1NativeToString);
            flag1.AddFlag(flag2).ShouldBeEquivalentTo(flag1XorFlag2);
            var flagsAll = flag1 | flag2 | flag3;
            flag1.AddFlags(flag2, flag3).ShouldBeEquivalentTo(flagsAll);
            flag1XorFlag2.HasFlag(flag1).Should().BeTrue();
            flag1XorFlag2.HasFlag(flag3).Should().BeFalse();
            flagsAll.RemoveFlags(flag2, flag3).ShouldBeEquivalentTo(flag1);
            Enums.Parse<FlagsUIntEnum>(flag1NativeToString).ShouldBeEquivalentTo(flag1);
            Enums.Parse<FlagsUIntEnum>(flag2NativeToString).ShouldBeEquivalentTo(flag2);
            Enums.Parse<FlagsUIntEnum>($"{flag1}, {flag2}").ShouldBeEquivalentTo(flag1XorFlag2);
            Enums.Parse<FlagsUIntEnum>($"{flag2}, {flag1}").ShouldBeEquivalentTo(flag1XorFlag2);
            flag1XorFlag2.RemoveFlag(flag1).ShouldBeEquivalentTo(flag2);
        }

        [Flags]
        enum FlagsIntEnum : int
        {
            Five = 0x1,
            Six = 0x2,
            Seven = 0x4
        }

        [TestMethod, EnumTest]
        public void TestInt32()
        {
            var flag1 = FlagsIntEnum.Five;
            var flag2 = FlagsIntEnum.Seven;
            var flag3 = FlagsIntEnum.Six;
            var flag1XorFlag2 = flag1 | flag2;
            var flag1NativeToString = flag1.ToString();
            var flag2NativeToString = flag2.ToString();
            flag1.AsString().ShouldBeEquivalentTo(flag1NativeToString);
            flag1.AddFlag(flag2).ShouldBeEquivalentTo(flag1XorFlag2);
            var flagsAll = flag1 | flag2 | flag3;
            flag1.AddFlags(flag2, flag3).ShouldBeEquivalentTo(flagsAll);
            flagsAll.RemoveFlags(flag2, flag3).ShouldBeEquivalentTo(flag1);
            flag1XorFlag2.HasFlag(flag1).Should().BeTrue();
            flag1XorFlag2.HasFlag(flag3).Should().BeFalse();
            Enums.Parse<FlagsIntEnum>(flag1NativeToString).ShouldBeEquivalentTo(flag1);
            Enums.Parse<FlagsIntEnum>(flag2NativeToString).ShouldBeEquivalentTo(flag2);
            Enums.Parse<FlagsIntEnum>($"{flag1}, {flag2}").ShouldBeEquivalentTo(flag1XorFlag2);
            Enums.Parse<FlagsIntEnum>($"{flag2}, {flag1}").ShouldBeEquivalentTo(flag1XorFlag2);
            flag1XorFlag2.RemoveFlag(flag1).ShouldBeEquivalentTo(flag2);
        }

        [Flags]
        enum FlagsULongEnum : ulong
        {
            Five = 0x1,
            Six = 0x2,
            Seven = 0x4
        }

        [TestMethod, EnumTest]
        public void TestUInt64()
        {
            var flag1 = FlagsULongEnum.Five;
            var flag2 = FlagsULongEnum.Seven;
            var flag3 = FlagsULongEnum.Six;
            var flag1XorFlag2 = flag1 | flag2;
            var flag1NativeToString = flag1.ToString();
            var flag2NativeToString = flag2.ToString();
            flag1.AsString().ShouldBeEquivalentTo(flag1NativeToString);
            flag1.AddFlag(flag2).ShouldBeEquivalentTo(flag1XorFlag2);
            var flagsAll = flag1 | flag2 | flag3;
            flag1.AddFlags(flag2, flag3).ShouldBeEquivalentTo(flagsAll);
            flagsAll.RemoveFlags(flag2, flag3).ShouldBeEquivalentTo(flag1);
            flag1XorFlag2.HasFlag(flag1).Should().BeTrue();
            flag1XorFlag2.HasFlag(flag3).Should().BeFalse();
            Enums.Parse<FlagsULongEnum>(flag1NativeToString).ShouldBeEquivalentTo(flag1);
            Enums.Parse<FlagsULongEnum>(flag2NativeToString).ShouldBeEquivalentTo(flag2);
            Enums.Parse<FlagsULongEnum>($"{flag1}, {flag2}").ShouldBeEquivalentTo(flag1XorFlag2);
            Enums.Parse<FlagsULongEnum>($"{flag2}, {flag1}").ShouldBeEquivalentTo(flag1XorFlag2);
            flag1XorFlag2.RemoveFlag(flag1).ShouldBeEquivalentTo(flag2);
            flag1XorFlag2.HasFlag(flag1).Should().BeTrue();
            flag1XorFlag2.HasFlag(flag2).Should().BeTrue();
            flag1XorFlag2.HasFlag(flag3).Should().BeFalse();
        }

        [Flags]
        enum FlagsLongEnum : long
        {
            Five = 0x1,
            Six = 0x2,
            Seven = 0x4
        }

        [TestMethod, EnumTest]
        public void TestInt64()
        {
            var flag1 = FlagsLongEnum.Five;
            var flag2 = FlagsLongEnum.Seven;
            var flag3 = FlagsLongEnum.Six;
            var flag1XorFlag2 = flag1 | flag2;
            var flag1NativeToString = flag1.ToString();
            var flag2NativeToString = flag2.ToString();
            flag1.AsString().ShouldBeEquivalentTo(flag1NativeToString);
            flag1.AddFlag(flag2).ShouldBeEquivalentTo(flag1XorFlag2);
            var flagsAll = flag1 | flag2 | flag3;
            flag1.AddFlags(flag2, flag3).ShouldBeEquivalentTo(flagsAll);
            flagsAll.RemoveFlags(flag2, flag3).ShouldBeEquivalentTo(flag1);
            flag1XorFlag2.HasFlag(flag1).Should().BeTrue();
            flag1XorFlag2.HasFlag(flag3).Should().BeFalse();
            Enums.Parse<FlagsLongEnum>(flag1NativeToString).ShouldBeEquivalentTo(flag1);
            Enums.Parse<FlagsLongEnum>(flag2NativeToString).ShouldBeEquivalentTo(flag2);
            Enums.Parse<FlagsLongEnum>($"{flag1}, {flag2}").ShouldBeEquivalentTo(flag1XorFlag2);
            Enums.Parse<FlagsLongEnum>($"{flag2}, {flag1}").ShouldBeEquivalentTo(flag1XorFlag2);
            flag1XorFlag2.RemoveFlag(flag1).ShouldBeEquivalentTo(flag2);
            flag1XorFlag2.HasFlag(flag1).Should().BeTrue();
            flag1XorFlag2.HasFlag(flag2).Should().BeTrue();
            flag1XorFlag2.HasFlag(flag3).Should().BeFalse();
        }
        [Flags]
        enum FlagsShortEnum : short
        {
            Five = 0x1,
            Six = 0x2,
            Seven = 0x4
        }

        [TestMethod, EnumTest]
        public void TestInt16()
        {
            var flag1 = FlagsShortEnum.Five;
            var flag2 = FlagsShortEnum.Seven;
            var flag3 = FlagsShortEnum.Six;
            var flag1XorFlag2 = flag1 | flag2;
            var flag1NativeToString = flag1.ToString();
            var flag2NativeToString = flag2.ToString();
            var flagsAll = flag1 | flag2 | flag3;
            flag1.AddFlags(flag2, flag3).ShouldBeEquivalentTo(flagsAll);
            flagsAll.RemoveFlags(flag2, flag3).ShouldBeEquivalentTo(flag1);
            flag1XorFlag2.HasFlag(flag1).Should().BeTrue();
            flag1XorFlag2.HasFlag(flag3).Should().BeFalse();
            flag1.AsString().ShouldBeEquivalentTo(flag1NativeToString);
            flag1.AddFlag(flag2).ShouldBeEquivalentTo(flag1XorFlag2);
            Enums.Parse<FlagsShortEnum>(flag1NativeToString).ShouldBeEquivalentTo(flag1);
            Enums.Parse<FlagsShortEnum>(flag2NativeToString).ShouldBeEquivalentTo(flag2);
            Enums.Parse<FlagsShortEnum>($"{flag1}, {flag2}").ShouldBeEquivalentTo(flag1XorFlag2);
            Enums.Parse<FlagsShortEnum>($"{flag2}, {flag1}").ShouldBeEquivalentTo(flag1XorFlag2);
            flag1XorFlag2.RemoveFlag(flag1).ShouldBeEquivalentTo(flag2);
            flag1XorFlag2.HasFlag(flag1).Should().BeTrue();
            flag1XorFlag2.HasFlag(flag2).Should().BeTrue();
            flag1XorFlag2.HasFlag(flag3).Should().BeFalse();
        }

        public void TestEnumKind(Enum flag1, Enum flag2, Enum flag3)
        {
            
        }
        [Flags]
        enum FlagsSByteEnum : sbyte
        {
            Five = 0x1,
            Six = 0x2,
            Seven = 0x4
        }

        [TestMethod, EnumTest]
        public void TestSByte()
        {
            var flag1 = FlagsSByteEnum.Five;
            var flag2 = FlagsSByteEnum.Seven;
            var flag3 = FlagsSByteEnum.Six;
            var flag1XorFlag2 = flag1 | flag2;
            var flag1NativeToString = flag1.ToString();
            var flag2NativeToString = flag2.ToString();
            var flagsAll = flag1 | flag2 | flag3;
            flag1.AddFlags(flag2, flag3).ShouldBeEquivalentTo(flagsAll);
            flagsAll.RemoveFlags(flag2, flag3).ShouldBeEquivalentTo(flag1);
            flag1.AsString().ShouldBeEquivalentTo(flag1NativeToString);
            flag1.AddFlag(flag2).ShouldBeEquivalentTo(flag1XorFlag2);
            flagsAll.RemoveFlags(flag2, flag3).ShouldBeEquivalentTo(flag1);
            flag1XorFlag2.HasFlag(flag1).Should().BeTrue();
            flag1XorFlag2.HasFlag(flag3).Should().BeFalse();
            Enums.Parse<FlagsSByteEnum>(flag1NativeToString).ShouldBeEquivalentTo(flag1);
            Enums.Parse<FlagsSByteEnum>(flag2NativeToString).ShouldBeEquivalentTo(flag2);
            Enums.Parse<FlagsSByteEnum>($"{flag1}, {flag2}").ShouldBeEquivalentTo(flag1XorFlag2);
            Enums.Parse<FlagsSByteEnum>($"{flag2}, {flag1}").ShouldBeEquivalentTo(flag1XorFlag2);
            FlagsSByteEnum res;
            Enums.TryParse("Five", false, out res).Should().BeTrue();
            res.ShouldBeEquivalentTo(FlagsSByteEnum.Five);
            Enums.TryParse("afive", true, out res).Should().BeFalse();
            flag1XorFlag2.RemoveFlag(flag1).ShouldBeEquivalentTo(flag2);
            flag1XorFlag2.HasFlag(flag1).Should().BeTrue();
            flag1XorFlag2.HasFlag(flag2).Should().BeTrue();
            flag1XorFlag2.HasFlag(flag3).Should().BeFalse();
        }

        [Flags]
        enum FlagsByteEnum : byte
        {
            Five = 0x1,
            Six = 0x2,
            Seven = 0x4
        }

        [TestMethod, EnumTest]
        public void TestByte()
        {
            var flag1 = FlagsByteEnum.Five;
            var flag2 = FlagsByteEnum.Seven;
            var flag3 = FlagsByteEnum.Six;
            var flag1XorFlag2 = flag1 | flag2;
            var flag1NativeToString = flag1.ToString();
            var flag2NativeToString = flag2.ToString();
            flag1.AsString().ShouldBeEquivalentTo(flag1NativeToString);
            flag1.AddFlag(flag2).ShouldBeEquivalentTo(flag1XorFlag2);
            var flagsAll = flag1 | flag2 | flag3;
            flag1.AddFlags(flag2, flag3).ShouldBeEquivalentTo(flagsAll);
            flagsAll.RemoveFlags(flag2, flag3).ShouldBeEquivalentTo(flag1);
            flag1XorFlag2.HasFlag(flag1).Should().BeTrue();
            flag1XorFlag2.HasFlag(flag3).Should().BeFalse();
            Enums.Parse<FlagsByteEnum>(flag1NativeToString).ShouldBeEquivalentTo(flag1);
            Enums.Parse<FlagsByteEnum>(flag2NativeToString).ShouldBeEquivalentTo(flag2);
            Enums.Parse<FlagsByteEnum>($"{flag1}, {flag2}").ShouldBeEquivalentTo(flag1XorFlag2);
            Enums.Parse<FlagsByteEnum>($"{flag2}, {flag1}").ShouldBeEquivalentTo(flag1XorFlag2);
            flag1XorFlag2.RemoveFlag(flag1).ShouldBeEquivalentTo(flag2);
            flag1XorFlag2.HasFlag(flag1).Should().BeTrue();
            flag1XorFlag2.HasFlag(flag2).Should().BeTrue();
            flag1XorFlag2.HasFlag(flag3).Should().BeFalse();
        }
    }
}
