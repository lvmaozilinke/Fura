// Copyright Druid Mechanics


#include "Character/JRPGCharacter.h"
#include "AbilitySystem/JRPGAbilitySystemLibrary.h"


// Sets default values
AJRPGCharacter::AJRPGCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AJRPGCharacter::Init()
{
	Super::Init();
	InitAbilityActorInfo();
	AddAbilities();
}

void AJRPGCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
}


void AJRPGCharacter::InitializeDefaultAttributes() const
{
	//调用函数库初始化角色属性
	//UJRPGAbilitySystemLibrary::InitializeCharacterDefaultAttributes(this, CharacterClass, Level, AbilitySystemComponent);
	UJRPGAbilitySystemLibrary::InitializeCharacterDefaultAttributesFromData(
		this, AbilitySystemComponent, FJRPGTagAttributesValue, const_cast<AJRPGCharacter*>(this));
}
