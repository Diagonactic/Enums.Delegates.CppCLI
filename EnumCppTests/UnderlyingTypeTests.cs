using System;
using Diagonactic;
using DiagonacticTests;
using EnumCppTests.Attributes;
using FluentAssertions;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using static Diagonactic.Enums.Flag;
using System.Diagnostics.CodeAnalysis;

namespace EnumCppUnderlyingTypeTests {
	[TestClass]
	public class EnumUnderlyingTests {
	
	[TestClass]
	public class TestFlagsSByteEnumEnumUnderlyingKind
	{
		[Flags]
		private enum TestEnum : sbyte	
		{ 
			All = unchecked((sbyte)~0),
			Invalid = -1,			
			Zero = 0,
			One = 0x000000001,
			Two = 0x000000002,
			Too = 0x000000004,
			Eight = 0x000000008,
			Ten = 0x000000010,
			TenAndTwelve = 0x000000030,			
		}

		private const TestEnum None            = TestEnum.Zero,
							   Flag1           = TestEnum.One, 
							   Flag2           = TestEnum.Two,
							   Flag4           = TestEnum.Too,
							   Flag8           = TestEnum.Eight,
							   Flag10          = TestEnum.Ten,
							   Flag1Flag2      = TestEnum.One | TestEnum.Two,
							   Flag1Flag2Flag4 = TestEnum.One | TestEnum.Two | TestEnum.Too,
							   AllFlags        = TestEnum.One | TestEnum.Two | TestEnum.Too | TestEnum.Eight | TestEnum.Ten;
		private const string Flag1StringValue = "One";
		private const string Flag1StringValueLowerCase = "one";
		private const string Flag2StringValue = "Two";		
		private const string Flag2Flag10StringValue = "Two, Ten";
		private const string Flag2Flag10StringValueLowerCase = "two, ten";
		
		[TestMethod, EnumTest]
		public void TestAllDefinedFlags()
		{
			var allFlags = TestEnum.Zero.AddAllDefinedFlags();
			var asNumeric = (sbyte)allFlags;
			allFlags.ShouldBeEquivalentTo(TestEnum.One | TestEnum.Two | TestEnum.Too | TestEnum.Eight | TestEnum.Ten);
			TestEnum.Zero.AddAllDefinedFlags().Should().NotBe(TestEnum.All);

		}

		[TestMethod, EnumTest]
        public void TestSByteAsString()
        {
            var flag1NativeToString = Flag1.ToString();
            var flag2NativeToString = Flag2.ToString();
			Flag1.AsString().ShouldBeEquivalentTo(flag1NativeToString);
			Flag2.AsString().ShouldBeEquivalentTo(flag2NativeToString);
			AllFlags.AsString().ShouldBeEquivalentTo(AllFlags.ToString());
			(Flag2 | Flag10).ShouldBeEquivalentTo(Flag2Flag10StringValue);
			(TestEnum.Zero | Flag1).AsString().ShouldBeEquivalentTo((TestEnum.Zero | Flag1).ToString());			
		}

		[TestMethod, EnumTest]
        public void TestSByteRemoveFlag()
		{
            Flag1Flag2.RemoveFlag(Flag1).ShouldBeEquivalentTo(Flag2);
			Flag1Flag2.RemoveFlag(Flag2).ShouldBeEquivalentTo(Flag1);
			Flag1Flag2.RemoveFlag(None).ShouldBeEquivalentTo(Flag1Flag2);
		}

		[TestMethod, EnumTest]
        public void TestSByteRemoveFlagIf()
		{
			Flag1Flag2.RemoveFlagIf(Flag2, false).ShouldBeEquivalentTo(Flag1Flag2);
			Flag1Flag2.RemoveFlagIf(Flag1, true).ShouldBeEquivalentTo(Flag2);
			Flag1Flag2.RemoveFlagIf(Flag2, () => false).ShouldBeEquivalentTo(Flag1Flag2);
			Flag1Flag2.RemoveFlagIf(Flag2, () => true).ShouldBeEquivalentTo(Flag1);
			Flag1Flag2.RemoveFlagIf(Flag2, s => s == TestEnum.One).ShouldBeEquivalentTo(Flag1Flag2); // false
			Flag1Flag2.RemoveFlagIf(Flag2, s => s.IsFlagSet(TestEnum.One)).ShouldBeEquivalentTo(Flag1); // true
		}

		[TestMethod, EnumTest]
        public void TestSByteModifyFlag()
		{
			Flag1Flag2.ModifyFlag(Flag4, false).ShouldBeEquivalentTo(Flag1Flag2);
			Flag1Flag2.ModifyFlag(Flag2, false).ShouldBeEquivalentTo(Flag1);
			Flag1Flag2.ModifyFlag(Flag4, true).ShouldBeEquivalentTo(Flag1Flag2Flag4);
			Flag1Flag2.ModifyFlag(Flag4, () => true).ShouldBeEquivalentTo(Flag1Flag2Flag4);
			Flag1Flag2.ModifyFlag(Flag4, () => false).ShouldBeEquivalentTo(Flag1Flag2);
			Flag1Flag2.ModifyFlag(Flag4, s => s.IsFlagSet(Flag1)).ShouldBeEquivalentTo(Flag1Flag2Flag4);
			Flag1Flag2.ModifyFlag(Flag4, s => !s.IsFlagSet(Flag1)).ShouldBeEquivalentTo(Flag1Flag2);
		}

		[TestMethod, EnumTest]
        public void TestSByteToList()
		{
            var result = Flag1Flag2.ToList();
			result[0].ShouldBeEquivalentTo(Flag1);
			result[1].ShouldBeEquivalentTo(Flag2);
			result.Count.ShouldBeEquivalentTo(2);
		}

		[TestMethod, EnumTest]
        public void TestSByteAreAllFlagsSet()
		{
			Flag1Flag2.AreAllFlagsSet(Flag1, Flag2).Should().BeTrue();
			Flag1Flag2.AreAllFlagsSet(Flag1, Flag2, Flag4).Should().BeFalse();
			None.AreAllFlagsSet(Flag1, Flag2).Should().BeFalse();
			None.AreAllFlagsSet(None).Should().BeTrue();
		}

		[TestMethod, EnumTest]
        public void TestSByteAreAnyFlagsSet()
		{
            Flag1Flag2.AreAnyFlagsSet(Flag1).Should().BeTrue();
			Flag1Flag2.AreAnyFlagsSet(Flag4).Should().BeFalse();
			Flag1Flag2.AreAnyFlagsSet(Flag1, Flag4).Should().BeTrue();
			Flag1Flag2.AreAnyFlagsSet(None, Flag1).Should().BeTrue();
			None.AreAnyFlagsSet(None, Flag1).Should().BeTrue();
			None.AreAnyFlagsSet(Flag1, Flag2).Should().BeFalse();
		}

		[TestMethod, EnumTest]
        public void TestSByteEqualsAny()
		{
            Flag1Flag2.EqualsAny(Flag1).Should().BeFalse();
			Flag1.EqualsAny(Flag1, Flag2, Flag4).Should().BeTrue();
			Flag1.EqualsAny(Flag2, Flag4).Should().BeFalse();
		}

		[TestMethod, EnumTest]
        public void TestSByteAddFlag()
        {
			None.AddFlag(Flag1).ShouldBeEquivalentTo(Flag1);
            Flag1.AddFlag(Flag2).ShouldBeEquivalentTo(Flag1Flag2);
			Flag1.AddFlag(None).ShouldBeEquivalentTo(Flag1);
			Flag1.AddFlag(Flag1).ShouldBeEquivalentTo(Flag1);
			Flag1Flag2.AddFlag(Flag1Flag2).ShouldBeEquivalentTo(Flag1Flag2);
		}

		[TestMethod, EnumTest]
        public void TestSByteAddFlagIf()
        {
			None.AddFlagIf(Flag1, true).ShouldBeEquivalentTo(Flag1);
			
			Flag1.AddFlagIf(Flag2, false).ShouldBeEquivalentTo(Flag1);
			Flag2.AddFlagIf(Flag1, true).ShouldBeEquivalentTo(Flag1Flag2);
			Flag2.AddFlagIf(Flag1, () => true).ShouldBeEquivalentTo(Flag1Flag2);
			Flag1.AddFlagIf(Flag2, () => false).ShouldBeEquivalentTo(Flag1);
			Flag2.AddFlagIf(Flag1, s => TestEnum.Two == s).ShouldBeEquivalentTo(Flag1Flag2);
			Flag1.AddFlagIf(Flag2, s => TestEnum.One != s).ShouldBeEquivalentTo(Flag1);
		}

		[TestMethod, EnumTest]
		public void TestSByteAddFlags()
		{
			None.AddFlags(Flag1, Flag2).ShouldBeEquivalentTo(Flag1Flag2);			
			Flag1Flag2.AddFlags(Flag1, Flag2).ShouldBeEquivalentTo(Flag1Flag2);
			Flag1Flag2.AddFlags(None).ShouldBeEquivalentTo(Flag1Flag2);
			var result = Flag1.AddFlags(Flag2, Flag4, Flag8, Flag10);
            result.ShouldBeEquivalentTo(AllFlags);
		}

		[TestMethod, EnumTest]
		public void TestSByteRemoveFlags()
		{
			None.RemoveFlags(Flag1, Flag2).ShouldBeEquivalentTo(None);
            AllFlags.RemoveFlags(Flag1, Flag2, Flag4, Flag8).ShouldBeEquivalentTo(Flag10);
		}
		
		[TestMethod, EnumTest]
		public void TestSByteIsFlagSet()
		{
			None.IsFlagSet(Flag1).ShouldBeEquivalentTo(None.HasFlag(Flag1));
			None.IsFlagSet(None).ShouldBeEquivalentTo(None.HasFlag(None));
			Flag1Flag2.IsFlagSet(Flag1).Should().BeTrue();
            Flag1Flag2.IsFlagSet(Flag4).Should().BeFalse();
		}

		[TestMethod, EnumTest]
		public void TestSByteTryParseBadValue()
		{
			TestEnum result;
			Enums.TryParse("foo", out result).ShouldBeEquivalentTo(false);
			Enums.TryParse("One, foo", out result).ShouldBeEquivalentTo(false); 
		}
		
		[TestMethod, EnumTest, SuppressMessage("ReSharper", "ExceptionNotDocumented")]
		public void TestSByteParseOneValue()
		{				
			Enums.Parse<TestEnum>(Flag1StringValue).ShouldBeEquivalentTo((TestEnum)Enum.Parse(typeof(TestEnum), Flag1StringValue));
            Enums.Parse<TestEnum>(Flag2StringValue).ShouldBeEquivalentTo((TestEnum)Enum.Parse(typeof(TestEnum), Flag2StringValue)); 			           
		}

		[TestMethod, EnumTest, SuppressMessage("ReSharper", "ExceptionNotDocumented")]
		public void TestSByteParseCaseInsensitiveValue()
		{				
			Enums.Parse<TestEnum>(Flag2Flag10StringValueLowerCase, true).ShouldBeEquivalentTo((TestEnum)Enum.Parse(typeof(TestEnum), Flag2Flag10StringValueLowerCase, true));
            Enums.Parse<TestEnum>(Flag1StringValueLowerCase, true).ShouldBeEquivalentTo((TestEnum)Enum.Parse(typeof(TestEnum), Flag1StringValueLowerCase, true)); 			           
		}

		[TestMethod, EnumTest, SuppressMessage("ReSharper", "ExceptionNotDocumented")]
		public void TestSByteTryParseOneValue()
		{
			TestEnum result;	
			Enums.TryParse(Flag1StringValue, out result).ShouldBeEquivalentTo(true);
			result.ShouldBeEquivalentTo((TestEnum)Enum.Parse(typeof(TestEnum), Flag1StringValue));
            Enums.TryParse(Flag2StringValue, out result).ShouldBeEquivalentTo(true);
			result.ShouldBeEquivalentTo((TestEnum)Enum.Parse(typeof(TestEnum), Flag2StringValue));
		}

		[TestMethod, EnumTest, SuppressMessage("ReSharper", "ExceptionNotDocumented")]
		public void TestSByteParseMultipleValues()
		{			
			Enums.Parse<TestEnum>($"{Flag1}, {Flag2}").ShouldBeEquivalentTo((TestEnum)Enum.Parse(typeof(TestEnum), $"{Flag1}, {Flag2}"));
            Enums.Parse<TestEnum>($"{Flag2}, {Flag1}").ShouldBeEquivalentTo((TestEnum)Enum.Parse(typeof(TestEnum), $"{Flag2}, {Flag1}"));
		}

		[TestMethod, EnumTest]
		public void TestSByteToEnum()
		{
			Enums.ToEnum<TestEnum>((sbyte)0x000000000).ShouldBeEquivalentTo(None);
			Enums.ToEnum<TestEnum>((sbyte)0x000000001).ShouldBeEquivalentTo(Flag1);
			Enums.ToEnum<TestEnum>((sbyte)0x000000001 | 0x000000002).ShouldBeEquivalentTo(Flag1Flag2);
			Enums.ToEnum<TestEnum>((Object)0x000000001).ShouldBeEquivalentTo(Flag1);
			var enumTest1 = (sbyte)0x000000000;
			var enumTest2 = (sbyte)0x000000001;
			var enumTest3 = ((sbyte)0x000000001 | 0x000000002);
			Enums.ToEnum<TestEnum>(enumTest1).ShouldBeEquivalentTo((TestEnum)Enum.ToObject(typeof(TestEnum), enumTest1));
			Enums.ToEnum<TestEnum>(enumTest2).ShouldBeEquivalentTo((TestEnum)Enum.ToObject(typeof(TestEnum), enumTest2));
			Enums.ToEnum<TestEnum>(enumTest3).ShouldBeEquivalentTo((TestEnum)Enum.ToObject(typeof(TestEnum), enumTest3));
		}

