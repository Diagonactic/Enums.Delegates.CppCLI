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
#pragma warning disable S1481, CS0219 // Unused local variables should be removed
            Action b = () => {int i = 0;};
#pragma warning restore S1481, CS0219 // Unused local variables should be removed
            TestEvent += a;
            TestEvent += b;
            /*var list = TestEvent.GetInvokationsAsArray();
            list.Length.ShouldBeEquivalentTo(2);

#pragma warning disable S1481, CS0219 // Variable is assigned but its value is never used
            Action c = () => {int k = 1;};
#pragma warning restore S1481, CS0219 // Variable is assigned but its value is never used
            Action d = TestEvent.CombineDelegates(c);
            d.GetInvokationsAsArray().Length.ShouldBeEquivalentTo(3);

            d.RemoveDelegate(c).GetInvokationsAsArray().Length.ShouldBeEquivalentTo(2);*/
        }

        public event EventHandler<EventArgs> TestEventArgs;
        
        [TestMethod, DelegateTest]
        public void TestFireOnce()
        {
            int ea = 0;
            EventHandler<EventArgs> eventWithArgs = (sender, args) => ea++;

            Delegates.AttachWithUnsubscribe(this, nameof(DelegateTests.TestEventArgs), eventWithArgs);

            TestEventArgs?.Invoke(this, null);
            TestEventArgs?.Invoke(this, null);
            TestEventArgs?.Invoke(this, null);

            ea.ShouldBeEquivalentTo(1);
            TestEventArgs.Should().BeNull();
        }
    }
}
