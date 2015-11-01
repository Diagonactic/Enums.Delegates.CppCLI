#pragma once

using namespace System;
using namespace System::Runtime::Serialization;
using namespace System::Reflection;

[Extension]
public ref class Delegates abstract sealed
{
private:
	static Delegates()
	{
		
	}
public:

	/// <summary>
	/// Returns the invocation list of <paramref name="source"/>
	/// </summary>
	/// <param name="source">Any delegate (<see cref="System::Delegate"/></param>
	/// <typeparam name="TDelegate">Any delegate (<see cref="System::Delegate"/>)</typeparam>
	/// <returns></returns>
	generic <typename TDelegate> where TDelegate : System::Delegate, ICloneable, ISerializable
	[Extension] static array<TDelegate>^ GetInvokationsAsArray(TDelegate source)
	{
		if (source == nullptr) throw gcnew ArgumentNullException("source");

		array<Delegate^>^ delegates = source->GetInvocationList();
		array<TDelegate>^ tDelegates = gcnew array<TDelegate>(delegates->Length);
		delegates->CopyTo(tDelegates, 0);
		return tDelegates;
	}

	/// <summary>Creates a <typeparamref name="TDelegate"/> that represents <paramref name="targetMethod"/> static or instance method with the specified <paramref name="firstArgument"/>. </summary>
	/// <param name="firstArgument">The object to which the delegate is bound, or <see langword="null" /> to treat method as <see langword="static" />.</param>
	/// <param name="targetMethod">The <see cref="MethodInfo"/> describing the static or instance method the delegate is to represent.</param>
	/// <typeparam name="TDelegate">The type of delegate (<see cref="System::Delegate"/>) to create.</typeparam>
	/// <returns>A <typeparamref name="TDelegate"/> that represents <paramref name="targetMethod"/> static or instance method, with <paramref name="firstArgument"/>.</returns>
	generic <typename TDelegate> where TDelegate : System::Delegate, ICloneable, ISerializable
	static TDelegate CreateDelegate(Object^ firstArgument, MethodInfo^ targetMethod) //
	{
		return (TDelegate)Delegate::CreateDelegate(TDelegate::typeid, firstArgument, targetMethod);
	}

	/// <summary>Creates a <typeparamref name="TDelegate"/> that represents the specified static method of <paramref name="target"/>.</summary>
	/// <param name="target">The <see cref="Type"/> representing the class that implements <paramref name="nameOfMethod"/>.</param>
	/// <param name="nameOfMethod">The name of the <see langword="static"/> method that delegate is to represent</param>
	/// <typeparam name="TDelegate">The type of delegate (<see cref="System::Delegate"/>) to create.</typeparam>
	/// <returns>A delegate of <typeparamref name="TDelegate"/> that represents <paramref name="nameOfMethod"/> to invoke on <paramref name="target"/>.</returns>
	/// <exception cref="System::ArgumentNullException"><typeparamref name="TDelegate" /> or <paramref name="nameOfMethod" /> is <see langword="null" />.</exception>
	/// <exception cref="System::ArgumentException">
	///		<para><typeparamref name="TDelegate" /> does not derive from <see cref="System::Delegate" />.</para>
	///		<para>-or-</para>
	///		<para><paramref name="nameOfMethod" /> does not reflect a static method.</para>
	/// </exception>
	/// <exception cref="System::ExecutionEngineException"><para>The <see langword="Invoke" /> method of the <typeparamref name="TDelegate" /> delegate was not found.</para></exception>
	/// <exception cref="System::MethodAccessException"><para>The caller does not have the required permission.</para></exception>
	/// <exception cref="System::InvalidProgramException"><para>The <see langword="Invoke" /> method of the <typeparamref name="TDelegate" /> delegate was not found.</para></exception>
	/// <permission cref="System::Security::Permissions::ReflectionPermission">Requires permission to access type information. See <see cref="System::Security::Permissions::ReflectionPermissionFlag::MemberAccess" /></permission>
	generic <typename TDelegate> where TDelegate : System::Delegate, ICloneable, ISerializable
		static TDelegate CreateDelegate(Type^ target, String^ nameOfMethod)
	{
		return (TDelegate)Delegate::CreateDelegate(TDelegate::typeid, target, nameOfMethod);
	}

	/// <summary>
	/// Creates a <typeparamref name="TDelegate"/> that represents the specified static method of <paramref name="target"/> with case-sensitivity provided by <paramref name="ignoreCase"/>.
	/// </summary>
	/// <param name="target">The <see cref="Type"/> representing the class that implements <paramref name="nameOfMethod"/>.</param>
	/// <param name="nameOfMethod">The name of the <see langword="static"/> method that delegate is to represent</param>
	/// <param name="ignoreCase"><see langword="true"/> if case should be ignored; otherwise <see langword="false"/></param>
	/// <typeparam name="TDelegate">The type of delegate (<see cref="System::Delegate"/>) to create.</typeparam>
	/// <returns>A delegate of <typeparamref name="TDelegate"/> that represents <paramref name="nameOfMethod"/> to invoke on <paramref name="target"/>.</returns>
	/// <exception cref="System::ArgumentNullException"><typeparamref name="TDelegate" /> or <paramref name="nameOfMethod" /> is <see langword="null" />.</exception>
	/// <exception cref="System::ArgumentException">
	///		<para><typeparamref name="TDelegate" /> does not derive from <see cref="System::Delegate" />.</para>
	///		<para>-or-</para>
	///		<para><paramref name="nameOfMethod" /> does not reflect a static method.</para>
	/// </exception>
	/// <exception cref="System::ExecutionEngineException"><para>The <see langword="Invoke" /> method of the <typeparamref name="TDelegate" /> delegate was not found.</para></exception>
	/// <exception cref="System::MethodAccessException"><para>The caller does not have the required permission.</para></exception>
	/// <exception cref="System::InvalidProgramException"><para>The <see langword="Invoke" /> method of the <typeparamref name="TDelegate" /> delegate was not found.</para></exception>
	/// <permission cref="System::Security::Permissions::ReflectionPermission">Requires permission to access type information. See <see cref="System::Security::Permissions::ReflectionPermissionFlag::MemberAccess" /></permission>
	generic <typename TDelegate> where TDelegate : System::Delegate, ICloneable, ISerializable
		static TDelegate CreateDelegate(Type^ target, String^ nameOfMethod, Boolean ignoreCase) //
	{
		return (TDelegate)Delegate::CreateDelegate(TDelegate::typeid, target, nameOfMethod, ignoreCase);
	}

	/// <summary>
	/// Creates a <typeparamref name="TDelegate"/> that represents the specified static method of <paramref name="target"/> with case-sensitivity provided by <paramref name="ignoreCase"/>.
	/// </summary>
	/// <param name="target">The <see cref="Type"/> representing the class that implements <paramref name="nameOfMethod"/>.</param>
	/// <param name="nameOfMethod">The name of the <see langword="static"/> method that delegate is to represent</param>
	/// <param name="ignoreCase"><see langword="true"/> if case should be ignored; otherwise <see langword="false"/></param>
	/// <param name="throwOnBindFailure"><see langword="true"/> if an exception should be thrown in bind failure; otherwise <see langword="false"/></param>
	/// <typeparam name="TDelegate">The type of delegate (<see cref="System::Delegate"/>) to create.</typeparam>
	/// <returns>A delegate of <typeparamref name="TDelegate"/> that represents <paramref name="nameOfMethod"/> to invoke on <paramref name="target"/>.</returns>
	generic <typename TDelegate> where TDelegate : System::Delegate, ICloneable, ISerializable
		static TDelegate CreateDelegate(Type^ target, String^ nameOfMethod, Boolean ignoreCase, Boolean throwOnBindFailure) //
	{
		return (TDelegate)Delegate::CreateDelegate(TDelegate::typeid, target, nameOfMethod, ignoreCase, throwOnBindFailure);
	}

	/// <summary><para> Returns a new delegate with the specified static method as its invocation list.</para></summary>
	/// <typeparam name="TDelegate">The type of delegate (<see cref="System::Delegate"/>) to create.</typeparam>
	/// <param name="method">A <see cref="System::Reflection::MethodInfo" /> that reflects a static method.</param>
	/// <returns>A <see cref="System::Delegate" /> of type <typeparamref name="TDelegate" /> that invokes <paramref name="method" />.</returns>
	/// <remarks><para>
	///     <block subset="none" type="note">This method is used to dynamically create delegates that invoke static methods. To create a `
	///		delegate that invokes instance methods, see <see cref="System::Delegate::CreateDelegate(System::Type,System::Object,System::String)" />(<see cref="System::Type" />, <see cref="System::Object" />, <see cref="System::String" />).</block>
	/// </para></remarks>
	/// <exception cref="System::ArgumentNullException"><typeparamref name="TDelegate" /> or <paramref name="method" /> is <see langword="null" />.</exception>
	/// <exception cref="System::ArgumentException">
	///		<para><typeparamref name="TDelegate" /> does not derive from <see cref="System::Delegate" />.</para>
	///		<para>-or-</para>
	///		<para><paramref name="method" /> does not reflect a static method.</para>
	/// </exception>
	/// <exception cref="System::ExecutionEngineException"><para>The <see langword="Invoke" /> method of the <typeparamref name="TDelegate" /> delegate was not found.</para></exception>
	/// <exception cref="System::MethodAccessException"><para>The caller does not have the required permission.</para></exception>
	/// <exception cref="System::InvalidProgramException"><para>The <see langword="Invoke" /> method of the <typeparamref name="TDelegate" /> delegate was not found.</para></exception>
	/// <permission cref="System::Security::Permissions::ReflectionPermission">Requires permission to access type information. See <see cref="System::Security::Permissions::ReflectionPermissionFlag::MemberAccess" /></permission>
	generic <typename TDelegate> where TDelegate : System::Delegate, ICloneable, ISerializable
		static TDelegate CreateDelegate(MethodInfo^ method) //
	{
		return (TDelegate)Delegate::CreateDelegate(TDelegate::typeid, method);
	}

	/// <summary>
	/// Creates a <typeparamref name="TDelegate"/> to represent the specified static <paramref name="method"/>, with the specified behavior on failure to bind.
	/// </summary>
	/// <param name="method">The <see cref="MethodInfo"/> describing the static or instance method the delegate is to represent.</param>
	/// <param name="throwOnBindFailure"><see langword="true"/> if an exception should be thrown in bind failure; otherwise <see langword="false"/></param>
	/// <typeparam name="TDelegate">The type of delegate (<see cref="System::Delegate"/>) to create.</typeparam>
	/// <returns>A new delegate of <typeparamref name="TDelegate"/>.</returns>
	generic <typename TDelegate> where TDelegate : System::Delegate, ICloneable, ISerializable
		static TDelegate CreateDelegate(MethodInfo^ method, Boolean throwOnBindFailure) //
	{
		return (TDelegate)Delegate::CreateDelegate(TDelegate::typeid, method, throwOnBindFailure);
	}

	
	/// <summary>Creates a delegate of <typeparamref name="TDelegate"/> that represents <paramref name="nameOfMethod"/> with the specified <paramref name="firstArgument"/>.</summary>
	/// <param name="firstArgument">A <see cref="Object" /> that is the first argument of the method the delegate represents. For instance methods, it must be compatible with the instance type.</param>
	/// <param name="nameOfMethod">The name of the instance method that represented by <typeparamref name="TDelegate"/></param>
	/// <param name="ignoreCase"><see langword="true"/> if case should be ignored; otherwise <see langword="false"/></param>
	/// <typeparam name="TDelegate">Any delegate (<see cref="System::Delegate"/>)</typeparam>
	/// <returns>A delegate of <typeparamref name="TDelegate"/> that represents <paramref name="nameOfMethod"/>.</returns>
	generic <typename TDelegate> 		
		static TDelegate CreateDelegate(Object^ firstArgument, String^ nameOfMethod, Boolean ignoreCase)
	{
		return (TDelegate)Delegate::CreateDelegate(TDelegate::typeid, firstArgument, nameOfMethod, ignoreCase);
	}	

	/// <summary>Creates a delegate of <typeparamref name="TDelegate"/> that represents <paramref name="nameOfMethod"/> with the specified <paramref name="firstArgument"/>.</summary>
	/// <param name="firstArgument">A <see cref="Object" /> that is the first argument of the method the delegate represents. For instance methods, it must be compatible with the instance type.</param>
	/// <param name="nameOfMethod">The name of the instance method that represented by <typeparamref name="TDelegate"/></param>
	/// <param name="ignoreCase"><see langword="true"/> if case should be ignored; otherwise <see langword="false"/></param>
	/// <param name="throwOnBindFailure"><see langword="true"/> if an exception should be thrown in bind failure; otherwise <see langword="false"/></param>
	/// <typeparam name="TDelegate">Any delegate (<see cref="System::Delegate"/>)</typeparam>
	/// <returns>A delegate of <typeparamref name="TDelegate"/> that represents <paramref name="nameOfMethod"/>.</returns>
	generic <typename TDelegate>
		where TDelegate : System::Delegate, ICloneable, ISerializable
		static TDelegate CreateDelegate(Object^ firstArgument, String^ nameOfMethod, Boolean ignoreCase, Boolean throwOnBindFailure)
	{
		return (TDelegate)Delegate::CreateDelegate(TDelegate::typeid, firstArgument, nameOfMethod, ignoreCase, throwOnBindFailure);
	}

	/// <summary>Concatenates the invocatino list of  <paramref name="source"/> to include <paramref name="values"/>.</summary>
	/// <param name="source">The delegate (for extension method convenience)</param>
	/// <param name="values">One or more delegates to combine</param>
	/// <typeparam name="TDelegate">Any delegate (<see cref="System::Delegate"/>)</typeparam>
	/// <returns>A <typeparamref name="TDelegate"/> with <paramref name="source"/> and <paramref name="values"/> as invoker</returns>
	generic <typename TDelegate> where TDelegate : System::Delegate, ICloneable, ISerializable
	[Extension] static TDelegate CombineDelegates(TDelegate source, ...array<TDelegate>^ values)
	{
		if (values == nullptr) throw gcnew ArgumentNullException("value");
		if (values->Length == 0) return source;
		if (values->Length == 1)
			return (TDelegate)Delegate::Combine(source, values[0]);

		array<TDelegate>^ newArray = (array<TDelegate>^) Array::CreateInstance(TDelegate::typeid, values->Length + 1);
		newArray[0] = source;
		values->CopyTo(newArray, 1);
				
		return (TDelegate)Delegate::Combine(newArray);
	}

	/// <summary>Removes the last occurrence of the invocation list of <paramref name="value"/> from the invocation list of another delegate.</summary>
	/// <param name="source">The delegate to remove</param>
	/// <param name="value">The value to remove</param>
	/// <returns>A new delegate with an invocation list formed by taking the invocation list of source and removing the last occurrence of the invocation list of value, if the invocation list of value is found within the invocation list of source. Returns source if value is null or if the invocation list of value is not found within the invocation list of source. Returns a null reference if the invocation list of value is equal to the invocation list of source or if source is a null reference.</returns>
	generic <typename TDelegate> where TDelegate : System::Delegate, ICloneable, ISerializable
		[Extension] static TDelegate RemoveDelegate(TDelegate source, TDelegate value)
	{
		return (TDelegate)Delegate::Remove(source, value);
	}
};

