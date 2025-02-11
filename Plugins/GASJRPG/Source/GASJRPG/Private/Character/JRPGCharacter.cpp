// Copyright Druid Mechanics


#include "Character/JRPGCharacter.h"

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
	const AJRPGPlayerState* PlayerState = GetPlayerState<AJRPGPlayerState>();
	check(PlayerState);
	return PlayerState->GetPlayerLevel();
}

void AJRPGCharacter::InitAbilityActorInfo()
{
	//角色添加Effect
	ApplyEffectToSelf(DefaultPrimaryAttributes, 1.f);
	ApplyEffectToSelf(DefaultSecondaryAttributes, 1.f);
	ApplyEffectToSelf(DefaultVitalAttributes, 1.f);
}
