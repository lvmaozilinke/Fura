// Copyright Druid Mechanics

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Data/JRPGEnemyClassInfo.h"
#include "Engine/DataAsset.h"
#include "JRPGEnemyDataAsset.generated.h"

/**
 * 敌人的DataAsset类，用于存储敌人的属性
 */
UCLASS()
class GASJRPG_API UJRPGEnemyDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:

	// 敌人名称
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "JRPG|Enemy")
	FText EnemyName;

	//敌人等级对应的属性曲线表格
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "JRPG|Enemy")
	UCurveTable* EnemyAttributeCurveTable;

	//敌人死亡时获取的经验值
	UPROPERTY(EditDefaultsOnly, Category="JRPG|Enemy")
	FScalableFloat EnemyXPReward;
};
