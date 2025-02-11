// Copyright Druid Mechanics

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Data/JRPGCharacterClassInfo.h"
#include "AbilitySystem/Data/JRPGEnemyClassInfo.h"
#include "GameFramework/GameModeBase.h"
#include "JRPGGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class GASJRPG_API AJRPGGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	//角色类型
	UPROPERTY(EditDefaultsOnly, Category="JRPG|Character Class Defaults")
	TObjectPtr<UJRPGCharacterClassInfo> CharacterClassInfo;
	//敌人类型
	UPROPERTY(EditDefaultsOnly, Category="JRPG|Character Class Defaults")
	TObjectPtr<UJRPGEnemyClassInfo> EnemyClassInfo;

};