		[TestMethod, EnumTest]
		public void TestSByteToAsObject()
		{
			None.AsObject().ShouldBeEquivalentTo(None);
			Flag1.AsObject().ShouldBeEquivalentTo(Flag1);
			Flag1Flag2.AsObject().ShouldBeEquivalentTo((Flag1 | Flag2));
			var objResult = Enums.AsObject<TestEnum>((sbyte)(0x000000001 | 0x000000002)) as TestEnum? ?? TestEnum.Ten;
			objResult.ShouldBeEquivalentTo(Flag1 | Flag2);
        }
	}
	
	[TestClass]
	public class TestFlagsByteEnumEnumUnderlyingKind
	{
		[Flags]
		private enum TestEnum : byte	
		{ 
			All = unchecked((byte)~0),			
			Zero = 0,
			One = 0x000000001,
			Two = 0x000000002,
			Too = 0x000000004,
			Eight = 0x000000008,
			Ten = 0x000000010,
						
		}

		private const TestEnum None            = TestEnum.Zero,
							   Flag1           = TestEnum.One, 
							   Flag2           = TestEnum.Two,
							   Flag4           = TestEnum.Too,
							   Flag8           = TestEnum.Eight,
							   Flag10          = TestEnum.Ten,
							   Flag1Flag2      = TestEnum.One | TestEnum.Two,
							   Flag1Flag2Flag4 = TestEnum.One | TestEnum.Two | TestEnum.Too,
							   AllFlags        = TestEnum.One | TestEnum.Two | TestEnum.Too | TestEnum.Eight | TestEnum.Ten;
		private const string Flag1StringValue = "One";
		private const string Flag1StringValueLowerCase = "one";
		private const string Flag2StringValue = "Two";		
		private const string Flag2Flag10StringValue = "Two, Ten";
		private const string Flag2Flag10StringValueLowerCase = "two, ten";
		
		[TestMethod, EnumTest]
		public void TestAllDefinedFlags()
		{
			var allFlags = TestEnum.Zero.AddAllDefinedFlags();
			var asNumeric = (byte)allFlags;
			allFlags.ShouldBeEquivalentTo(TestEnum.One | TestEnum.Two | TestEnum.Too | TestEnum.Eight | TestEnum.Ten);
			TestEnum.Zero.AddAllDefinedFlags().Should().NotBe(TestEnum.All);

		}

		[TestMethod, EnumTest]
        public void TestByteAsString()
        {
            var flag1NativeToString = Flag1.ToString();
            var flag2NativeToString = Flag2.ToString();
			Flag1.AsString().ShouldBeEquivalentTo(flag1NativeToString);
			Flag2.AsString().ShouldBeEquivalentTo(flag2NativeToString);
			AllFlags.AsString().ShouldBeEquivalentTo(AllFlags.ToString());
			(Flag2 | Flag10).ShouldBeEquivalentTo(Flag2Flag10StringValue);
			(TestEnum.Zero | Flag1).AsString().ShouldBeEquivalentTo((TestEnum.Zero | Flag1).ToString());			
		}

		[TestMethod, EnumTest]
        public void TestByteRemoveFlag()
		{
            Flag1Flag2.RemoveFlag(Flag1).ShouldBeEquivalentTo(Flag2);
			Flag1Flag2.RemoveFlag(Flag2).ShouldBeEquivalentTo(Flag1);
			Flag1Flag2.RemoveFlag(None).ShouldBeEquivalentTo(Flag1Flag2);
		}

		[TestMethod, EnumTest]
        public void TestByteRemoveFlagIf()
		{
			Flag1Flag2.RemoveFlagIf(Flag2, false).ShouldBeEquivalentTo(Flag1Flag2);
			Flag1Flag2.RemoveFlagIf(Flag1, true).ShouldBeEquivalentTo(Flag2);
			Flag1Flag2.RemoveFlagIf(Flag2, () => false).ShouldBeEquivalentTo(Flag1Flag2);
			Flag1Flag2.RemoveFlagIf(Flag2, () => true).ShouldBeEquivalentTo(Flag1);
			Flag1Flag2.RemoveFlagIf(Flag2, s => s == TestEnum.One).ShouldBeEquivalentTo(Flag1Flag2); // false
			Flag1Flag2.RemoveFlagIf(Flag2, s => s.IsFlagSet(TestEnum.One)).ShouldBeEquivalentTo(Flag1); // true
		}

		[TestMethod, EnumTest]
        public void TestByteModifyFlag()
		{
			Flag1Flag2.ModifyFlag(Flag4, false).ShouldBeEquivalentTo(Flag1Flag2);
			Flag1Flag2.ModifyFlag(Flag2, false).ShouldBeEquivalentTo(Flag1);
			Flag1Flag2.ModifyFlag(Flag4, true).ShouldBeEquivalentTo(Flag1Flag2Flag4);
			Flag1Flag2.ModifyFlag(Flag4, () => true).ShouldBeEquivalentTo(Flag1Flag2Flag4);
			Flag1Flag2.ModifyFlag(Flag4, () => false).ShouldBeEquivalentTo(Flag1Flag2);
			Flag1Flag2.ModifyFlag(Flag4, s => s.IsFlagSet(Flag1)).ShouldBeEquivalentTo(Flag1Flag2Flag4);
			Flag1Flag2.ModifyFlag(Flag4, s => !s.IsFlagSet(Flag1)).ShouldBeEquivalentTo(Flag1Flag2);
		}

		[TestMethod, EnumTest]
        public void TestByteToList()
		{
            var result = Flag1Flag2.ToList();
			result[0].ShouldBeEquivalentTo(Flag1);
			result[1].ShouldBeEquivalentTo(Flag2);
			result.Count.ShouldBeEquivalentTo(2);
		}

		[TestMethod, EnumTest]
        public void TestByteAreAllFlagsSet()
		{
			Flag1Flag2.AreAllFlagsSet(Flag1, Flag2).Should().BeTrue();
			Flag1Flag2.AreAllFlagsSet(Flag1, Flag2, Flag4).Should().BeFalse();
			None.AreAllFlagsSet(Flag1, Flag2).Should().BeFalse();
			None.AreAllFlagsSet(None).Should().BeTrue();
		}

		[TestMethod, EnumTest]
        public void TestByteAreAnyFlagsSet()
		{
            Flag1Flag2.AreAnyFlagsSet(Flag1).Should().BeTrue();
			Flag1Flag2.AreAnyFlagsSet(Flag4).Should().BeFalse();
			Flag1Flag2.AreAnyFlagsSet(Flag1, Flag4).Should().BeTrue();
			Flag1Flag2.AreAnyFlagsSet(None, Flag1).Should().BeTrue();
			None.AreAnyFlagsSet(None, Flag1).Should().BeTrue();
			None.AreAnyFlagsSet(Flag1, Flag2).Should().BeFalse();
		}

		[TestMethod, EnumTest]
        public void TestByteEqualsAny()
		{
            Flag1Flag2.EqualsAny(Flag1).Should().BeFalse();
			Flag1.EqualsAny(Flag1, Flag2, Flag4).Should().BeTrue();
			Flag1.EqualsAny(Flag2, Flag4).Should().BeFalse();
		}

		[TestMethod, EnumTest]
        public void TestByteAddFlag()
        {
			None.AddFlag(Flag1).ShouldBeEquivalentTo(Flag1);
            Flag1.AddFlag(Flag2).ShouldBeEquivalentTo(Flag1Flag2);
			Flag1.AddFlag(None).ShouldBeEquivalentTo(Flag1);
			Flag1.AddFlag(Flag1).ShouldBeEquivalentTo(Flag1);
			Flag1Flag2.AddFlag(Flag1Flag2).ShouldBeEquivalentTo(Flag1Flag2);
		}

		[TestMethod, EnumTest]
        public void TestByteAddFlagIf()
        {
			None.AddFlagIf(Flag1, true).ShouldBeEquivalentTo(Flag1);
			
			Flag1.AddFlagIf(Flag2, false).ShouldBeEquivalentTo(Flag1);
			Flag2.AddFlagIf(Flag1, true).ShouldBeEquivalentTo(Flag1Flag2);
			Flag2.AddFlagIf(Flag1, () => true).ShouldBeEquivalentTo(Flag1Flag2);
			Flag1.AddFlagIf(Flag2, () => false).ShouldBeEquivalentTo(Flag1);
			Flag2.AddFlagIf(Flag1, s => TestEnum.Two == s).ShouldBeEquivalentTo(Flag1Flag2);
			Flag1.AddFlagIf(Flag2, s => TestEnum.One != s).ShouldBeEquivalentTo(Flag1);
		}

		[TestMethod, EnumTest]
		public void TestByteAddFlags()
		{
			None.AddFlags(Flag1, Flag2).ShouldBeEquivalentTo(Flag1Flag2);			
			Flag1Flag2.AddFlags(Flag1, Flag2).ShouldBeEquivalentTo(Flag1Flag2);
			Flag1Flag2.AddFlags(None).ShouldBeEquivalentTo(Flag1Flag2);
			var result = Flag1.AddFlags(Flag2, Flag4, Flag8, Flag10);
            result.ShouldBeEquivalentTo(AllFlags);
		}

		[TestMethod, EnumTest]
		public void TestByteRemoveFlags()
		{
			None.RemoveFlags(Flag1, Flag2).ShouldBeEquivalentTo(None);
            AllFlags.RemoveFlags(Flag1, Flag2, Flag4, Flag8).ShouldBeEquivalentTo(Flag10);
		}
		
		[TestMethod, EnumTest]
		public void TestByteIsFlagSet()
		{
			None.IsFlagSet(Flag1).ShouldBeEquivalentTo(None.HasFlag(Flag1));
			None.IsFlagSet(None).ShouldBeEquivalentTo(None.HasFlag(None));
			Flag1Flag2.IsFlagSet(Flag1).Should().BeTrue();
            Flag1Flag2.IsFlagSet(Flag4).Should().BeFalse();
		}

		[TestMethod, EnumTest]
		public void TestByteTryParseBadValue()
		{
			TestEnum result;
			Enums.TryParse("foo", out result).ShouldBeEquivalentTo(false);
			Enums.TryParse("One, foo", out result).ShouldBeEquivalentTo(false); 
		}
		
		[TestMethod, EnumTest, SuppressMessage("ReSharper", "ExceptionNotDocumented")]
		public void TestByteParseOneValue()
		{				
			Enums.Parse<TestEnum>(Flag1StringValue).ShouldBeEquivalentTo((TestEnum)Enum.Parse(typeof(TestEnum), Flag1StringValue));
            Enums.Parse<TestEnum>(Flag2StringValue).ShouldBeEquivalentTo((TestEnum)Enum.Parse(typeof(TestEnum), Flag2StringValue)); 			           
		}

		[TestMethod, EnumTest, SuppressMessage("ReSharper", "ExceptionNotDocumented")]
		public void TestByteParseCaseInsensitiveValue()
		{				
			Enums.Parse<TestEnum>(Flag2Flag10StringValueLowerCase, true).ShouldBeEquivalentTo((TestEnum)Enum.Parse(typeof(TestEnum), Flag2Flag10StringValueLowerCase, true));
            Enums.Parse<TestEnum>(Flag1StringValueLowerCase, true).ShouldBeEquivalentTo((TestEnum)Enum.Parse(typeof(TestEnum), Flag1StringValueLowerCase, true)); 			           
		}

		[TestMethod, EnumTest, SuppressMessage("ReSharper", "ExceptionNotDocumented")]
		public void TestByteTryParseOneValue()
		{
			TestEnum result;	
			Enums.TryParse(Flag1StringValue, out result).ShouldBeEquivalentTo(true);
			result.ShouldBeEquivalentTo((TestEnum)Enum.Parse(typeof(TestEnum), Flag1StringValue));
            Enums.TryParse(Flag2StringValue, out result).ShouldBeEquivalentTo(true);
			result.ShouldBeEquivalentTo((TestEnum)Enum.Parse(typeof(TestEnum), Flag2StringValue));
		}

		[TestMethod, EnumTest, SuppressMessage("ReSharper", "ExceptionNotDocumented")]
		public void TestByteParseMultipleValues()
		{			
			Enums.Parse<TestEnum>($"{Flag1}, {Flag2}").ShouldBeEquivalentTo((TestEnum)Enum.Parse(typeof(TestEnum), $"{Flag1}, {Flag2}"));
            Enums.Parse<TestEnum>($"{Flag2}, {Flag1}").ShouldBeEquivalentTo((TestEnum)Enum.Parse(typeof(TestEnum), $"{Flag2}, {Flag1}"));
		}

		[TestMethod, EnumTest]
		public void TestByteToEnum()
		{
			Enums.ToEnum<TestEnum>((byte)0x000000000).ShouldBeEquivalentTo(None);
			Enums.ToEnum<TestEnum>((byte)0x000000001).ShouldBeEquivalentTo(Flag1);
			Enums.ToEnum<TestEnum>((byte)0x000000001 | 0x000000002).ShouldBeEquivalentTo(Flag1Flag2);
			Enums.ToEnum<TestEnum>((Object)0x000000001).ShouldBeEquivalentTo(Flag1);
			var enumTest1 = (byte)0x000000000;
			var enumTest2 = (byte)0x000000001;
			var enumTest3 = ((byte)0x000000001 | 0x000000002);
			Enums.ToEnum<TestEnum>(enumTest1).ShouldBeEquivalentTo((TestEnum)Enum.ToObject(typeof(TestEnum), enumTest1));
			Enums.ToEnum<TestEnum>(enumTest2).ShouldBeEquivalentTo((TestEnum)Enum.ToObject(typeof(TestEnum), enumTest2));
			Enums.ToEnum<TestEnum>(enumTest3).ShouldBeEquivalentTo((TestEnum)Enum.ToObject(typeof(TestEnum), enumTest3));
		}

		[TestMethod, EnumTest]
		public void TestByteToAsObject()
		{
			None.AsObject().ShouldBeEquivalentTo(None);
			Flag1.AsObject().ShouldBeEquivalentTo(Flag1);
			Flag1Flag2.AsObject().ShouldBeEquivalentTo((Flag1 | Flag2));
			var objResult = Enums.AsObject<TestEnum>((byte)(0x000000001 | 0x000000002)) as TestEnum? ?? TestEnum.Ten;
			objResult.ShouldBeEquivalentTo(Flag1 | Flag2);
        }
	}
	
