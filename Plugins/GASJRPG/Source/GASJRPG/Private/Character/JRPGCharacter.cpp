// Copyright Druid Mechanics


#include "Character/JRPGCharacter.h"

#include "AbilitySystem/JRPGAbilitySystemComponent.h"
#include "AbilitySystem/JRPGAbilitySystemLibrary.h"
#include "Player/JRPGPlayerState.h"


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
	AddCharacterAbilities();
}

void AJRPGCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
}

void AJRPGCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
}


int32 AJRPGCharacter::GetPlayerLevel()
{
	return Level;
}

void AJRPGCharacter::InitializeDefaultAttributes() const
{
	UJRPGAbilitySystemLibrary::InitializeCharacterDefaultAttributes(this, CharacterClass, Level, AbilitySystemComponent);
}

void AJRPGCharacter::InitAbilityActorInfo()
{
	//角色添加Effect
	AbilitySystemComponent->InitAbilityActorInfo(this, this);

	Cast<UJRPGAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();
	if (HasAuthority())
	{
		InitializeDefaultAttributes();
	}
	
}
