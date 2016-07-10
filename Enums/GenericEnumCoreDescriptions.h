#pragma once
#include "GenericNumericEnumCore.h"

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Reflection;
using namespace System::ComponentModel;

ref class GenericNumericEnumCore;

namespace Diagonactic
{
	GenericEnumType	private ref class GenericEnumCoreDescriptions sealed : public GenericNumericEnumCore<TEnum>
	{
	private:
		static Dictionary<String^, TEnum> ^s_descriptionToEnum = gcnew Dictionary<String^, TEnum>(s_length);
		static Dictionary<TEnum, String^> ^s_enumToDescription = gcnew Dictionary<TEnum, String^>(s_length);

		static GenericEnumCoreDescriptions();

		static String^ GetDescriptionFromAttribute(String^ source);
		

	internal:	

		static String^ TryGetDescription(TEnum source);		

		static Boolean TryGetEnum(String^ source, [Out] TEnum %result);
	};
}