	[TestClass]
	public class TestFlagsInt16EnumEnumUnderlyingKind
	{
		[Flags]
		private enum TestEnum : short	
		{ 
			All = unchecked((short)~0),
			Invalid = -1,			
			Zero = 0,
			One = 0x000000008,
			Two = 0x000000010,
			Too = 0x000000020,
			Eight = 0x000000040,
			Ten = 0x000000080,
			TenAndTwelve = 0x000000180,			
		}

		private const TestEnum None            = TestEnum.Zero,
							   Flag1           = TestEnum.One, 
							   Flag2           = TestEnum.Two,
							   Flag4           = TestEnum.Too,
							   Flag8           = TestEnum.Eight,
							   Flag10          = TestEnum.Ten,
							   Flag1Flag2      = TestEnum.One | TestEnum.Two,
							   Flag1Flag2Flag4 = TestEnum.One | TestEnum.Two | TestEnum.Too,
							   AllFlags        = TestEnum.One | TestEnum.Two | TestEnum.Too | TestEnum.Eight | TestEnum.Ten;
		private const string Flag1StringValue = "One";
		private const string Flag1StringValueLowerCase = "one";
		private const string Flag2StringValue = "Two";		
		private const string Flag2Flag10StringValue = "Two, Ten";
		private const string Flag2Flag10StringValueLowerCase = "two, ten";
		
		[TestMethod, EnumTest]
		public void TestAllDefinedFlags()
		{
			var allFlags = TestEnum.Zero.AddAllDefinedFlags();
			var asNumeric = (short)allFlags;
			allFlags.ShouldBeEquivalentTo(TestEnum.One | TestEnum.Two | TestEnum.Too | TestEnum.Eight | TestEnum.Ten);
			TestEnum.Zero.AddAllDefinedFlags().Should().NotBe(TestEnum.All);

		}

		[TestMethod, EnumTest]
        public void TestInt16AsString()
        {
            var flag1NativeToString = Flag1.ToString();
            var flag2NativeToString = Flag2.ToString();
			Flag1.AsString().ShouldBeEquivalentTo(flag1NativeToString);
			Flag2.AsString().ShouldBeEquivalentTo(flag2NativeToString);
			AllFlags.AsString().ShouldBeEquivalentTo(AllFlags.ToString());
			(Flag2 | Flag10).ShouldBeEquivalentTo(Flag2Flag10StringValue);
			(TestEnum.Zero | Flag1).AsString().ShouldBeEquivalentTo((TestEnum.Zero | Flag1).ToString());			
		}

		[TestMethod, EnumTest]
        public void TestInt16RemoveFlag()
		{
            Flag1Flag2.RemoveFlag(Flag1).ShouldBeEquivalentTo(Flag2);
			Flag1Flag2.RemoveFlag(Flag2).ShouldBeEquivalentTo(Flag1);
			Flag1Flag2.RemoveFlag(None).ShouldBeEquivalentTo(Flag1Flag2);
		}

		[TestMethod, EnumTest]
        public void TestInt16RemoveFlagIf()
		{
			Flag1Flag2.RemoveFlagIf(Flag2, false).ShouldBeEquivalentTo(Flag1Flag2);
			Flag1Flag2.RemoveFlagIf(Flag1, true).ShouldBeEquivalentTo(Flag2);
			Flag1Flag2.RemoveFlagIf(Flag2, () => false).ShouldBeEquivalentTo(Flag1Flag2);
			Flag1Flag2.RemoveFlagIf(Flag2, () => true).ShouldBeEquivalentTo(Flag1);
			Flag1Flag2.RemoveFlagIf(Flag2, s => s == TestEnum.One).ShouldBeEquivalentTo(Flag1Flag2); // false
			Flag1Flag2.RemoveFlagIf(Flag2, s => s.IsFlagSet(TestEnum.One)).ShouldBeEquivalentTo(Flag1); // true
		}

		[TestMethod, EnumTest]
        public void TestInt16ModifyFlag()
		{
			Flag1Flag2.ModifyFlag(Flag4, false).ShouldBeEquivalentTo(Flag1Flag2);
			Flag1Flag2.ModifyFlag(Flag2, false).ShouldBeEquivalentTo(Flag1);
			Flag1Flag2.ModifyFlag(Flag4, true).ShouldBeEquivalentTo(Flag1Flag2Flag4);
			Flag1Flag2.ModifyFlag(Flag4, () => true).ShouldBeEquivalentTo(Flag1Flag2Flag4);
			Flag1Flag2.ModifyFlag(Flag4, () => false).ShouldBeEquivalentTo(Flag1Flag2);
			Flag1Flag2.ModifyFlag(Flag4, s => s.IsFlagSet(Flag1)).ShouldBeEquivalentTo(Flag1Flag2Flag4);
			Flag1Flag2.ModifyFlag(Flag4, s => !s.IsFlagSet(Flag1)).ShouldBeEquivalentTo(Flag1Flag2);
		}

		[TestMethod, EnumTest]
        public void TestInt16ToList()
		{
            var result = Flag1Flag2.ToList();
			result[0].ShouldBeEquivalentTo(Flag1);
			result[1].ShouldBeEquivalentTo(Flag2);
			result.Count.ShouldBeEquivalentTo(2);
		}

		[TestMethod, EnumTest]
        public void TestInt16AreAllFlagsSet()
		{
			Flag1Flag2.AreAllFlagsSet(Flag1, Flag2).Should().BeTrue();
			Flag1Flag2.AreAllFlagsSet(Flag1, Flag2, Flag4).Should().BeFalse();
			None.AreAllFlagsSet(Flag1, Flag2).Should().BeFalse();
			None.AreAllFlagsSet(None).Should().BeTrue();
		}

		[TestMethod, EnumTest]
        public void TestInt16AreAnyFlagsSet()
		{
            Flag1Flag2.AreAnyFlagsSet(Flag1).Should().BeTrue();
			Flag1Flag2.AreAnyFlagsSet(Flag4).Should().BeFalse();
			Flag1Flag2.AreAnyFlagsSet(Flag1, Flag4).Should().BeTrue();
			Flag1Flag2.AreAnyFlagsSet(None, Flag1).Should().BeTrue();
			None.AreAnyFlagsSet(None, Flag1).Should().BeTrue();
			None.AreAnyFlagsSet(Flag1, Flag2).Should().BeFalse();
		}

		[TestMethod, EnumTest]
        public void TestInt16EqualsAny()
		{
            Flag1Flag2.EqualsAny(Flag1).Should().BeFalse();
			Flag1.EqualsAny(Flag1, Flag2, Flag4).Should().BeTrue();
			Flag1.EqualsAny(Flag2, Flag4).Should().BeFalse();
		}

		[TestMethod, EnumTest]
        public void TestInt16AddFlag()
        {
			None.AddFlag(Flag1).ShouldBeEquivalentTo(Flag1);
            Flag1.AddFlag(Flag2).ShouldBeEquivalentTo(Flag1Flag2);
			Flag1.AddFlag(None).ShouldBeEquivalentTo(Flag1);
			Flag1.AddFlag(Flag1).ShouldBeEquivalentTo(Flag1);
			Flag1Flag2.AddFlag(Flag1Flag2).ShouldBeEquivalentTo(Flag1Flag2);
		}

		[TestMethod, EnumTest]
        public void TestInt16AddFlagIf()
        {
			None.AddFlagIf(Flag1, true).ShouldBeEquivalentTo(Flag1);
			
			Flag1.AddFlagIf(Flag2, false).ShouldBeEquivalentTo(Flag1);
			Flag2.AddFlagIf(Flag1, true).ShouldBeEquivalentTo(Flag1Flag2);
			Flag2.AddFlagIf(Flag1, () => true).ShouldBeEquivalentTo(Flag1Flag2);
			Flag1.AddFlagIf(Flag2, () => false).ShouldBeEquivalentTo(Flag1);
			Flag2.AddFlagIf(Flag1, s => TestEnum.Two == s).ShouldBeEquivalentTo(Flag1Flag2);
			Flag1.AddFlagIf(Flag2, s => TestEnum.One != s).ShouldBeEquivalentTo(Flag1);
		}

		[TestMethod, EnumTest]
		public void TestInt16AddFlags()
		{
			None.AddFlags(Flag1, Flag2).ShouldBeEquivalentTo(Flag1Flag2);			
			Flag1Flag2.AddFlags(Flag1, Flag2).ShouldBeEquivalentTo(Flag1Flag2);
			Flag1Flag2.AddFlags(None).ShouldBeEquivalentTo(Flag1Flag2);
			var result = Flag1.AddFlags(Flag2, Flag4, Flag8, Flag10);
            result.ShouldBeEquivalentTo(AllFlags);
		}

		[TestMethod, EnumTest]
		public void TestInt16RemoveFlags()
		{
			None.RemoveFlags(Flag1, Flag2).ShouldBeEquivalentTo(None);
            AllFlags.RemoveFlags(Flag1, Flag2, Flag4, Flag8).ShouldBeEquivalentTo(Flag10);
		}
		
		[TestMethod, EnumTest]
		public void TestInt16IsFlagSet()
		{
			None.IsFlagSet(Flag1).ShouldBeEquivalentTo(None.HasFlag(Flag1));
			None.IsFlagSet(None).ShouldBeEquivalentTo(None.HasFlag(None));
			Flag1Flag2.IsFlagSet(Flag1).Should().BeTrue();
            Flag1Flag2.IsFlagSet(Flag4).Should().BeFalse();
		}

		[TestMethod, EnumTest]
		public void TestInt16TryParseBadValue()
		{
			TestEnum result;
			Enums.TryParse("foo", out result).ShouldBeEquivalentTo(false);
			Enums.TryParse("One, foo", out result).ShouldBeEquivalentTo(false); 
		}
		
		[TestMethod, EnumTest, SuppressMessage("ReSharper", "ExceptionNotDocumented")]
		public void TestInt16ParseOneValue()
		{				
			Enums.Parse<TestEnum>(Flag1StringValue).ShouldBeEquivalentTo((TestEnum)Enum.Parse(typeof(TestEnum), Flag1StringValue));
            Enums.Parse<TestEnum>(Flag2StringValue).ShouldBeEquivalentTo((TestEnum)Enum.Parse(typeof(TestEnum), Flag2StringValue)); 			           
		}

		[TestMethod, EnumTest, SuppressMessage("ReSharper", "ExceptionNotDocumented")]
		public void TestInt16ParseCaseInsensitiveValue()
		{				
			Enums.Parse<TestEnum>(Flag2Flag10StringValueLowerCase, true).ShouldBeEquivalentTo((TestEnum)Enum.Parse(typeof(TestEnum), Flag2Flag10StringValueLowerCase, true));
            Enums.Parse<TestEnum>(Flag1StringValueLowerCase, true).ShouldBeEquivalentTo((TestEnum)Enum.Parse(typeof(TestEnum), Flag1StringValueLowerCase, true)); 			           
		}

		[TestMethod, EnumTest, SuppressMessage("ReSharper", "ExceptionNotDocumented")]
		public void TestInt16TryParseOneValue()
		{
			TestEnum result;	
			Enums.TryParse(Flag1StringValue, out result).ShouldBeEquivalentTo(true);
			result.ShouldBeEquivalentTo((TestEnum)Enum.Parse(typeof(TestEnum), Flag1StringValue));
            Enums.TryParse(Flag2StringValue, out result).ShouldBeEquivalentTo(true);
			result.ShouldBeEquivalentTo((TestEnum)Enum.Parse(typeof(TestEnum), Flag2StringValue));
		}

		[TestMethod, EnumTest, SuppressMessage("ReSharper", "ExceptionNotDocumented")]
		public void TestInt16ParseMultipleValues()
		{			
			Enums.Parse<TestEnum>($"{Flag1}, {Flag2}").ShouldBeEquivalentTo((TestEnum)Enum.Parse(typeof(TestEnum), $"{Flag1}, {Flag2}"));
            Enums.Parse<TestEnum>($"{Flag2}, {Flag1}").ShouldBeEquivalentTo((TestEnum)Enum.Parse(typeof(TestEnum), $"{Flag2}, {Flag1}"));
		}

		[TestMethod, EnumTest]
		public void TestInt16ToEnum()
		{
			Enums.ToEnum<TestEnum>((short)0x000000000).ShouldBeEquivalentTo(None);
			Enums.ToEnum<TestEnum>((short)0x000000008).ShouldBeEquivalentTo(Flag1);
			Enums.ToEnum<TestEnum>((short)0x000000008 | 0x000000010).ShouldBeEquivalentTo(Flag1Flag2);
			Enums.ToEnum<TestEnum>((Object)0x000000008).ShouldBeEquivalentTo(Flag1);
			var enumTest1 = (short)0x000000000;
			var enumTest2 = (short)0x000000008;
			var enumTest3 = ((short)0x000000008 | 0x000000010);
			Enums.ToEnum<TestEnum>(enumTest1).ShouldBeEquivalentTo((TestEnum)Enum.ToObject(typeof(TestEnum), enumTest1));
			Enums.ToEnum<TestEnum>(enumTest2).ShouldBeEquivalentTo((TestEnum)Enum.ToObject(typeof(TestEnum), enumTest2));
			Enums.ToEnum<TestEnum>(enumTest3).ShouldBeEquivalentTo((TestEnum)Enum.ToObject(typeof(TestEnum), enumTest3));
		}

		[TestMethod, EnumTest]
		public void TestInt16ToAsObject()
		{
			None.AsObject().ShouldBeEquivalentTo(None);
			Flag1.AsObject().ShouldBeEquivalentTo(Flag1);
			Flag1Flag2.AsObject().ShouldBeEquivalentTo((Flag1 | Flag2));
			var objResult = Enums.AsObject<TestEnum>((short)(0x000000008 | 0x000000010)) as TestEnum? ?? TestEnum.Ten;
			objResult.ShouldBeEquivalentTo(Flag1 | Flag2);
        }
	}
	
