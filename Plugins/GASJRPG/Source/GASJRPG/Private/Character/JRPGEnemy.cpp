// Copyright Druid Mechanics


#include "Character/JRPGEnemy.h"

#include "AbilitySystem/JRPGAbilitySystemComponent.h"
#include "AbilitySystem/JRPGAbilitySystemLibrary.h"


// Sets default values
AJRPGEnemy::AJRPGEnemy()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AJRPGEnemy::Init()
{
	Super::Init();
	InitAbilityActorInfo();
	AddCharacterAbilities();
}

void AJRPGEnemy::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
}

void AJRPGEnemy::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
}

int32 AJRPGEnemy::GetPlayerLevel()
{
	return Level;
}

void AJRPGEnemy::InitializeDefaultAttributes() const
{
	UJRPGAbilitySystemLibrary::InitializeEnemyDefaultAttributes(this, EnemyClass, Level, AbilitySystemComponent);
}

void AJRPGEnemy::InitAbilityActorInfo()
{
	//敌人添加Effect
	AbilitySystemComponent->InitAbilityActorInfo(this, this);

	Cast<UJRPGAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();
	if (HasAuthority())
	{
		InitializeDefaultAttributes();
	}
}

