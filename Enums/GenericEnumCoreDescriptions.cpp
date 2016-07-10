#include "Stdafx.h"
#include "GenericEnumCoreDescriptions.h"

#define GenericEnumCoreDescriptionsMethod(returnType) GenericEnumType returnType Diagonactic::GenericEnumCoreDescriptions<TEnum>::

GenericEnumType static Diagonactic::GenericEnumCoreDescriptions<TEnum>::GenericEnumCoreDescriptions()
{
	array<String^>^ names = GetNames();

	for (Int32 i = 0; i < s_length; i++)
	{
		TEnum value = GenericNumericEnumCore<TEnum>::s_values[i];
		String ^description = GetDescriptionFromAttribute(names[i]);
		if (description == nullptr)
			continue;
		try
		{
			s_descriptionToEnum->Add(description, value);
		}
		catch (ArgumentException^)
		{

		}
		s_enumToDescription->Add(value, description);
	}
}

GenericEnumCoreDescriptionsMethod(String^) GetDescriptionFromAttribute(String^ source)
{
	array<Object^>^ attr = (s_type)->GetField(source)->GetCustomAttributes(DescriptionAttribute::typeid, false);
	if (attr != nullptr && attr->Length > 0)
	{
		DescriptionAttribute ^descAttr = (DescriptionAttribute^)attr[0];
		return descAttr->Description;
	}
	StringBuilder^ sb = gcnew StringBuilder();

	if (String::IsNullOrWhiteSpace(source))	return source;

	if (!Char::IsUpper(source[0]))
		sb->Append(Char::ToUpperInvariant(source[0]));
	else
		sb->Append(source[0]);

	Boolean isUnderscored = source->Contains("_");

	for (Int32 i = 1; i < source->Length; i++)
	{
		if (isUnderscored)
		{
			if (source[i] == '_')
				sb->Append(" ");
			else if (source[i - 1] == '_')
			{
				if (Char::IsUpper(source[i]))
					sb->Append(source[i]);
				else
					sb->Append(Char::ToUpperInvariant(source[i]));
			}
			else
				sb->Append(Char::ToLower(source[i]));
		}
		else if (Char::IsUpper(source[i]) && !Char::IsUpper(source[i - 1]))
		{
			sb->Append(" " + source[i]);
		}
		else
		{
			sb->Append(source[i]);
		}
	}
	return sb->ToString();
}

GenericEnumCoreDescriptionsMethod(String^) TryGetDescription(TEnum source)
{
	String^ retVal;
	if (s_enumToDescription->TryGetValue(source, retVal))
		return retVal;
	return nullptr;
}

GenericEnumCoreDescriptionsMethod(Boolean) TryGetEnum(String^ source, [Out] TEnum %result)
{
	return s_descriptionToEnum->TryGetValue(source, result);
}