	[TestClass]
	public class TestFlagsUInt16EnumEnumUnderlyingKind
	{
		[Flags]
		private enum TestEnum : ushort	
		{ 
			All = unchecked((ushort)~0),			
			Zero = 0,
			One = 0x000000010,
			Two = 0x000000020,
			Too = 0x000000040,
			Eight = 0x000000080,
			Ten = 0x000000100,
						
		}

		private const TestEnum None            = TestEnum.Zero,
							   Flag1           = TestEnum.One, 
							   Flag2           = TestEnum.Two,
							   Flag4           = TestEnum.Too,
							   Flag8           = TestEnum.Eight,
							   Flag10          = TestEnum.Ten,
							   Flag1Flag2      = TestEnum.One | TestEnum.Two,
							   Flag1Flag2Flag4 = TestEnum.One | TestEnum.Two | TestEnum.Too,
							   AllFlags        = TestEnum.One | TestEnum.Two | TestEnum.Too | TestEnum.Eight | TestEnum.Ten;
		private const string Flag1StringValue = "One";
		private const string Flag1StringValueLowerCase = "one";
		private const string Flag2StringValue = "Two";		
		private const string Flag2Flag10StringValue = "Two, Ten";
		private const string Flag2Flag10StringValueLowerCase = "two, ten";
		
		[TestMethod, EnumTest]
		public void TestAllDefinedFlags()
		{
			var allFlags = TestEnum.Zero.AddAllDefinedFlags();
			var asNumeric = (ushort)allFlags;
			allFlags.ShouldBeEquivalentTo(TestEnum.One | TestEnum.Two | TestEnum.Too | TestEnum.Eight | TestEnum.Ten);
			TestEnum.Zero.AddAllDefinedFlags().Should().NotBe(TestEnum.All);

		}

		[TestMethod, EnumTest]
        public void TestUInt16AsString()
        {
            var flag1NativeToString = Flag1.ToString();
            var flag2NativeToString = Flag2.ToString();
			Flag1.AsString().ShouldBeEquivalentTo(flag1NativeToString);
			Flag2.AsString().ShouldBeEquivalentTo(flag2NativeToString);
			AllFlags.AsString().ShouldBeEquivalentTo(AllFlags.ToString());
			(Flag2 | Flag10).ShouldBeEquivalentTo(Flag2Flag10StringValue);
			(TestEnum.Zero | Flag1).AsString().ShouldBeEquivalentTo((TestEnum.Zero | Flag1).ToString());			
		}

		[TestMethod, EnumTest]
        public void TestUInt16RemoveFlag()
		{
            Flag1Flag2.RemoveFlag(Flag1).ShouldBeEquivalentTo(Flag2);
			Flag1Flag2.RemoveFlag(Flag2).ShouldBeEquivalentTo(Flag1);
			Flag1Flag2.RemoveFlag(None).ShouldBeEquivalentTo(Flag1Flag2);
		}

		[TestMethod, EnumTest]
        public void TestUInt16RemoveFlagIf()
		{
			Flag1Flag2.RemoveFlagIf(Flag2, false).ShouldBeEquivalentTo(Flag1Flag2);
			Flag1Flag2.RemoveFlagIf(Flag1, true).ShouldBeEquivalentTo(Flag2);
			Flag1Flag2.RemoveFlagIf(Flag2, () => false).ShouldBeEquivalentTo(Flag1Flag2);
			Flag1Flag2.RemoveFlagIf(Flag2, () => true).ShouldBeEquivalentTo(Flag1);
			Flag1Flag2.RemoveFlagIf(Flag2, s => s == TestEnum.One).ShouldBeEquivalentTo(Flag1Flag2); // false
			Flag1Flag2.RemoveFlagIf(Flag2, s => s.IsFlagSet(TestEnum.One)).ShouldBeEquivalentTo(Flag1); // true
		}

		[TestMethod, EnumTest]
        public void TestUInt16ModifyFlag()
		{
			Flag1Flag2.ModifyFlag(Flag4, false).ShouldBeEquivalentTo(Flag1Flag2);
			Flag1Flag2.ModifyFlag(Flag2, false).ShouldBeEquivalentTo(Flag1);
			Flag1Flag2.ModifyFlag(Flag4, true).ShouldBeEquivalentTo(Flag1Flag2Flag4);
			Flag1Flag2.ModifyFlag(Flag4, () => true).ShouldBeEquivalentTo(Flag1Flag2Flag4);
			Flag1Flag2.ModifyFlag(Flag4, () => false).ShouldBeEquivalentTo(Flag1Flag2);
			Flag1Flag2.ModifyFlag(Flag4, s => s.IsFlagSet(Flag1)).ShouldBeEquivalentTo(Flag1Flag2Flag4);
			Flag1Flag2.ModifyFlag(Flag4, s => !s.IsFlagSet(Flag1)).ShouldBeEquivalentTo(Flag1Flag2);
		}

		[TestMethod, EnumTest]
        public void TestUInt16ToList()
		{
            var result = Flag1Flag2.ToList();
			result[0].ShouldBeEquivalentTo(Flag1);
			result[1].ShouldBeEquivalentTo(Flag2);
			result.Count.ShouldBeEquivalentTo(2);
		}

		[TestMethod, EnumTest]
        public void TestUInt16AreAllFlagsSet()
		{
			Flag1Flag2.AreAllFlagsSet(Flag1, Flag2).Should().BeTrue();
			Flag1Flag2.AreAllFlagsSet(Flag1, Flag2, Flag4).Should().BeFalse();
			None.AreAllFlagsSet(Flag1, Flag2).Should().BeFalse();
			None.AreAllFlagsSet(None).Should().BeTrue();
		}

		[TestMethod, EnumTest]
        public void TestUInt16AreAnyFlagsSet()
		{
            Flag1Flag2.AreAnyFlagsSet(Flag1).Should().BeTrue();
			Flag1Flag2.AreAnyFlagsSet(Flag4).Should().BeFalse();
			Flag1Flag2.AreAnyFlagsSet(Flag1, Flag4).Should().BeTrue();
			Flag1Flag2.AreAnyFlagsSet(None, Flag1).Should().BeTrue();
			None.AreAnyFlagsSet(None, Flag1).Should().BeTrue();
			None.AreAnyFlagsSet(Flag1, Flag2).Should().BeFalse();
		}

		[TestMethod, EnumTest]
        public void TestUInt16EqualsAny()
		{
            Flag1Flag2.EqualsAny(Flag1).Should().BeFalse();
			Flag1.EqualsAny(Flag1, Flag2, Flag4).Should().BeTrue();
			Flag1.EqualsAny(Flag2, Flag4).Should().BeFalse();
		}

		[TestMethod, EnumTest]
        public void TestUInt16AddFlag()
        {
			None.AddFlag(Flag1).ShouldBeEquivalentTo(Flag1);
            Flag1.AddFlag(Flag2).ShouldBeEquivalentTo(Flag1Flag2);
			Flag1.AddFlag(None).ShouldBeEquivalentTo(Flag1);
			Flag1.AddFlag(Flag1).ShouldBeEquivalentTo(Flag1);
			Flag1Flag2.AddFlag(Flag1Flag2).ShouldBeEquivalentTo(Flag1Flag2);
		}

		[TestMethod, EnumTest]
        public void TestUInt16AddFlagIf()
        {
			None.AddFlagIf(Flag1, true).ShouldBeEquivalentTo(Flag1);
			
			Flag1.AddFlagIf(Flag2, false).ShouldBeEquivalentTo(Flag1);
			Flag2.AddFlagIf(Flag1, true).ShouldBeEquivalentTo(Flag1Flag2);
			Flag2.AddFlagIf(Flag1, () => true).ShouldBeEquivalentTo(Flag1Flag2);
			Flag1.AddFlagIf(Flag2, () => false).ShouldBeEquivalentTo(Flag1);
			Flag2.AddFlagIf(Flag1, s => TestEnum.Two == s).ShouldBeEquivalentTo(Flag1Flag2);
			Flag1.AddFlagIf(Flag2, s => TestEnum.One != s).ShouldBeEquivalentTo(Flag1);
		}

		[TestMethod, EnumTest]
		public void TestUInt16AddFlags()
		{
			None.AddFlags(Flag1, Flag2).ShouldBeEquivalentTo(Flag1Flag2);			
			Flag1Flag2.AddFlags(Flag1, Flag2).ShouldBeEquivalentTo(Flag1Flag2);
			Flag1Flag2.AddFlags(None).ShouldBeEquivalentTo(Flag1Flag2);
			var result = Flag1.AddFlags(Flag2, Flag4, Flag8, Flag10);
            result.ShouldBeEquivalentTo(AllFlags);
		}

		[TestMethod, EnumTest]
		public void TestUInt16RemoveFlags()
		{
			None.RemoveFlags(Flag1, Flag2).ShouldBeEquivalentTo(None);
            AllFlags.RemoveFlags(Flag1, Flag2, Flag4, Flag8).ShouldBeEquivalentTo(Flag10);
		}
		
		[TestMethod, EnumTest]
		public void TestUInt16IsFlagSet()
		{
			None.IsFlagSet(Flag1).ShouldBeEquivalentTo(None.HasFlag(Flag1));
			None.IsFlagSet(None).ShouldBeEquivalentTo(None.HasFlag(None));
			Flag1Flag2.IsFlagSet(Flag1).Should().BeTrue();
            Flag1Flag2.IsFlagSet(Flag4).Should().BeFalse();
		}

		[TestMethod, EnumTest]
		public void TestUInt16TryParseBadValue()
		{
			TestEnum result;
			Enums.TryParse("foo", out result).ShouldBeEquivalentTo(false);
			Enums.TryParse("One, foo", out result).ShouldBeEquivalentTo(false); 
		}
		
		[TestMethod, EnumTest, SuppressMessage("ReSharper", "ExceptionNotDocumented")]
		public void TestUInt16ParseOneValue()
		{				
			Enums.Parse<TestEnum>(Flag1StringValue).ShouldBeEquivalentTo((TestEnum)Enum.Parse(typeof(TestEnum), Flag1StringValue));
            Enums.Parse<TestEnum>(Flag2StringValue).ShouldBeEquivalentTo((TestEnum)Enum.Parse(typeof(TestEnum), Flag2StringValue)); 			           
		}

		[TestMethod, EnumTest, SuppressMessage("ReSharper", "ExceptionNotDocumented")]
		public void TestUInt16ParseCaseInsensitiveValue()
		{				
			Enums.Parse<TestEnum>(Flag2Flag10StringValueLowerCase, true).ShouldBeEquivalentTo((TestEnum)Enum.Parse(typeof(TestEnum), Flag2Flag10StringValueLowerCase, true));
            Enums.Parse<TestEnum>(Flag1StringValueLowerCase, true).ShouldBeEquivalentTo((TestEnum)Enum.Parse(typeof(TestEnum), Flag1StringValueLowerCase, true)); 			           
		}

		[TestMethod, EnumTest, SuppressMessage("ReSharper", "ExceptionNotDocumented")]
		public void TestUInt16TryParseOneValue()
		{
			TestEnum result;	
			Enums.TryParse(Flag1StringValue, out result).ShouldBeEquivalentTo(true);
			result.ShouldBeEquivalentTo((TestEnum)Enum.Parse(typeof(TestEnum), Flag1StringValue));
            Enums.TryParse(Flag2StringValue, out result).ShouldBeEquivalentTo(true);
			result.ShouldBeEquivalentTo((TestEnum)Enum.Parse(typeof(TestEnum), Flag2StringValue));
		}

		[TestMethod, EnumTest, SuppressMessage("ReSharper", "ExceptionNotDocumented")]
		public void TestUInt16ParseMultipleValues()
		{			
			Enums.Parse<TestEnum>($"{Flag1}, {Flag2}").ShouldBeEquivalentTo((TestEnum)Enum.Parse(typeof(TestEnum), $"{Flag1}, {Flag2}"));
            Enums.Parse<TestEnum>($"{Flag2}, {Flag1}").ShouldBeEquivalentTo((TestEnum)Enum.Parse(typeof(TestEnum), $"{Flag2}, {Flag1}"));
		}

		[TestMethod, EnumTest]
		public void TestUInt16ToEnum()
		{
			Enums.ToEnum<TestEnum>((ushort)0x000000000).ShouldBeEquivalentTo(None);
			Enums.ToEnum<TestEnum>((ushort)0x000000010).ShouldBeEquivalentTo(Flag1);
			Enums.ToEnum<TestEnum>((ushort)0x000000010 | 0x000000020).ShouldBeEquivalentTo(Flag1Flag2);
			Enums.ToEnum<TestEnum>((Object)0x000000010).ShouldBeEquivalentTo(Flag1);
			var enumTest1 = (ushort)0x000000000;
			var enumTest2 = (ushort)0x000000010;
			var enumTest3 = ((ushort)0x000000010 | 0x000000020);
			Enums.ToEnum<TestEnum>(enumTest1).ShouldBeEquivalentTo((TestEnum)Enum.ToObject(typeof(TestEnum), enumTest1));
			Enums.ToEnum<TestEnum>(enumTest2).ShouldBeEquivalentTo((TestEnum)Enum.ToObject(typeof(TestEnum), enumTest2));
			Enums.ToEnum<TestEnum>(enumTest3).ShouldBeEquivalentTo((TestEnum)Enum.ToObject(typeof(TestEnum), enumTest3));
		}

		[TestMethod, EnumTest]
		public void TestUInt16ToAsObject()
		{
			None.AsObject().ShouldBeEquivalentTo(None);
			Flag1.AsObject().ShouldBeEquivalentTo(Flag1);
			Flag1Flag2.AsObject().ShouldBeEquivalentTo((Flag1 | Flag2));
			var objResult = Enums.AsObject<TestEnum>((ushort)(0x000000010 | 0x000000020)) as TestEnum? ?? TestEnum.Ten;
			objResult.ShouldBeEquivalentTo(Flag1 | Flag2);
        }
	}
	
