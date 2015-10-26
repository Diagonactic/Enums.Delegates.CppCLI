using System.Collections.Generic;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace EnumCppTests.Attributes

{

    public sealed class EnumTest : TestCategoryBaseAttribute
    {
        /// <summary>
        /// Gets the test category that has been applied to the test.
        /// </summary>
        /// <returns>
        /// The test category.
        /// </returns>
        public override IList<string> TestCategories => new[] { "All Functionality", "Enum Functionality" };
    }
}