using System;
using EnumCppTests.Attributes;
using FluentAssertions;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace EnumCppTests
{
    [TestClass]
    public class DelegateTests
    {
        private static event Action TestEvent;
        [TestMethod, DelegateTest]
        public void TestDelegateExtensions()
        {
            Action a = () => {};
            Action b = () => {int i = 0;};
            TestEvent += a;
            TestEvent += b;
            var list = TestEvent.GetInvokationsAsArray();
            list.Length.ShouldBeEquivalentTo(2);

            Action c = () => {int k = 1;};
            Action d = TestEvent.CombineDelegates(c);
            d.GetInvokationsAsArray().Length.ShouldBeEquivalentTo(3);

            d.RemoveDelegate(c).GetInvokationsAsArray().Length.ShouldBeEquivalentTo(2);
        }
    }
}