	[TestClass]
	public class TestFlagsInt32EnumEnumUnderlyingKind
	{
		[Flags]
		private enum TestEnum : int	
		{ 
			All = unchecked((int)~0),
			Invalid = -1,			
			Zero = 0,
			One = 0x000008000,
			Two = 0x000010000,
			Too = 0x000020000,
			Eight = 0x000040000,
			Ten = 0x000080000,
			TenAndTwelve = 0x000180000,			
		}

		private const TestEnum None            = TestEnum.Zero,
							   Flag1           = TestEnum.One, 
							   Flag2           = TestEnum.Two,
							   Flag4           = TestEnum.Too,
							   Flag8           = TestEnum.Eight,
							   Flag10          = TestEnum.Ten,
							   Flag1Flag2      = TestEnum.One | TestEnum.Two,
							   Flag1Flag2Flag4 = TestEnum.One | TestEnum.Two | TestEnum.Too,
							   AllFlags        = TestEnum.One | TestEnum.Two | TestEnum.Too | TestEnum.Eight | TestEnum.Ten;
		private const string Flag1StringValue = "One";
		private const string Flag1StringValueLowerCase = "one";
		private const string Flag2StringValue = "Two";		
		private const string Flag2Flag10StringValue = "Two, Ten";
		private const string Flag2Flag10StringValueLowerCase = "two, ten";
		
		[TestMethod, EnumTest]
		public void TestAllDefinedFlags()
		{
			var allFlags = TestEnum.Zero.AddAllDefinedFlags();
			var asNumeric = (int)allFlags;
			allFlags.ShouldBeEquivalentTo(TestEnum.One | TestEnum.Two | TestEnum.Too | TestEnum.Eight | TestEnum.Ten);
			TestEnum.Zero.AddAllDefinedFlags().Should().NotBe(TestEnum.All);

		}

		[TestMethod, EnumTest]
        public void TestInt32AsString()
        {
            var flag1NativeToString = Flag1.ToString();
            var flag2NativeToString = Flag2.ToString();
			Flag1.AsString().ShouldBeEquivalentTo(flag1NativeToString);
			Flag2.AsString().ShouldBeEquivalentTo(flag2NativeToString);
			AllFlags.AsString().ShouldBeEquivalentTo(AllFlags.ToString());
			(Flag2 | Flag10).ShouldBeEquivalentTo(Flag2Flag10StringValue);
			(TestEnum.Zero | Flag1).AsString().ShouldBeEquivalentTo((TestEnum.Zero | Flag1).ToString());			
		}

		[TestMethod, EnumTest]
        public void TestInt32RemoveFlag()
		{
            Flag1Flag2.RemoveFlag(Flag1).ShouldBeEquivalentTo(Flag2);
			Flag1Flag2.RemoveFlag(Flag2).ShouldBeEquivalentTo(Flag1);
			Flag1Flag2.RemoveFlag(None).ShouldBeEquivalentTo(Flag1Flag2);
		}

		[TestMethod, EnumTest]
        public void TestInt32RemoveFlagIf()
		{
			Flag1Flag2.RemoveFlagIf(Flag2, false).ShouldBeEquivalentTo(Flag1Flag2);
			Flag1Flag2.RemoveFlagIf(Flag1, true).ShouldBeEquivalentTo(Flag2);
			Flag1Flag2.RemoveFlagIf(Flag2, () => false).ShouldBeEquivalentTo(Flag1Flag2);
			Flag1Flag2.RemoveFlagIf(Flag2, () => true).ShouldBeEquivalentTo(Flag1);
			Flag1Flag2.RemoveFlagIf(Flag2, s => s == TestEnum.One).ShouldBeEquivalentTo(Flag1Flag2); // false
			Flag1Flag2.RemoveFlagIf(Flag2, s => s.IsFlagSet(TestEnum.One)).ShouldBeEquivalentTo(Flag1); // true
		}

		[TestMethod, EnumTest]
        public void TestInt32ModifyFlag()
		{
			Flag1Flag2.ModifyFlag(Flag4, false).ShouldBeEquivalentTo(Flag1Flag2);
			Flag1Flag2.ModifyFlag(Flag2, false).ShouldBeEquivalentTo(Flag1);
			Flag1Flag2.ModifyFlag(Flag4, true).ShouldBeEquivalentTo(Flag1Flag2Flag4);
			Flag1Flag2.ModifyFlag(Flag4, () => true).ShouldBeEquivalentTo(Flag1Flag2Flag4);
			Flag1Flag2.ModifyFlag(Flag4, () => false).ShouldBeEquivalentTo(Flag1Flag2);
			Flag1Flag2.ModifyFlag(Flag4, s => s.IsFlagSet(Flag1)).ShouldBeEquivalentTo(Flag1Flag2Flag4);
			Flag1Flag2.ModifyFlag(Flag4, s => !s.IsFlagSet(Flag1)).ShouldBeEquivalentTo(Flag1Flag2);
		}

		[TestMethod, EnumTest]
        public void TestInt32ToList()
		{
            var result = Flag1Flag2.ToList();
			result[0].ShouldBeEquivalentTo(Flag1);
			result[1].ShouldBeEquivalentTo(Flag2);
			result.Count.ShouldBeEquivalentTo(2);
		}

		[TestMethod, EnumTest]
        public void TestInt32AreAllFlagsSet()
		{
			Flag1Flag2.AreAllFlagsSet(Flag1, Flag2).Should().BeTrue();
			Flag1Flag2.AreAllFlagsSet(Flag1, Flag2, Flag4).Should().BeFalse();
			None.AreAllFlagsSet(Flag1, Flag2).Should().BeFalse();
			None.AreAllFlagsSet(None).Should().BeTrue();
		}

		[TestMethod, EnumTest]
        public void TestInt32AreAnyFlagsSet()
		{
            Flag1Flag2.AreAnyFlagsSet(Flag1).Should().BeTrue();
			Flag1Flag2.AreAnyFlagsSet(Flag4).Should().BeFalse();
			Flag1Flag2.AreAnyFlagsSet(Flag1, Flag4).Should().BeTrue();
			Flag1Flag2.AreAnyFlagsSet(None, Flag1).Should().BeTrue();
			None.AreAnyFlagsSet(None, Flag1).Should().BeTrue();
			None.AreAnyFlagsSet(Flag1, Flag2).Should().BeFalse();
		}

		[TestMethod, EnumTest]
        public void TestInt32EqualsAny()
		{
            Flag1Flag2.EqualsAny(Flag1).Should().BeFalse();
			Flag1.EqualsAny(Flag1, Flag2, Flag4).Should().BeTrue();
			Flag1.EqualsAny(Flag2, Flag4).Should().BeFalse();
		}

		[TestMethod, EnumTest]
        public void TestInt32AddFlag()
        {
			None.AddFlag(Flag1).ShouldBeEquivalentTo(Flag1);
            Flag1.AddFlag(Flag2).ShouldBeEquivalentTo(Flag1Flag2);
			Flag1.AddFlag(None).ShouldBeEquivalentTo(Flag1);
			Flag1.AddFlag(Flag1).ShouldBeEquivalentTo(Flag1);
			Flag1Flag2.AddFlag(Flag1Flag2).ShouldBeEquivalentTo(Flag1Flag2);
		}

		[TestMethod, EnumTest]
        public void TestInt32AddFlagIf()
        {
			None.AddFlagIf(Flag1, true).ShouldBeEquivalentTo(Flag1);
			
			Flag1.AddFlagIf(Flag2, false).ShouldBeEquivalentTo(Flag1);
			Flag2.AddFlagIf(Flag1, true).ShouldBeEquivalentTo(Flag1Flag2);
			Flag2.AddFlagIf(Flag1, () => true).ShouldBeEquivalentTo(Flag1Flag2);
			Flag1.AddFlagIf(Flag2, () => false).ShouldBeEquivalentTo(Flag1);
			Flag2.AddFlagIf(Flag1, s => TestEnum.Two == s).ShouldBeEquivalentTo(Flag1Flag2);
			Flag1.AddFlagIf(Flag2, s => TestEnum.One != s).ShouldBeEquivalentTo(Flag1);
		}

		[TestMethod, EnumTest]
		public void TestInt32AddFlags()
		{
			None.AddFlags(Flag1, Flag2).ShouldBeEquivalentTo(Flag1Flag2);			
			Flag1Flag2.AddFlags(Flag1, Flag2).ShouldBeEquivalentTo(Flag1Flag2);
			Flag1Flag2.AddFlags(None).ShouldBeEquivalentTo(Flag1Flag2);
			var result = Flag1.AddFlags(Flag2, Flag4, Flag8, Flag10);
            result.ShouldBeEquivalentTo(AllFlags);
		}

		[TestMethod, EnumTest]
		public void TestInt32RemoveFlags()
		{
			None.RemoveFlags(Flag1, Flag2).ShouldBeEquivalentTo(None);
            AllFlags.RemoveFlags(Flag1, Flag2, Flag4, Flag8).ShouldBeEquivalentTo(Flag10);
		}
		
		[TestMethod, EnumTest]
		public void TestInt32IsFlagSet()
		{
			None.IsFlagSet(Flag1).ShouldBeEquivalentTo(None.HasFlag(Flag1));
			None.IsFlagSet(None).ShouldBeEquivalentTo(None.HasFlag(None));
			Flag1Flag2.IsFlagSet(Flag1).Should().BeTrue();
            Flag1Flag2.IsFlagSet(Flag4).Should().BeFalse();
		}

		[TestMethod, EnumTest]
		public void TestInt32TryParseBadValue()
		{
			TestEnum result;
			Enums.TryParse("foo", out result).ShouldBeEquivalentTo(false);
			Enums.TryParse("One, foo", out result).ShouldBeEquivalentTo(false); 
		}
		
		[TestMethod, EnumTest, SuppressMessage("ReSharper", "ExceptionNotDocumented")]
		public void TestInt32ParseOneValue()
		{				
			Enums.Parse<TestEnum>(Flag1StringValue).ShouldBeEquivalentTo((TestEnum)Enum.Parse(typeof(TestEnum), Flag1StringValue));
            Enums.Parse<TestEnum>(Flag2StringValue).ShouldBeEquivalentTo((TestEnum)Enum.Parse(typeof(TestEnum), Flag2StringValue)); 			           
		}

		[TestMethod, EnumTest, SuppressMessage("ReSharper", "ExceptionNotDocumented")]
		public void TestInt32ParseCaseInsensitiveValue()
		{				
			Enums.Parse<TestEnum>(Flag2Flag10StringValueLowerCase, true).ShouldBeEquivalentTo((TestEnum)Enum.Parse(typeof(TestEnum), Flag2Flag10StringValueLowerCase, true));
            Enums.Parse<TestEnum>(Flag1StringValueLowerCase, true).ShouldBeEquivalentTo((TestEnum)Enum.Parse(typeof(TestEnum), Flag1StringValueLowerCase, true)); 			           
		}

		[TestMethod, EnumTest, SuppressMessage("ReSharper", "ExceptionNotDocumented")]
		public void TestInt32TryParseOneValue()
		{
			TestEnum result;	
			Enums.TryParse(Flag1StringValue, out result).ShouldBeEquivalentTo(true);
			result.ShouldBeEquivalentTo((TestEnum)Enum.Parse(typeof(TestEnum), Flag1StringValue));
            Enums.TryParse(Flag2StringValue, out result).ShouldBeEquivalentTo(true);
			result.ShouldBeEquivalentTo((TestEnum)Enum.Parse(typeof(TestEnum), Flag2StringValue));
		}

		[TestMethod, EnumTest, SuppressMessage("ReSharper", "ExceptionNotDocumented")]
		public void TestInt32ParseMultipleValues()
		{			
			Enums.Parse<TestEnum>($"{Flag1}, {Flag2}").ShouldBeEquivalentTo((TestEnum)Enum.Parse(typeof(TestEnum), $"{Flag1}, {Flag2}"));
            Enums.Parse<TestEnum>($"{Flag2}, {Flag1}").ShouldBeEquivalentTo((TestEnum)Enum.Parse(typeof(TestEnum), $"{Flag2}, {Flag1}"));
		}

		[TestMethod, EnumTest]
		public void TestInt32ToEnum()
		{
			Enums.ToEnum<TestEnum>((int)0x000000000).ShouldBeEquivalentTo(None);
			Enums.ToEnum<TestEnum>((int)0x000008000).ShouldBeEquivalentTo(Flag1);
			Enums.ToEnum<TestEnum>((int)0x000008000 | 0x000010000).ShouldBeEquivalentTo(Flag1Flag2);
			Enums.ToEnum<TestEnum>((Object)0x000008000).ShouldBeEquivalentTo(Flag1);
			var enumTest1 = (int)0x000000000;
			var enumTest2 = (int)0x000008000;
			var enumTest3 = ((int)0x000008000 | 0x000010000);
			Enums.ToEnum<TestEnum>(enumTest1).ShouldBeEquivalentTo((TestEnum)Enum.ToObject(typeof(TestEnum), enumTest1));
			Enums.ToEnum<TestEnum>(enumTest2).ShouldBeEquivalentTo((TestEnum)Enum.ToObject(typeof(TestEnum), enumTest2));
			Enums.ToEnum<TestEnum>(enumTest3).ShouldBeEquivalentTo((TestEnum)Enum.ToObject(typeof(TestEnum), enumTest3));
		}

		[TestMethod, EnumTest]
		public void TestInt32ToAsObject()
		{
			None.AsObject().ShouldBeEquivalentTo(None);
			Flag1.AsObject().ShouldBeEquivalentTo(Flag1);
			Flag1Flag2.AsObject().ShouldBeEquivalentTo((Flag1 | Flag2));
			var objResult = Enums.AsObject<TestEnum>((int)(0x000008000 | 0x000010000)) as TestEnum? ?? TestEnum.Ten;
			objResult.ShouldBeEquivalentTo(Flag1 | Flag2);
        }
	}
	
