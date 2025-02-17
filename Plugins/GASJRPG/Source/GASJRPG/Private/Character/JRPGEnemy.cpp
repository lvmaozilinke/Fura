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
	AddAbilities();
}

void AJRPGEnemy::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
}

void AJRPGEnemy::InitializeDefaultAttributes() const
{
	//调用函数库初始化角色属性
	//UJRPGAbilitySystemLibrary::InitializeEnemyDefaultAttributes(this, EnemyClass, Level, AbilitySystemComponent);
	UJRPGAbilitySystemLibrary::InitializeEnemyDefaultAttributesFromData(this, AbilitySystemComponent,
	                                                                    FJRPGTagAttributesValue, this);
}
