using System;
using System.Threading;
using System.Threading.Tasks;
using Diagonactic;
using EnumCppTests.Attributes;
using FluentAssertions;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace EnumCppTests
{
    enum LongEnum : long { One = 0x20000000000, Two = 0x40000000000, Four = 0x80000000000, Eight = 0x100000000000, Ten = 0x200000000000 }
    enum IntEnum : int { One = 0x2000000, Two = 0x4000000, Four = 0x8000000, Eight = 0x10000000, Ten = 0x20000000 }
    [TestClass]
    public class UnderlyingKindTests
    {
        private InterlockedEnum<LongEnum> m_longEnum = new InterlockedEnum<LongEnum>(LongEnum.One);

        [TestMethod, EnumTest]
        public void InterlockedTest()
        {
            // This is a very poor quality test
            Thread t1 = new Thread(() =>
            {
                m_longEnum.Value = LongEnum.Ten;
                Thread.Sleep(500);
                m_longEnum.Value.ShouldBeEquivalentTo(LongEnum.Eight);
            });
            Thread t2 = new Thread(() =>
            {
                Thread.Sleep(250);
                m_longEnum.Value = LongEnum.Eight;
            });
            t1.Start();
            t2.Start();
            t2.Join();
        }
    }
}
