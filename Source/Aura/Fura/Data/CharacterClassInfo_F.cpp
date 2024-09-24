// Copyright Druid Mechanics


#include "CharacterClassInfo_F.h"

FCharacterClassDefaultInfo_F UCharacterClassInfo_F::GetClassDefaultInfo(ECharacterClass_F CharacterClass)
{
		return CharacterClassInformation.FindChecked(CharacterClass);
}
