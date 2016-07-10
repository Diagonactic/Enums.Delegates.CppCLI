#include "stdafx.h"
#include "Delegates.h"

GenericEventsHelperTypes private ref class EventsHelper
{
private:

	TTargetClass m_targetClass;
	EventHandler<TEventArgs>^ m_newDelegate;
	EventHandler<TEventArgs>^ m_raiseOnce;
	EventInfo^ m_targetEvent;

public:

	EventsHelper(TTargetClass targetClass, EventInfo^ targetEvent, EventHandler<TEventArgs>^ raiseOnce) {
		m_targetClass = targetClass;
		m_raiseOnce = raiseOnce;
		m_targetEvent = targetEvent;
	}

	void RaiseOnce(Object^ sender, TEventArgs eventArgs)
	{
		m_targetEvent->RemoveEventHandler(m_targetClass, m_newDelegate);
		m_raiseOnce->Invoke(sender, eventArgs);
	}

	void SetDelegate(EventHandler<TEventArgs>^ newDelegate)
	{
		m_newDelegate = newDelegate;
	}
};

GenericEventsHelperTypes void Diagonactic::Delegates::AttachWithUnsubscribe(TTargetClass target, String ^ eventName, EventHandler<TEventArgs>^ raiseWithUnsubscribe)
{
	auto eventInfo = TTargetClass::typeid->GetEvent(eventName);
	if (eventInfo == nullptr) throw gcnew ArgumentException(String::Format("Event {0} was not found on target specified", eventName), "eventName");

	AttachWithUnsubscribe(target, eventInfo, raiseWithUnsubscribe);
}

GenericEventsHelperTypes void Diagonactic::Delegates::AttachWithUnsubscribe(TTargetClass target, EventInfo ^ targetEvent, EventHandler<TEventArgs>^ raiseWithUnsubscribe)
{
	if (targetEvent == nullptr)	throw gcnew ArgumentNullException("targetEvent");

	auto eventWrapper = gcnew EventsHelper<TTargetClass, TEventArgs>(target, targetEvent, raiseWithUnsubscribe);
	auto singleRaiseDelegate = gcnew EventHandler<TEventArgs>(eventWrapper, &EventsHelper<TTargetClass, TEventArgs>::RaiseOnce);

	eventWrapper->SetDelegate(singleRaiseDelegate);

	targetEvent->AddEventHandler(target, singleRaiseDelegate);
}

GenericTDelegateTResult[Extension]TResult Diagonactic::Delegates::ConvertTo(TDelegate source)
{
	array<Delegate^>^ invocationList = source->GetInvocationList();

	if (invocationList->Length == 0)
		throw gcnew ArgumentException("Cannot convert a delegate without invocations defined", "source");
	else if (invocationList->Length == 1)
		return safe_cast<TResult>(Delegate::CreateDelegate(TResult::typeid, invocationList[0]->Target, invocationList[0]->Method));
	else
	{
		array<TResult>^ newDelegates = safe_cast<array<TResult>^>(Array::CreateInstance(TResult::typeid, invocationList->Length));

		for (Int32 i = 0; i < invocationList->Length; i++)
			newDelegates[i] = safe_cast<TResult>(Delegate::CreateDelegate(TResult::typeid, invocationList[i]->Target, invocationList[i]->Method));

		auto retVal = safe_cast<TResult>(Delegate::Combine(invocationList));
		if (retVal == nullptr)
			throw gcnew ArgumentException("TDelegate and TResult are not compatible");

		return retVal;
	}
	if (source->GetInvocationList()->Length > 1)
		throw gcnew ArgumentException("Multicast delegates cannot safely be converted", "source");
}

GenericTDelegate TDelegate Diagonactic::Delegates::CreateDelegate(Object ^ firstArgument, MethodInfo ^ targetMethod)
{
	return (TDelegate)Delegate::CreateDelegate(TDelegate::typeid, firstArgument, targetMethod);
}

GenericTDelegate TDelegate Diagonactic::Delegates::CreateDelegate(Type ^ target, String ^ nameOfMethod)
{
	return (TDelegate)Delegate::CreateDelegate(TDelegate::typeid, target, nameOfMethod);
}

GenericTDelegate TDelegate Diagonactic::Delegates::CreateDelegate(Type ^ target, String ^ nameOfMethod, Boolean ignoreCase)
{
	return (TDelegate)Delegate::CreateDelegate(TDelegate::typeid, target, nameOfMethod, ignoreCase);
}

GenericTDelegate TDelegate Diagonactic::Delegates::CreateDelegate(Type ^ target, String ^ nameOfMethod, Boolean ignoreCase, Boolean throwOnBindFailure)
{
	return (TDelegate)Delegate::CreateDelegate(TDelegate::typeid, target, nameOfMethod, ignoreCase, throwOnBindFailure);
}

GenericTDelegate TDelegate Diagonactic::Delegates::CreateDelegate(MethodInfo ^ method) {
	return (TDelegate)Delegate::CreateDelegate(TDelegate::typeid, method);
}

GenericTDelegate TDelegate Diagonactic::Delegates::CreateDelegate(MethodInfo ^ method, Boolean throwOnBindFailure)
{
	return (TDelegate)Delegate::CreateDelegate(TDelegate::typeid, method, throwOnBindFailure);
}

GenericTDelegate TDelegate Diagonactic::Delegates::CreateDelegate(Object ^ firstArgument, String ^ nameOfMethod, Boolean ignoreCase)
{
	return (TDelegate)Delegate::CreateDelegate(TDelegate::typeid, firstArgument, nameOfMethod, ignoreCase);
}

GenericTDelegate TDelegate Diagonactic::Delegates::CreateDelegate(Object ^ firstArgument, String ^ nameOfMethod, Boolean ignoreCase, Boolean throwOnBindFailure)
{
	return (TDelegate)Delegate::CreateDelegate(TDelegate::typeid, firstArgument, nameOfMethod, ignoreCase, throwOnBindFailure);
}

GenericTDelegate[Extension]TDelegate Diagonactic::Delegates::CombineDelegates(TDelegate source, ...array<TDelegate>^ values)
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

GenericTDelegate[Extension]TDelegate Diagonactic::Delegates::RemoveDelegate(TDelegate source, TDelegate value)
{
	return (TDelegate)Delegate::Remove(source, value);
}
