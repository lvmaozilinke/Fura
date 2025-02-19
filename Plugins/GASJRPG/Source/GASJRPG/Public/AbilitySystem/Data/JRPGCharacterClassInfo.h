// Copyright Druid Mechanics

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "JRPGCharacterClassInfo.generated.h"

/**
 * PlayerCharacterClassInfo
 * 玩家控制角色
 */

class UGameplayAbility;
class UGameplayEffect;

UENUM()
enum class EJRPGCharacterClass : uint8
{
	//角色类型，每个类型不同的属性
	Hunter, // 猎人
	Soldier, // 士兵
	Wrestler, // 摔跤手
	Nurse, // 护士
	Artist, // 艺术家
	Mechanic, // 机械师
};

USTRUCT()
struct FJRPGCharacterClassDefaultInfo
{
	GENERATED_BODY()

	//UGameplayEffect：类似buff，捕获属性后计算给出新的属性值
	//主要属性
	UPROPERTY(EditDefaultsOnly, Category = "JRPG Character Class Defaults")
	TSubclassOf<UGameplayEffect> PrimaryAttributes_SetByCaller;
	//次要属性
	UPROPERTY(EditDefaultsOnly, Category="JRPG Character Class Defaults")
	TSubclassOf<UGameplayEffect> SecondaryAttributes;
	//重要属性
	UPROPERTY(EditDefaultsOnly, Category="JRPG Character Class Defaults")
	TSubclassOf<UGameplayEffect> VitalAttributes;
	//角色能力技能数组（GameplayAbility）
	UPROPERTY(EditDefaultsOnly, Category="JRPG Character Class Defaults")
	TArray<TSubclassOf<UGameplayAbility>> CommonAttributes;
	//等级对应的属性曲线表格（不同的类型的表格成长曲线也不同）
	UPROPERTY(EditDefaultsOnly, Category="JRPG Character Class Defaults")
	UCurveTable* CharacterAttributeCurveTable;
	
};


UCLASS()
class GASJRPG_API UJRPGCharacterClassInfo : public UDataAsset
{
	GENERATED_BODY()

public:
	//角色类型对应不同的Effect和Ability能力的TMap
	UPROPERTY(EditDefaultsOnly, Category="JRPG Character Class Defaults")
	TMap<EJRPGCharacterClass, FJRPGCharacterClassDefaultInfo> CharacterClassInformation;

	//根绝角色类型返回对应的effect和ability
	FJRPGCharacterClassDefaultInfo GetClassDefaultInfo(EJRPGCharacterClass CharacterClass);

	//曲线表格，不同等级对应的护甲计算参数值（护甲值*参数值）
	UPROPERTY(EditDefaultsOnly, Category="JRPG Character Common Class Defaults|Damage")
	TObjectPtr<UCurveTable> DamageCalculationCoefficients;

	
};