	[TestClass]
	public class TestFlagsUInt32EnumEnumUnderlyingKind
	{
		[Flags]
		private enum TestEnum : uint	
		{ 
			All = unchecked((uint)~0),			
			Zero = 0,
			One = 0x000008000,
			Two = 0x000010000,
			Too = 0x000020000,
			Eight = 0x000040000,
			Ten = 0x000080000,
						
		}

		private const TestEnum None            = TestEnum.Zero,
							   Flag1           = TestEnum.One, 
							   Flag2           = TestEnum.Two,
							   Flag4           = TestEnum.Too,
							   Flag8           = TestEnum.Eight,
							   Flag10          = TestEnum.Ten,
							   Flag1Flag2      = TestEnum.One | TestEnum.Two,
							   Flag1Flag2Flag4 = TestEnum.One | TestEnum.Two | TestEnum.Too,
							   AllFlags        = TestEnum.One | TestEnum.Two | TestEnum.Too | TestEnum.Eight | TestEnum.Ten;
		private const string Flag1StringValue = "One";
		private const string Flag1StringValueLowerCase = "one";
		private const string Flag2StringValue = "Two";		
		private const string Flag2Flag10StringValue = "Two, Ten";
		private const string Flag2Flag10StringValueLowerCase = "two, ten";
		
		[TestMethod, EnumTest]
		public void TestAllDefinedFlags()
		{
			var allFlags = TestEnum.Zero.AddAllDefinedFlags();
			var asNumeric = (uint)allFlags;
			allFlags.ShouldBeEquivalentTo(TestEnum.One | TestEnum.Two | TestEnum.Too | TestEnum.Eight | TestEnum.Ten);
			TestEnum.Zero.AddAllDefinedFlags().Should().NotBe(TestEnum.All);

		}

		[TestMethod, EnumTest]
        public void TestUInt32AsString()
        {
            var flag1NativeToString = Flag1.ToString();
            var flag2NativeToString = Flag2.ToString();
			Flag1.AsString().ShouldBeEquivalentTo(flag1NativeToString);
			Flag2.AsString().ShouldBeEquivalentTo(flag2NativeToString);
			AllFlags.AsString().ShouldBeEquivalentTo(AllFlags.ToString());
			(Flag2 | Flag10).ShouldBeEquivalentTo(Flag2Flag10StringValue);
			(TestEnum.Zero | Flag1).AsString().ShouldBeEquivalentTo((TestEnum.Zero | Flag1).ToString());			
		}

		[TestMethod, EnumTest]
        public void TestUInt32RemoveFlag()
		{
            Flag1Flag2.RemoveFlag(Flag1).ShouldBeEquivalentTo(Flag2);
			Flag1Flag2.RemoveFlag(Flag2).ShouldBeEquivalentTo(Flag1);
			Flag1Flag2.RemoveFlag(None).ShouldBeEquivalentTo(Flag1Flag2);
		}

		[TestMethod, EnumTest]
        public void TestUInt32RemoveFlagIf()
		{
			Flag1Flag2.RemoveFlagIf(Flag2, false).ShouldBeEquivalentTo(Flag1Flag2);
			Flag1Flag2.RemoveFlagIf(Flag1, true).ShouldBeEquivalentTo(Flag2);
			Flag1Flag2.RemoveFlagIf(Flag2, () => false).ShouldBeEquivalentTo(Flag1Flag2);
			Flag1Flag2.RemoveFlagIf(Flag2, () => true).ShouldBeEquivalentTo(Flag1);
			Flag1Flag2.RemoveFlagIf(Flag2, s => s == TestEnum.One).ShouldBeEquivalentTo(Flag1Flag2); // false
			Flag1Flag2.RemoveFlagIf(Flag2, s => s.IsFlagSet(TestEnum.One)).ShouldBeEquivalentTo(Flag1); // true
		}

		[TestMethod, EnumTest]
        public void TestUInt32ModifyFlag()
		{
			Flag1Flag2.ModifyFlag(Flag4, false).ShouldBeEquivalentTo(Flag1Flag2);
			Flag1Flag2.ModifyFlag(Flag2, false).ShouldBeEquivalentTo(Flag1);
			Flag1Flag2.ModifyFlag(Flag4, true).ShouldBeEquivalentTo(Flag1Flag2Flag4);
			Flag1Flag2.ModifyFlag(Flag4, () => true).ShouldBeEquivalentTo(Flag1Flag2Flag4);
			Flag1Flag2.ModifyFlag(Flag4, () => false).ShouldBeEquivalentTo(Flag1Flag2);
			Flag1Flag2.ModifyFlag(Flag4, s => s.IsFlagSet(Flag1)).ShouldBeEquivalentTo(Flag1Flag2Flag4);
			Flag1Flag2.ModifyFlag(Flag4, s => !s.IsFlagSet(Flag1)).ShouldBeEquivalentTo(Flag1Flag2);
		}

		[TestMethod, EnumTest]
        public void TestUInt32ToList()
		{
            var result = Flag1Flag2.ToList();
			result[0].ShouldBeEquivalentTo(Flag1);
			result[1].ShouldBeEquivalentTo(Flag2);
			result.Count.ShouldBeEquivalentTo(2);
		}

		[TestMethod, EnumTest]
        public void TestUInt32AreAllFlagsSet()
		{
			Flag1Flag2.AreAllFlagsSet(Flag1, Flag2).Should().BeTrue();
			Flag1Flag2.AreAllFlagsSet(Flag1, Flag2, Flag4).Should().BeFalse();
			None.AreAllFlagsSet(Flag1, Flag2).Should().BeFalse();
			None.AreAllFlagsSet(None).Should().BeTrue();
		}

		[TestMethod, EnumTest]
        public void TestUInt32AreAnyFlagsSet()
		{
            Flag1Flag2.AreAnyFlagsSet(Flag1).Should().BeTrue();
			Flag1Flag2.AreAnyFlagsSet(Flag4).Should().BeFalse();
			Flag1Flag2.AreAnyFlagsSet(Flag1, Flag4).Should().BeTrue();
			Flag1Flag2.AreAnyFlagsSet(None, Flag1).Should().BeTrue();
			None.AreAnyFlagsSet(None, Flag1).Should().BeTrue();
			None.AreAnyFlagsSet(Flag1, Flag2).Should().BeFalse();
		}

		[TestMethod, EnumTest]
        public void TestUInt32EqualsAny()
		{
            Flag1Flag2.EqualsAny(Flag1).Should().BeFalse();
			Flag1.EqualsAny(Flag1, Flag2, Flag4).Should().BeTrue();
			Flag1.EqualsAny(Flag2, Flag4).Should().BeFalse();
		}

		[TestMethod, EnumTest]
        public void TestUInt32AddFlag()
        {
			None.AddFlag(Flag1).ShouldBeEquivalentTo(Flag1);
            Flag1.AddFlag(Flag2).ShouldBeEquivalentTo(Flag1Flag2);
			Flag1.AddFlag(None).ShouldBeEquivalentTo(Flag1);
			Flag1.AddFlag(Flag1).ShouldBeEquivalentTo(Flag1);
			Flag1Flag2.AddFlag(Flag1Flag2).ShouldBeEquivalentTo(Flag1Flag2);
		}

		[TestMethod, EnumTest]
        public void TestUInt32AddFlagIf()
        {
			None.AddFlagIf(Flag1, true).ShouldBeEquivalentTo(Flag1);
			
			Flag1.AddFlagIf(Flag2, false).ShouldBeEquivalentTo(Flag1);
			Flag2.AddFlagIf(Flag1, true).ShouldBeEquivalentTo(Flag1Flag2);
			Flag2.AddFlagIf(Flag1, () => true).ShouldBeEquivalentTo(Flag1Flag2);
			Flag1.AddFlagIf(Flag2, () => false).ShouldBeEquivalentTo(Flag1);
			Flag2.AddFlagIf(Flag1, s => TestEnum.Two == s).ShouldBeEquivalentTo(Flag1Flag2);
			Flag1.AddFlagIf(Flag2, s => TestEnum.One != s).ShouldBeEquivalentTo(Flag1);
		}

		[TestMethod, EnumTest]
		public void TestUInt32AddFlags()
		{
			None.AddFlags(Flag1, Flag2).ShouldBeEquivalentTo(Flag1Flag2);			
			Flag1Flag2.AddFlags(Flag1, Flag2).ShouldBeEquivalentTo(Flag1Flag2);
			Flag1Flag2.AddFlags(None).ShouldBeEquivalentTo(Flag1Flag2);
			var result = Flag1.AddFlags(Flag2, Flag4, Flag8, Flag10);
            result.ShouldBeEquivalentTo(AllFlags);
		}

		[TestMethod, EnumTest]
		public void TestUInt32RemoveFlags()
		{
			None.RemoveFlags(Flag1, Flag2).ShouldBeEquivalentTo(None);
            AllFlags.RemoveFlags(Flag1, Flag2, Flag4, Flag8).ShouldBeEquivalentTo(Flag10);
		}
		
		[TestMethod, EnumTest]
		public void TestUInt32IsFlagSet()
		{
			None.IsFlagSet(Flag1).ShouldBeEquivalentTo(None.HasFlag(Flag1));
			None.IsFlagSet(None).ShouldBeEquivalentTo(None.HasFlag(None));
			Flag1Flag2.IsFlagSet(Flag1).Should().BeTrue();
            Flag1Flag2.IsFlagSet(Flag4).Should().BeFalse();
		}

		[TestMethod, EnumTest]
		public void TestUInt32TryParseBadValue()
		{
			TestEnum result;
			Enums.TryParse("foo", out result).ShouldBeEquivalentTo(false);
			Enums.TryParse("One, foo", out result).ShouldBeEquivalentTo(false); 
		}
		
		[TestMethod, EnumTest, SuppressMessage("ReSharper", "ExceptionNotDocumented")]
		public void TestUInt32ParseOneValue()
		{				
			Enums.Parse<TestEnum>(Flag1StringValue).ShouldBeEquivalentTo((TestEnum)Enum.Parse(typeof(TestEnum), Flag1StringValue));
            Enums.Parse<TestEnum>(Flag2StringValue).ShouldBeEquivalentTo((TestEnum)Enum.Parse(typeof(TestEnum), Flag2StringValue)); 			           
		}

		[TestMethod, EnumTest, SuppressMessage("ReSharper", "ExceptionNotDocumented")]
		public void TestUInt32ParseCaseInsensitiveValue()
		{				
			Enums.Parse<TestEnum>(Flag2Flag10StringValueLowerCase, true).ShouldBeEquivalentTo((TestEnum)Enum.Parse(typeof(TestEnum), Flag2Flag10StringValueLowerCase, true));
            Enums.Parse<TestEnum>(Flag1StringValueLowerCase, true).ShouldBeEquivalentTo((TestEnum)Enum.Parse(typeof(TestEnum), Flag1StringValueLowerCase, true)); 			           
		}

		[TestMethod, EnumTest, SuppressMessage("ReSharper", "ExceptionNotDocumented")]
		public void TestUInt32TryParseOneValue()
		{
			TestEnum result;	
			Enums.TryParse(Flag1StringValue, out result).ShouldBeEquivalentTo(true);
			result.ShouldBeEquivalentTo((TestEnum)Enum.Parse(typeof(TestEnum), Flag1StringValue));
            Enums.TryParse(Flag2StringValue, out result).ShouldBeEquivalentTo(true);
			result.ShouldBeEquivalentTo((TestEnum)Enum.Parse(typeof(TestEnum), Flag2StringValue));
		}

		[TestMethod, EnumTest, SuppressMessage("ReSharper", "ExceptionNotDocumented")]
		public void TestUInt32ParseMultipleValues()
		{			
			Enums.Parse<TestEnum>($"{Flag1}, {Flag2}").ShouldBeEquivalentTo((TestEnum)Enum.Parse(typeof(TestEnum), $"{Flag1}, {Flag2}"));
            Enums.Parse<TestEnum>($"{Flag2}, {Flag1}").ShouldBeEquivalentTo((TestEnum)Enum.Parse(typeof(TestEnum), $"{Flag2}, {Flag1}"));
		}

		[TestMethod, EnumTest]
		public void TestUInt32ToEnum()
		{
			Enums.ToEnum<TestEnum>((uint)0x000000000).ShouldBeEquivalentTo(None);
			Enums.ToEnum<TestEnum>((uint)0x000008000).ShouldBeEquivalentTo(Flag1);
			Enums.ToEnum<TestEnum>((uint)0x000008000 | 0x000010000).ShouldBeEquivalentTo(Flag1Flag2);
			Enums.ToEnum<TestEnum>((Object)0x000008000).ShouldBeEquivalentTo(Flag1);
			var enumTest1 = (uint)0x000000000;
			var enumTest2 = (uint)0x000008000;
			var enumTest3 = ((uint)0x000008000 | 0x000010000);
			Enums.ToEnum<TestEnum>(enumTest1).ShouldBeEquivalentTo((TestEnum)Enum.ToObject(typeof(TestEnum), enumTest1));
			Enums.ToEnum<TestEnum>(enumTest2).ShouldBeEquivalentTo((TestEnum)Enum.ToObject(typeof(TestEnum), enumTest2));
			Enums.ToEnum<TestEnum>(enumTest3).ShouldBeEquivalentTo((TestEnum)Enum.ToObject(typeof(TestEnum), enumTest3));
		}

		[TestMethod, EnumTest]
		public void TestUInt32ToAsObject()
		{
			None.AsObject().ShouldBeEquivalentTo(None);
			Flag1.AsObject().ShouldBeEquivalentTo(Flag1);
			Flag1Flag2.AsObject().ShouldBeEquivalentTo((Flag1 | Flag2));
			var objResult = Enums.AsObject<TestEnum>((uint)(0x000008000 | 0x000010000)) as TestEnum? ?? TestEnum.Ten;
			objResult.ShouldBeEquivalentTo(Flag1 | Flag2);
        }
	}
	
