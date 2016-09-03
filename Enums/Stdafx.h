// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently,
// but are changed infrequently

#pragma once

#using <C:\Program Files (x86)\Reference Assemblies\Microsoft\Framework\.NETCore\v4.5\System.Linq.Dll>

#define GenericEnumTypeConstraint(name) where name : IComparable, IFormattable, IConvertible, System::Enum, value class
#define GenericEnumTypeName(name) generic <typename name> GenericEnumTypeConstraint(name)
#define GenericEnumType GenericEnumTypeName(TEnum)

// http://stackoverflow.com/questions/13872586/macro-how-do-i-change-each-value-in-va-args - variation of this

#define CommaRepeat0(textToRepeat) textToRepeat
#define CommaRepeat1(textToRepeat) textToRepeat##1, CommaRepeat0(textToRepeat)
#define CommaRepeat2(textToRepeat) textToRepeat##2, CommaRepeat1(textToRepeat)
#define CommaRepeat3(textToRepeat) textToRepeat##3, CommaRepeat2(textToRepeat)
#define CommaRepeat4(textToRepeat) textToRepeat##4, CommaRepeat3(textToRepeat)
#define CommaRepeat5(textToRepeat) textToRepeat##5, CommaRepeat4(textToRepeat)
#define CommaRepeat6(textToRepeat) textToRepeat##6, CommaRepeat5(textToRepeat)
#define CommaRepeat(numberOfTimes, textToRepeat) CommaRepeat##numberOfTimes(textToRepeat)

#define CommaRepeatTwoParams0(textLeftSideRepeat, textRightSideRepeat) textLeftSideRepeat textRightSideRepeat
#define CommaRepeatTwoParams1(textLeftSideRepeat, textRightSideRepeat) textLeftSideRepeat##1 textRightSideRepeat##1, CommaRepeatTwoParams0(textLeftSideRepeat, textRightSideRepeat)
#define CommaRepeatTwoParams2(textLeftSideRepeat, textRightSideRepeat) textLeftSideRepeat##2 textRightSideRepeat##2, CommaRepeatTwoParams1(textLeftSideRepeat, textRightSideRepeat)
#define CommaRepeatTwoParams3(textLeftSideRepeat, textRightSideRepeat) textLeftSideRepeat##3 textRightSideRepeat##3, CommaRepeatTwoParams2(textLeftSideRepeat, textRightSideRepeat)
#define CommaRepeatTwoParams4(textLeftSideRepeat, textRightSideRepeat) textLeftSideRepeat##4 textRightSideRepeat##4, CommaRepeatTwoParams3(textLeftSideRepeat, textRightSideRepeat)
#define CommaRepeatTwoParams5(textLeftSideRepeat, textRightSideRepeat) textLeftSideRepeat##5 textRightSideRepeat##5, CommaRepeatTwoParams4(textLeftSideRepeat, textRightSideRepeat)
#define CommaRepeatTwoParams6(textLeftSideRepeat, textRightSideRepeat) textLeftSideRepeat##6 textRightSideRepeat##6, CommaRepeatTwoParams5(textLeftSideRepeat, textRightSideRepeat)
#define CommaRepeatTwoParams(numberOfTimes, textLeftSideRepeat, textRightSideRepeat) CommaRepeatTwoParams##numberOfTimes(textLeftSideRepeat, textRightSideRepeat)

#define TParameterDeclaration(numberOfParameters) CommaRepeat(numberOfParameters, TParameter)
#define TypenameTParameterName typename TParameter
#define TParameterTypenameDeclaration(numberOfParameters) CommaRepeat(numberOfParameters, TypenameTParameterName)
#define TParameterIdentifierNames(numberOfParameters) CommaRepeat(numberOfParameters, param)
#define TParameterMethodParameters(numberOfParameters) CommaRepeatTwoParams(numberOfParameters, TParameter, param)
#define ThrowEnumUnderlyingValueInvalid throw gcnew Exception("This should never throw. All underlying types are represented above.");

#define EnumKind GenericEnumMinimal<TEnum>::s_kind
#define SwitchOnType(targetEnumValue, valueWithTypeParameter)		\
switch (targetEnumValue) {											\
	case UnderlyingKind::Int32Kind:									\
		valueWithTypeParameter(Int32);								\
	break;															\
	case UnderlyingKind::UInt32Kind:								\
		valueWithTypeParameter(UInt32);								\
	break;															\
	case UnderlyingKind::Int64Kind:									\
		valueWithTypeParameter(Int64);								\
	break;															\
	case UnderlyingKind::UInt64Kind:								\
		valueWithTypeParameter(UInt64);								\
	break;															\
	case UnderlyingKind::Int16Kind:									\
		valueWithTypeParameter(Int16);								\
	break;															\
	case UnderlyingKind::UInt16Kind:								\
		valueWithTypeParameter(UInt16);								\
	break;															\
	case UnderlyingKind::ByteKind:									\
		valueWithTypeParameter(Byte);								\
	break;															\
	case UnderlyingKind::SByteKind:									\
		valueWithTypeParameter(SByte);								\
	break;															\
}


