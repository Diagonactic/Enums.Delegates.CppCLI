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

        public event EventHandler<EventArgs> TestEventArgs;
        
        public event EventHandler<EventArgs> SubscribeUnsubscribe { add { } remove { } }
        
        [TestMethod, DelegateTest]
        public void TestFireOnce()
        {
            int ea = 0;
            EventHandler<EventArgs> eventWithArgs = (sender, args) => ea++;

            Delegates.AttachWithUnsubscribe(this, nameof(DelegateTests.TestEventArgs), eventWithArgs);
            //Delegates.AttachWithUnsubscribe(this, nameof(DelegateTests.TestWithoutEventArgs), eventWithoutArgs);

            TestEventArgs?.Invoke(this, null);
            TestEventArgs?.Invoke(this, null);
            TestEventArgs?.Invoke(this, null);

            ea.ShouldBeEquivalentTo(1);
            TestEventArgs.Should().BeNull();
        }
    }
}
