// Copyright Druid Mechanics


#include "AbilitySystem/Data/JRPGCharacterClassInfo.h"

FJRPGCharacterClassDefaultInfo UJRPGCharacterClassInfo::GetClassDefaultInfo(EJRPGCharacterClass CharacterClass)
{
	return CharacterClassInformation.FindChecked(CharacterClass);
}
