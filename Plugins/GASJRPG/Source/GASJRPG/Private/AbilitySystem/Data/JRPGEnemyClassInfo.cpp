// Copyright Druid Mechanics


#include "AbilitySystem/Data/JRPGEnemyClassInfo.h"

FJRPGEnemyClassDefaultInfo UJRPGEnemyClassInfo::GetClassDefaultInfo(EJRPGEnemyClass CharacterClass)
{
	return EnemyClassInformation.FindChecked(CharacterClass);
}