	[TestClass]
	public class TestFlagsInt64EnumEnumUnderlyingKind
	{
		[Flags]
		private enum TestEnum : long	
		{ 
			All = unchecked((long)~0),
			Invalid = -1,			
			Zero = 0,
			One = 0x20000000000,
			Two = 0x40000000000,
			Too = 0x80000000000,
			Eight = 0x100000000000,
			Ten = 0x200000000000,
			TenAndTwelve = 0x600000000000,			
		}

		private const TestEnum None            = TestEnum.Zero,
							   Flag1           = TestEnum.One, 
							   Flag2           = TestEnum.Two,
							   Flag4           = TestEnum.Too,
							   Flag8           = TestEnum.Eight,
							   Flag10          = TestEnum.Ten,
							   Flag1Flag2      = TestEnum.One | TestEnum.Two,
							   Flag1Flag2Flag4 = TestEnum.One | TestEnum.Two | TestEnum.Too,
							   AllFlags        = TestEnum.One | TestEnum.Two | TestEnum.Too | TestEnum.Eight | TestEnum.Ten;
		private const string Flag1StringValue = "One";
		private const string Flag1StringValueLowerCase = "one";
		private const string Flag2StringValue = "Two";		
		private const string Flag2Flag10StringValue = "Two, Ten";
		private const string Flag2Flag10StringValueLowerCase = "two, ten";
		
		[TestMethod, EnumTest]
		public void TestAllDefinedFlags()
		{
			var allFlags = TestEnum.Zero.AddAllDefinedFlags();
			var asNumeric = (long)allFlags;
			allFlags.ShouldBeEquivalentTo(TestEnum.One | TestEnum.Two | TestEnum.Too | TestEnum.Eight | TestEnum.Ten);
			TestEnum.Zero.AddAllDefinedFlags().Should().NotBe(TestEnum.All);

		}

		[TestMethod, EnumTest]
        public void TestInt64AsString()
        {
            var flag1NativeToString = Flag1.ToString();
            var flag2NativeToString = Flag2.ToString();
			Flag1.AsString().ShouldBeEquivalentTo(flag1NativeToString);
			Flag2.AsString().ShouldBeEquivalentTo(flag2NativeToString);
			AllFlags.AsString().ShouldBeEquivalentTo(AllFlags.ToString());
			(Flag2 | Flag10).ShouldBeEquivalentTo(Flag2Flag10StringValue);
			(TestEnum.Zero | Flag1).AsString().ShouldBeEquivalentTo((TestEnum.Zero | Flag1).ToString());			
		}

		[TestMethod, EnumTest]
        public void TestInt64RemoveFlag()
		{
            Flag1Flag2.RemoveFlag(Flag1).ShouldBeEquivalentTo(Flag2);
			Flag1Flag2.RemoveFlag(Flag2).ShouldBeEquivalentTo(Flag1);
			Flag1Flag2.RemoveFlag(None).ShouldBeEquivalentTo(Flag1Flag2);
		}

		[TestMethod, EnumTest]
        public void TestInt64RemoveFlagIf()
		{
			Flag1Flag2.RemoveFlagIf(Flag2, false).ShouldBeEquivalentTo(Flag1Flag2);
			Flag1Flag2.RemoveFlagIf(Flag1, true).ShouldBeEquivalentTo(Flag2);
			Flag1Flag2.RemoveFlagIf(Flag2, () => false).ShouldBeEquivalentTo(Flag1Flag2);
			Flag1Flag2.RemoveFlagIf(Flag2, () => true).ShouldBeEquivalentTo(Flag1);
			Flag1Flag2.RemoveFlagIf(Flag2, s => s == TestEnum.One).ShouldBeEquivalentTo(Flag1Flag2); // false
			Flag1Flag2.RemoveFlagIf(Flag2, s => s.IsFlagSet(TestEnum.One)).ShouldBeEquivalentTo(Flag1); // true
		}

		[TestMethod, EnumTest]
        public void TestInt64ModifyFlag()
		{
			Flag1Flag2.ModifyFlag(Flag4, false).ShouldBeEquivalentTo(Flag1Flag2);
			Flag1Flag2.ModifyFlag(Flag2, false).ShouldBeEquivalentTo(Flag1);
			Flag1Flag2.ModifyFlag(Flag4, true).ShouldBeEquivalentTo(Flag1Flag2Flag4);
			Flag1Flag2.ModifyFlag(Flag4, () => true).ShouldBeEquivalentTo(Flag1Flag2Flag4);
			Flag1Flag2.ModifyFlag(Flag4, () => false).ShouldBeEquivalentTo(Flag1Flag2);
			Flag1Flag2.ModifyFlag(Flag4, s => s.IsFlagSet(Flag1)).ShouldBeEquivalentTo(Flag1Flag2Flag4);
			Flag1Flag2.ModifyFlag(Flag4, s => !s.IsFlagSet(Flag1)).ShouldBeEquivalentTo(Flag1Flag2);
		}

		[TestMethod, EnumTest]
        public void TestInt64ToList()
		{
            var result = Flag1Flag2.ToList();
			result[0].ShouldBeEquivalentTo(Flag1);
			result[1].ShouldBeEquivalentTo(Flag2);
			result.Count.ShouldBeEquivalentTo(2);
		}

		[TestMethod, EnumTest]
        public void TestInt64AreAllFlagsSet()
		{
			Flag1Flag2.AreAllFlagsSet(Flag1, Flag2).Should().BeTrue();
			Flag1Flag2.AreAllFlagsSet(Flag1, Flag2, Flag4).Should().BeFalse();
			None.AreAllFlagsSet(Flag1, Flag2).Should().BeFalse();
			None.AreAllFlagsSet(None).Should().BeTrue();
		}

		[TestMethod, EnumTest]
        public void TestInt64AreAnyFlagsSet()
		{
            Flag1Flag2.AreAnyFlagsSet(Flag1).Should().BeTrue();
			Flag1Flag2.AreAnyFlagsSet(Flag4).Should().BeFalse();
			Flag1Flag2.AreAnyFlagsSet(Flag1, Flag4).Should().BeTrue();
			Flag1Flag2.AreAnyFlagsSet(None, Flag1).Should().BeTrue();
			None.AreAnyFlagsSet(None, Flag1).Should().BeTrue();
			None.AreAnyFlagsSet(Flag1, Flag2).Should().BeFalse();
		}

		[TestMethod, EnumTest]
        public void TestInt64EqualsAny()
		{
            Flag1Flag2.EqualsAny(Flag1).Should().BeFalse();
			Flag1.EqualsAny(Flag1, Flag2, Flag4).Should().BeTrue();
			Flag1.EqualsAny(Flag2, Flag4).Should().BeFalse();
		}

		[TestMethod, EnumTest]
        public void TestInt64AddFlag()
        {
			None.AddFlag(Flag1).ShouldBeEquivalentTo(Flag1);
            Flag1.AddFlag(Flag2).ShouldBeEquivalentTo(Flag1Flag2);
			Flag1.AddFlag(None).ShouldBeEquivalentTo(Flag1);
			Flag1.AddFlag(Flag1).ShouldBeEquivalentTo(Flag1);
			Flag1Flag2.AddFlag(Flag1Flag2).ShouldBeEquivalentTo(Flag1Flag2);
		}

		[TestMethod, EnumTest]
        public void TestInt64AddFlagIf()
        {
			None.AddFlagIf(Flag1, true).ShouldBeEquivalentTo(Flag1);
			
			Flag1.AddFlagIf(Flag2, false).ShouldBeEquivalentTo(Flag1);
			Flag2.AddFlagIf(Flag1, true).ShouldBeEquivalentTo(Flag1Flag2);
			Flag2.AddFlagIf(Flag1, () => true).ShouldBeEquivalentTo(Flag1Flag2);
			Flag1.AddFlagIf(Flag2, () => false).ShouldBeEquivalentTo(Flag1);
			Flag2.AddFlagIf(Flag1, s => TestEnum.Two == s).ShouldBeEquivalentTo(Flag1Flag2);
			Flag1.AddFlagIf(Flag2, s => TestEnum.One != s).ShouldBeEquivalentTo(Flag1);
		}

		[TestMethod, EnumTest]
		public void TestInt64AddFlags()
		{
			None.AddFlags(Flag1, Flag2).ShouldBeEquivalentTo(Flag1Flag2);			
			Flag1Flag2.AddFlags(Flag1, Flag2).ShouldBeEquivalentTo(Flag1Flag2);
			Flag1Flag2.AddFlags(None).ShouldBeEquivalentTo(Flag1Flag2);
			var result = Flag1.AddFlags(Flag2, Flag4, Flag8, Flag10);
            result.ShouldBeEquivalentTo(AllFlags);
		}

		[TestMethod, EnumTest]
		public void TestInt64RemoveFlags()
		{
			None.RemoveFlags(Flag1, Flag2).ShouldBeEquivalentTo(None);
            AllFlags.RemoveFlags(Flag1, Flag2, Flag4, Flag8).ShouldBeEquivalentTo(Flag10);
		}
		
		[TestMethod, EnumTest]
		public void TestInt64IsFlagSet()
		{
			None.IsFlagSet(Flag1).ShouldBeEquivalentTo(None.HasFlag(Flag1));
			None.IsFlagSet(None).ShouldBeEquivalentTo(None.HasFlag(None));
			Flag1Flag2.IsFlagSet(Flag1).Should().BeTrue();
            Flag1Flag2.IsFlagSet(Flag4).Should().BeFalse();
		}

		[TestMethod, EnumTest]
		public void TestInt64TryParseBadValue()
		{
			TestEnum result;
			Enums.TryParse("foo", out result).ShouldBeEquivalentTo(false);
			Enums.TryParse("One, foo", out result).ShouldBeEquivalentTo(false); 
		}
		
		[TestMethod, EnumTest, SuppressMessage("ReSharper", "ExceptionNotDocumented")]
		public void TestInt64ParseOneValue()
		{				
			Enums.Parse<TestEnum>(Flag1StringValue).ShouldBeEquivalentTo((TestEnum)Enum.Parse(typeof(TestEnum), Flag1StringValue));
            Enums.Parse<TestEnum>(Flag2StringValue).ShouldBeEquivalentTo((TestEnum)Enum.Parse(typeof(TestEnum), Flag2StringValue)); 			           
		}

		[TestMethod, EnumTest, SuppressMessage("ReSharper", "ExceptionNotDocumented")]
		public void TestInt64ParseCaseInsensitiveValue()
		{				
			Enums.Parse<TestEnum>(Flag2Flag10StringValueLowerCase, true).ShouldBeEquivalentTo((TestEnum)Enum.Parse(typeof(TestEnum), Flag2Flag10StringValueLowerCase, true));
            Enums.Parse<TestEnum>(Flag1StringValueLowerCase, true).ShouldBeEquivalentTo((TestEnum)Enum.Parse(typeof(TestEnum), Flag1StringValueLowerCase, true)); 			           
		}

		[TestMethod, EnumTest, SuppressMessage("ReSharper", "ExceptionNotDocumented")]
		public void TestInt64TryParseOneValue()
		{
			TestEnum result;	
			Enums.TryParse(Flag1StringValue, out result).ShouldBeEquivalentTo(true);
			result.ShouldBeEquivalentTo((TestEnum)Enum.Parse(typeof(TestEnum), Flag1StringValue));
            Enums.TryParse(Flag2StringValue, out result).ShouldBeEquivalentTo(true);
			result.ShouldBeEquivalentTo((TestEnum)Enum.Parse(typeof(TestEnum), Flag2StringValue));
		}

		[TestMethod, EnumTest, SuppressMessage("ReSharper", "ExceptionNotDocumented")]
		public void TestInt64ParseMultipleValues()
		{			
			Enums.Parse<TestEnum>($"{Flag1}, {Flag2}").ShouldBeEquivalentTo((TestEnum)Enum.Parse(typeof(TestEnum), $"{Flag1}, {Flag2}"));
            Enums.Parse<TestEnum>($"{Flag2}, {Flag1}").ShouldBeEquivalentTo((TestEnum)Enum.Parse(typeof(TestEnum), $"{Flag2}, {Flag1}"));
		}

		[TestMethod, EnumTest]
		public void TestInt64ToEnum()
		{
			Enums.ToEnum<TestEnum>((long)0x000000000).ShouldBeEquivalentTo(None);
			Enums.ToEnum<TestEnum>((long)0x20000000000).ShouldBeEquivalentTo(Flag1);
			Enums.ToEnum<TestEnum>((long)0x20000000000 | 0x40000000000).ShouldBeEquivalentTo(Flag1Flag2);
			Enums.ToEnum<TestEnum>((Object)0x20000000000).ShouldBeEquivalentTo(Flag1);
			var enumTest1 = (long)0x000000000;
			var enumTest2 = (long)0x20000000000;
			var enumTest3 = ((long)0x20000000000 | 0x40000000000);
			Enums.ToEnum<TestEnum>(enumTest1).ShouldBeEquivalentTo((TestEnum)Enum.ToObject(typeof(TestEnum), enumTest1));
			Enums.ToEnum<TestEnum>(enumTest2).ShouldBeEquivalentTo((TestEnum)Enum.ToObject(typeof(TestEnum), enumTest2));
			Enums.ToEnum<TestEnum>(enumTest3).ShouldBeEquivalentTo((TestEnum)Enum.ToObject(typeof(TestEnum), enumTest3));
		}

		[TestMethod, EnumTest]
		public void TestInt64ToAsObject()
		{
			None.AsObject().ShouldBeEquivalentTo(None);
			Flag1.AsObject().ShouldBeEquivalentTo(Flag1);
			Flag1Flag2.AsObject().ShouldBeEquivalentTo((Flag1 | Flag2));
			var objResult = Enums.AsObject<TestEnum>((long)(0x20000000000 | 0x40000000000)) as TestEnum? ?? TestEnum.Ten;
			objResult.ShouldBeEquivalentTo(Flag1 | Flag2);
        }
	}
	
