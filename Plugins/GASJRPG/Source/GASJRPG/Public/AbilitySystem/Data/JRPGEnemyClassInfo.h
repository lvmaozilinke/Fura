// Copyright Druid Mechanics

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ScalableFloat.h"
#include "JRPGEnemyClassInfo.generated.h"

/**
 * Enemy Class Info
 * 敌人相关,和角色有一些区别
 */
class UGameplayAbility;
class UGameplayEffect;

UENUM()
enum class EJRPGEnemyClass : uint8
{
	//敌人类型，每个类型不同的属性
	Humanoid, // 人形
	Mechanical, // 机械
	Aerial, // 天空
	Aquatic, // 海洋
	Plant, // 植物
	Beast, // 动物
	WarMachine // 战车
};

USTRUCT()
struct FJRPGEnemyClassDefaultInfo
{
	GENERATED_BODY()

	//主要属性
	UPROPERTY(EditDefaultsOnly, Category = "JRPG Enemy Class Defaults")
	TSubclassOf<UGameplayEffect> PrimaryAttributes_SetByCaller;
	//次要属性
	UPROPERTY(EditDefaultsOnly, Category="JRPG Enemy Class Defaults")
	TSubclassOf<UGameplayEffect> SecondaryAttributes;
	//重要属性
	UPROPERTY(EditDefaultsOnly, Category="JRPG Enemy Class Defaults")
	TSubclassOf<UGameplayEffect> VitalAttributes;
	//角色能力技能数组（GameplayAbility）
	UPROPERTY(EditDefaultsOnly, Category="JRPG Enemy Class Defaults")
	TArray<TSubclassOf<UGameplayAbility>> CommonAttributes;
	//等级对应的属性曲线表格（不同的类型的表格成长曲线也不同）
	UPROPERTY(EditDefaultsOnly, Category="JRPG Enemy Class Defaults")
	UCurveTable* EnemyAttributeCurveTable;
	//敌人死亡时获取的经验值
	UPROPERTY(EditDefaultsOnly, Category="JRPG Enemy Class Defaults")
	FScalableFloat EnemyXPReward;
};

UCLASS()
class GASJRPG_API UJRPGEnemyClassInfo : public UDataAsset
{
	GENERATED_BODY()

public:
	//角色类型对应不同的Effect和Ability能力的TMap
	UPROPERTY(EditDefaultsOnly, Category="JRPG Enemy Class Defaults")
	TMap<EJRPGEnemyClass, FJRPGEnemyClassDefaultInfo> EnemyClassInformation;

	//根绝角色类型返回对应的effect和ability
	FJRPGEnemyClassDefaultInfo GetClassDefaultInfo(EJRPGEnemyClass CharacterClass);

	//曲线表格，不同等级对应的护甲计算参数值（护甲值*参数值）
	UPROPERTY(EditDefaultsOnly, Category="JRPG Enemy Common Class Defaults|Damage")
	TObjectPtr<UCurveTable> DamageCalculationCoefficients;
};
