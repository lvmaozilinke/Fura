// Copyright Druid Mechanics

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "JRPGEnemyClassInfo.generated.h"

/**
 * Enemy Class Info
 * 敌人相关
 */
class UGameplayAbility;
class UGameplayEffect;

UENUM()
enum class EJRPGEnemyClass : uint8
{
	//角色类型，每个类型不同的属性
	Hunter, // 猎人
	Warrior, // 战士
	Wrestler, // 摔跤手
	Nurse, // 护士
	Artist, // 艺术家
	Mechanic, // 机械师
};

UCLASS()
class GASJRPG_API UJRPGEnemyClassInfo : public UDataAsset
{
	GENERATED_BODY()
};