	[TestClass]
	public class TestFlagsUInt64EnumEnumUnderlyingKind
	{
		[Flags]
		private enum TestEnum : ulong	
		{ 
			All = unchecked((ulong)~0),			
			Zero = 0,
			One = 0x400000000000000,
			Two = 0x800000000000000,
			Too = 0x1000000000000000,
			Eight = 0x2000000000000000,
			Ten = 0x4000000000000000,
						
		}

		private const TestEnum None            = TestEnum.Zero,
							   Flag1           = TestEnum.One, 
							   Flag2           = TestEnum.Two,
							   Flag4           = TestEnum.Too,
							   Flag8           = TestEnum.Eight,
							   Flag10          = TestEnum.Ten,
							   Flag1Flag2      = TestEnum.One | TestEnum.Two,
							   Flag1Flag2Flag4 = TestEnum.One | TestEnum.Two | TestEnum.Too,
							   AllFlags        = TestEnum.One | TestEnum.Two | TestEnum.Too | TestEnum.Eight | TestEnum.Ten;
		private const string Flag1StringValue = "One";
		private const string Flag1StringValueLowerCase = "one";
		private const string Flag2StringValue = "Two";		
		private const string Flag2Flag10StringValue = "Two, Ten";
		private const string Flag2Flag10StringValueLowerCase = "two, ten";
		
		[TestMethod, EnumTest]
		public void TestAllDefinedFlags()
		{
			var allFlags = TestEnum.Zero.AddAllDefinedFlags();
			var asNumeric = (ulong)allFlags;
			allFlags.ShouldBeEquivalentTo(TestEnum.One | TestEnum.Two | TestEnum.Too | TestEnum.Eight | TestEnum.Ten);
			TestEnum.Zero.AddAllDefinedFlags().Should().NotBe(TestEnum.All);

		}

		[TestMethod, EnumTest]
        public void TestUInt64AsString()
        {
            var flag1NativeToString = Flag1.ToString();
            var flag2NativeToString = Flag2.ToString();
			Flag1.AsString().ShouldBeEquivalentTo(flag1NativeToString);
			Flag2.AsString().ShouldBeEquivalentTo(flag2NativeToString);
			AllFlags.AsString().ShouldBeEquivalentTo(AllFlags.ToString());
			(Flag2 | Flag10).ShouldBeEquivalentTo(Flag2Flag10StringValue);
			(TestEnum.Zero | Flag1).AsString().ShouldBeEquivalentTo((TestEnum.Zero | Flag1).ToString());			
		}

		[TestMethod, EnumTest]
        public void TestUInt64RemoveFlag()
		{
            Flag1Flag2.RemoveFlag(Flag1).ShouldBeEquivalentTo(Flag2);
			Flag1Flag2.RemoveFlag(Flag2).ShouldBeEquivalentTo(Flag1);
			Flag1Flag2.RemoveFlag(None).ShouldBeEquivalentTo(Flag1Flag2);
		}

		[TestMethod, EnumTest]
        public void TestUInt64RemoveFlagIf()
		{
			Flag1Flag2.RemoveFlagIf(Flag2, false).ShouldBeEquivalentTo(Flag1Flag2);
			Flag1Flag2.RemoveFlagIf(Flag1, true).ShouldBeEquivalentTo(Flag2);
			Flag1Flag2.RemoveFlagIf(Flag2, () => false).ShouldBeEquivalentTo(Flag1Flag2);
			Flag1Flag2.RemoveFlagIf(Flag2, () => true).ShouldBeEquivalentTo(Flag1);
			Flag1Flag2.RemoveFlagIf(Flag2, s => s == TestEnum.One).ShouldBeEquivalentTo(Flag1Flag2); // false
			Flag1Flag2.RemoveFlagIf(Flag2, s => s.IsFlagSet(TestEnum.One)).ShouldBeEquivalentTo(Flag1); // true
		}

		[TestMethod, EnumTest]
        public void TestUInt64ModifyFlag()
		{
			Flag1Flag2.ModifyFlag(Flag4, false).ShouldBeEquivalentTo(Flag1Flag2);
			Flag1Flag2.ModifyFlag(Flag2, false).ShouldBeEquivalentTo(Flag1);
			Flag1Flag2.ModifyFlag(Flag4, true).ShouldBeEquivalentTo(Flag1Flag2Flag4);
			Flag1Flag2.ModifyFlag(Flag4, () => true).ShouldBeEquivalentTo(Flag1Flag2Flag4);
			Flag1Flag2.ModifyFlag(Flag4, () => false).ShouldBeEquivalentTo(Flag1Flag2);
			Flag1Flag2.ModifyFlag(Flag4, s => s.IsFlagSet(Flag1)).ShouldBeEquivalentTo(Flag1Flag2Flag4);
			Flag1Flag2.ModifyFlag(Flag4, s => !s.IsFlagSet(Flag1)).ShouldBeEquivalentTo(Flag1Flag2);
		}

		[TestMethod, EnumTest]
        public void TestUInt64ToList()
		{
            var result = Flag1Flag2.ToList();
			result[0].ShouldBeEquivalentTo(Flag1);
			result[1].ShouldBeEquivalentTo(Flag2);
			result.Count.ShouldBeEquivalentTo(2);
		}

		[TestMethod, EnumTest]
        public void TestUInt64AreAllFlagsSet()
		{
			Flag1Flag2.AreAllFlagsSet(Flag1, Flag2).Should().BeTrue();
			Flag1Flag2.AreAllFlagsSet(Flag1, Flag2, Flag4).Should().BeFalse();
			None.AreAllFlagsSet(Flag1, Flag2).Should().BeFalse();
			None.AreAllFlagsSet(None).Should().BeTrue();
		}

		[TestMethod, EnumTest]
        public void TestUInt64AreAnyFlagsSet()
		{
            Flag1Flag2.AreAnyFlagsSet(Flag1).Should().BeTrue();
			Flag1Flag2.AreAnyFlagsSet(Flag4).Should().BeFalse();
			Flag1Flag2.AreAnyFlagsSet(Flag1, Flag4).Should().BeTrue();
			Flag1Flag2.AreAnyFlagsSet(None, Flag1).Should().BeTrue();
			None.AreAnyFlagsSet(None, Flag1).Should().BeTrue();
			None.AreAnyFlagsSet(Flag1, Flag2).Should().BeFalse();
		}

		[TestMethod, EnumTest]
        public void TestUInt64EqualsAny()
		{
            Flag1Flag2.EqualsAny(Flag1).Should().BeFalse();
			Flag1.EqualsAny(Flag1, Flag2, Flag4).Should().BeTrue();
			Flag1.EqualsAny(Flag2, Flag4).Should().BeFalse();
		}

		[TestMethod, EnumTest]
        public void TestUInt64AddFlag()
        {
			None.AddFlag(Flag1).ShouldBeEquivalentTo(Flag1);
            Flag1.AddFlag(Flag2).ShouldBeEquivalentTo(Flag1Flag2);
			Flag1.AddFlag(None).ShouldBeEquivalentTo(Flag1);
			Flag1.AddFlag(Flag1).ShouldBeEquivalentTo(Flag1);
			Flag1Flag2.AddFlag(Flag1Flag2).ShouldBeEquivalentTo(Flag1Flag2);
		}

		[TestMethod, EnumTest]
        public void TestUInt64AddFlagIf()
        {
			None.AddFlagIf(Flag1, true).ShouldBeEquivalentTo(Flag1);
			
			Flag1.AddFlagIf(Flag2, false).ShouldBeEquivalentTo(Flag1);
			Flag2.AddFlagIf(Flag1, true).ShouldBeEquivalentTo(Flag1Flag2);
			Flag2.AddFlagIf(Flag1, () => true).ShouldBeEquivalentTo(Flag1Flag2);
			Flag1.AddFlagIf(Flag2, () => false).ShouldBeEquivalentTo(Flag1);
			Flag2.AddFlagIf(Flag1, s => TestEnum.Two == s).ShouldBeEquivalentTo(Flag1Flag2);
			Flag1.AddFlagIf(Flag2, s => TestEnum.One != s).ShouldBeEquivalentTo(Flag1);
		}

		[TestMethod, EnumTest]
		public void TestUInt64AddFlags()
		{
			None.AddFlags(Flag1, Flag2).ShouldBeEquivalentTo(Flag1Flag2);			
			Flag1Flag2.AddFlags(Flag1, Flag2).ShouldBeEquivalentTo(Flag1Flag2);
			Flag1Flag2.AddFlags(None).ShouldBeEquivalentTo(Flag1Flag2);
			var result = Flag1.AddFlags(Flag2, Flag4, Flag8, Flag10);
            result.ShouldBeEquivalentTo(AllFlags);
		}

		[TestMethod, EnumTest]
		public void TestUInt64RemoveFlags()
		{
			None.RemoveFlags(Flag1, Flag2).ShouldBeEquivalentTo(None);
            AllFlags.RemoveFlags(Flag1, Flag2, Flag4, Flag8).ShouldBeEquivalentTo(Flag10);
		}
		
		[TestMethod, EnumTest]
		public void TestUInt64IsFlagSet()
		{
			None.IsFlagSet(Flag1).ShouldBeEquivalentTo(None.HasFlag(Flag1));
			None.IsFlagSet(None).ShouldBeEquivalentTo(None.HasFlag(None));
			Flag1Flag2.IsFlagSet(Flag1).Should().BeTrue();
            Flag1Flag2.IsFlagSet(Flag4).Should().BeFalse();
		}

		[TestMethod, EnumTest]
		public void TestUInt64TryParseBadValue()
		{
			TestEnum result;
			Enums.TryParse("foo", out result).ShouldBeEquivalentTo(false);
			Enums.TryParse("One, foo", out result).ShouldBeEquivalentTo(false); 
		}
		
		[TestMethod, EnumTest, SuppressMessage("ReSharper", "ExceptionNotDocumented")]
		public void TestUInt64ParseOneValue()
		{				
			Enums.Parse<TestEnum>(Flag1StringValue).ShouldBeEquivalentTo((TestEnum)Enum.Parse(typeof(TestEnum), Flag1StringValue));
            Enums.Parse<TestEnum>(Flag2StringValue).ShouldBeEquivalentTo((TestEnum)Enum.Parse(typeof(TestEnum), Flag2StringValue)); 			           
		}

		[TestMethod, EnumTest, SuppressMessage("ReSharper", "ExceptionNotDocumented")]
		public void TestUInt64ParseCaseInsensitiveValue()
		{				
			Enums.Parse<TestEnum>(Flag2Flag10StringValueLowerCase, true).ShouldBeEquivalentTo((TestEnum)Enum.Parse(typeof(TestEnum), Flag2Flag10StringValueLowerCase, true));
            Enums.Parse<TestEnum>(Flag1StringValueLowerCase, true).ShouldBeEquivalentTo((TestEnum)Enum.Parse(typeof(TestEnum), Flag1StringValueLowerCase, true)); 			           
		}

		[TestMethod, EnumTest, SuppressMessage("ReSharper", "ExceptionNotDocumented")]
		public void TestUInt64TryParseOneValue()
		{
			TestEnum result;	
			Enums.TryParse(Flag1StringValue, out result).ShouldBeEquivalentTo(true);
			result.ShouldBeEquivalentTo((TestEnum)Enum.Parse(typeof(TestEnum), Flag1StringValue));
            Enums.TryParse(Flag2StringValue, out result).ShouldBeEquivalentTo(true);
			result.ShouldBeEquivalentTo((TestEnum)Enum.Parse(typeof(TestEnum), Flag2StringValue));
		}

		[TestMethod, EnumTest, SuppressMessage("ReSharper", "ExceptionNotDocumented")]
		public void TestUInt64ParseMultipleValues()
		{			
			Enums.Parse<TestEnum>($"{Flag1}, {Flag2}").ShouldBeEquivalentTo((TestEnum)Enum.Parse(typeof(TestEnum), $"{Flag1}, {Flag2}"));
            Enums.Parse<TestEnum>($"{Flag2}, {Flag1}").ShouldBeEquivalentTo((TestEnum)Enum.Parse(typeof(TestEnum), $"{Flag2}, {Flag1}"));
		}

		[TestMethod, EnumTest]
		public void TestUInt64ToEnum()
		{
			Enums.ToEnum<TestEnum>((ulong)0x000000000).ShouldBeEquivalentTo(None);
			Enums.ToEnum<TestEnum>((ulong)0x400000000000000).ShouldBeEquivalentTo(Flag1);
			Enums.ToEnum<TestEnum>((ulong)0x400000000000000 | 0x800000000000000).ShouldBeEquivalentTo(Flag1Flag2);
			Enums.ToEnum<TestEnum>((Object)0x400000000000000).ShouldBeEquivalentTo(Flag1);
			var enumTest1 = (ulong)0x000000000;
			var enumTest2 = (ulong)0x400000000000000;
			var enumTest3 = ((ulong)0x400000000000000 | 0x800000000000000);
			Enums.ToEnum<TestEnum>(enumTest1).ShouldBeEquivalentTo((TestEnum)Enum.ToObject(typeof(TestEnum), enumTest1));
			Enums.ToEnum<TestEnum>(enumTest2).ShouldBeEquivalentTo((TestEnum)Enum.ToObject(typeof(TestEnum), enumTest2));
			Enums.ToEnum<TestEnum>(enumTest3).ShouldBeEquivalentTo((TestEnum)Enum.ToObject(typeof(TestEnum), enumTest3));
		}

		[TestMethod, EnumTest]
		public void TestUInt64ToAsObject()
		{
			None.AsObject().ShouldBeEquivalentTo(None);
			Flag1.AsObject().ShouldBeEquivalentTo(Flag1);
			Flag1Flag2.AsObject().ShouldBeEquivalentTo((Flag1 | Flag2));
			var objResult = Enums.AsObject<TestEnum>((ulong)(0x400000000000000 | 0x800000000000000)) as TestEnum? ?? TestEnum.Ten;
			objResult.ShouldBeEquivalentTo(Flag1 | Flag2);
        }
	}
	}
}
