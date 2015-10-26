#pragma once
#include "Stdafx.h"
using namespace System;

enum UnderlyingKind : char;
ref class Util;


namespace Diagonactic
{
	
	generic<typename TEnum>
		where TEnum : IComparable, IFormattable, IConvertible, System::Enum

		private ref class GenericEnumBase abstract
		{
		protected:
			
			static TEnum s_defaultValue = TEnum();
			static Type^ s_type = TEnum::typeid;
			static UnderlyingKind s_kind = Util::GetKind(s_defaultValue);

		internal:

			static Boolean HasFlag(TEnum source, TEnum testVal)
			{
				return Util::IsFlagSet(source, testVal, s_kind);
			}

			static TEnum AddFlags(array<TEnum>^ enumFlagsToAdd, TEnum sourceEnum)
			{
				pin_ptr<TEnum> source(&sourceEnum);
				pin_ptr<array<TEnum>^> flagsToAdd(&enumFlagsToAdd);				
				switch (s_kind)
				{
					case UnderlyingKind::Int32Kind:	 return (TEnum)Enum::ToObject(s_type, Util::AddFlags<Int32>(source, flagsToAdd));
					case UnderlyingKind::Int64Kind:	 return (TEnum)Enum::ToObject(s_type, Util::AddFlags<Int64>(source, flagsToAdd));
					case UnderlyingKind::Int16Kind:	 return (TEnum)Enum::ToObject(s_type, Util::AddFlags<Int16>(source, flagsToAdd));				
					case UnderlyingKind::UInt32Kind: return (TEnum)Enum::ToObject(s_type, Util::AddFlags<UInt32>(source, flagsToAdd));
					case UnderlyingKind::UInt64Kind: return (TEnum)Enum::ToObject(s_type, Util::AddFlags<UInt64>(source, flagsToAdd));
					case UnderlyingKind::UInt16Kind: return (TEnum)Enum::ToObject(s_type, Util::AddFlags<UInt16>(source, flagsToAdd));
					case UnderlyingKind::ByteKind:   return (TEnum)Enum::ToObject(s_type, Util::AddFlags<Byte>(source, flagsToAdd));
					case UnderlyingKind::SByteKind:	 return (TEnum)Enum::ToObject(s_type, Util::AddFlags<SByte>(source, flagsToAdd));
				}
				throw gcnew Exception("This should never throw. All underlying types are represented above.");
			}

			static Boolean AreAllFlagsSet(array<TEnum>^ enumFlagsToCheck, TEnum sourceEnum)
			{
				pin_ptr<TEnum> source(&sourceEnum);
				pin_ptr<array<TEnum>^> flagsToCheck(&enumFlagsToCheck);
				switch (s_kind)
				{
				case UnderlyingKind::Int32Kind:	 return Util::AreAllFlagsSet<Int32>(source, flagsToCheck);
				case UnderlyingKind::Int64Kind:	 return Util::AreAllFlagsSet<Int64>(source, flagsToCheck);
				case UnderlyingKind::Int16Kind:	 return Util::AreAllFlagsSet<Int16>(source, flagsToCheck);
				case UnderlyingKind::UInt32Kind: return Util::AreAllFlagsSet<UInt32>(source, flagsToCheck);
				case UnderlyingKind::UInt64Kind: return Util::AreAllFlagsSet<UInt64>(source, flagsToCheck);
				case UnderlyingKind::UInt16Kind: return Util::AreAllFlagsSet<UInt16>(source, flagsToCheck);
				case UnderlyingKind::ByteKind:   return Util::AreAllFlagsSet<Byte>(source, flagsToCheck);
				case UnderlyingKind::SByteKind:	 return Util::AreAllFlagsSet<SByte>(source, flagsToCheck);
				}
				throw gcnew Exception("This should never throw. All underlying types are represented above.");
			}

			static Boolean AreAnyFlagsSet(array<TEnum>^ enumFlagsToCheck, TEnum sourceEnum)
			{
				pin_ptr<TEnum> source(&sourceEnum);
				pin_ptr<array<TEnum>^> flagsToCheck(&enumFlagsToCheck);
				switch (s_kind)
				{
				case UnderlyingKind::Int32Kind:	 return Util::AreAnyFlagsSet<Int32>(source, flagsToCheck);
				case UnderlyingKind::Int64Kind:	 return Util::AreAnyFlagsSet<Int64>(source, flagsToCheck);
				case UnderlyingKind::Int16Kind:	 return Util::AreAnyFlagsSet<Int16>(source, flagsToCheck);
				case UnderlyingKind::UInt32Kind: return Util::AreAnyFlagsSet<UInt32>(source, flagsToCheck);
				case UnderlyingKind::UInt64Kind: return Util::AreAnyFlagsSet<UInt64>(source, flagsToCheck);
				case UnderlyingKind::UInt16Kind: return Util::AreAnyFlagsSet<UInt16>(source, flagsToCheck);
				case UnderlyingKind::ByteKind:   return Util::AreAnyFlagsSet<Byte>(source, flagsToCheck);
				case UnderlyingKind::SByteKind:	 return Util::AreAnyFlagsSet<SByte>(source, flagsToCheck);
				}
				throw gcnew Exception("This should never throw. All underlying types are represented above.");
			}

			static TEnum RemoveFlags(TEnum sourceEnum, ...array<TEnum>^ enumFlagsToRemove)
			{
				pin_ptr<TEnum> source(&sourceEnum);
				pin_ptr<array<TEnum>^> flagsToRemove(&enumFlagsToRemove);
				switch (s_kind)
				{
					case UnderlyingKind::Int32Kind:  return (TEnum)Enum::ToObject(s_type, Util::RemoveFlags<Int32>(source, flagsToRemove));
					case UnderlyingKind::Int64Kind:  return (TEnum)Enum::ToObject(s_type, Util::RemoveFlags<Int64>(source, flagsToRemove));
					case UnderlyingKind::Int16Kind:  return (TEnum)Enum::ToObject(s_type, Util::RemoveFlags<Int16>(source, flagsToRemove));				
					case UnderlyingKind::UInt32Kind: return (TEnum)Enum::ToObject(s_type, Util::RemoveFlags<UInt32>(source, flagsToRemove));
					case UnderlyingKind::UInt64Kind: return (TEnum)Enum::ToObject(s_type, Util::RemoveFlags<UInt64>(source, flagsToRemove));
					case UnderlyingKind::UInt16Kind: return (TEnum)Enum::ToObject(s_type, Util::RemoveFlags<UInt16>(source, flagsToRemove));
					case UnderlyingKind::ByteKind:   return (TEnum)Enum::ToObject(s_type, Util::RemoveFlags<Byte>(source, flagsToRemove));
					case UnderlyingKind::SByteKind:  return (TEnum)Enum::ToObject(s_type, Util::RemoveFlags<SByte>(source, flagsToRemove));
				}
				throw gcnew Exception("This should never throw. All underlying types are represented above.");
			}

			static TEnum AddFlag(TEnum sourceEnum, TEnum enumFlagToAdd)
			{
				pin_ptr<TEnum> source(&sourceEnum), flagToAdd(&enumFlagToAdd);
				switch (s_kind)
				{
					case UnderlyingKind::Int32Kind:	 return (TEnum)Enum::ToObject(TEnum::typeid, Util::AddFlagTo<Int32>(source, flagToAdd));
					case UnderlyingKind::UInt32Kind: return (TEnum)Enum::ToObject(TEnum::typeid, Util::AddFlagTo<UInt32>(source, flagToAdd));				
					case UnderlyingKind::Int64Kind:  return (TEnum)Enum::ToObject(TEnum::typeid, Util::AddFlagTo<Int64>(source, flagToAdd));				
					case UnderlyingKind::UInt64Kind: return (TEnum)Enum::ToObject(TEnum::typeid, Util::AddFlagTo<UInt64>(source, flagToAdd));				
					case UnderlyingKind::Int16Kind:  return (TEnum)Enum::ToObject(TEnum::typeid, Util::AddFlagTo<Int16>(source, flagToAdd));
					case UnderlyingKind::UInt16Kind: return (TEnum)Enum::ToObject(TEnum::typeid, Util::AddFlagTo<UInt16>(source, flagToAdd));
					case UnderlyingKind::ByteKind:   return (TEnum)Enum::ToObject(TEnum::typeid, Util::AddFlagTo<Byte>(source, flagToAdd));
					case UnderlyingKind::SByteKind:  return (TEnum)Enum::ToObject(TEnum::typeid, Util::AddFlagTo<SByte>(source, flagToAdd));
				}
				throw gcnew Exception("This should never throw. All underlying types are represented above.");
			}

			static TEnum RemoveFlag(TEnum sourceEnum, TEnum enumFlagToRemove)
			{
				pin_ptr<TEnum> source(&sourceEnum), flagToRemove(&enumFlagToRemove);
				switch (s_kind)
				{
					case UnderlyingKind::Int32Kind:	 return (TEnum)Enum::ToObject(TEnum::typeid, Util::RemoveFlag<Int32>(source, flagToRemove));
					case UnderlyingKind::UInt32Kind: return (TEnum)Enum::ToObject(TEnum::typeid, Util::RemoveFlag<UInt32>(source, flagToRemove));				
					case UnderlyingKind::Int64Kind:  return (TEnum)Enum::ToObject(TEnum::typeid, Util::RemoveFlag<Int64>(source, flagToRemove));				
					case UnderlyingKind::UInt64Kind: return (TEnum)Enum::ToObject(TEnum::typeid, Util::RemoveFlag<UInt64>(source, flagToRemove));				
					case UnderlyingKind::Int16Kind:  return (TEnum)Enum::ToObject(TEnum::typeid, Util::RemoveFlag<Int16>(source, flagToRemove));
					case UnderlyingKind::UInt16Kind: return (TEnum)Enum::ToObject(TEnum::typeid, Util::RemoveFlag<UInt16>(source, flagToRemove));
					case UnderlyingKind::ByteKind:   return (TEnum)Enum::ToObject(TEnum::typeid, Util::RemoveFlag<Byte>(source, flagToRemove));
					case UnderlyingKind::SByteKind:  return (TEnum)Enum::ToObject(TEnum::typeid, Util::RemoveFlag<SByte>(source, flagToRemove));
				}
				throw gcnew Exception("This should never throw. All underlying types are represented above.");
			}
		};
}