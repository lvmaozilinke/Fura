﻿// Copyright Druid Mechanics

#pragma once

#include "CoreMinimal.h"
#include "Engine/Classes/Engine/DataAsset.h"
#include "CharacterClassInfo_F.generated.h"

class UGameplayAbility;
class UGameplayEffect;

UENUM()
enum class ECharacterClass_F : uint8
{
	Elementalist,
	Warrior,
	Ranger
};

USTRUCT()
struct FCharacterClassDefaultInfo_F
{
	GENERATED_BODY()
	UPROPERTY(EditDefaultsOnly, Category="Class Defaults_F")
	TSubclassOf<UGameplayEffect> PrimaryAttributes;

	//常见属性数组，包含多个能力
	UPROPERTY(EditDefaultsOnly, Category="Class Defaults_F")
	TArray<TSubclassOf<UGameplayAbility>>CommonAttributes;

	
};


/**
 * 
 */
UCLASS()
class AURA_API UCharacterClassInfo_F : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category="Character Class Defaults_F")
	TMap<ECharacterClass_F, FCharacterClassDefaultInfo_F> CharacterClassInformation;

	UPROPERTY(EditDefaultsOnly, Category="Common Class Defaults_F")
	TSubclassOf<UGameplayEffect> SecondaryAttributes;

	UPROPERTY(EditDefaultsOnly, Category="Common Class Defaults_F")
	TSubclassOf<UGameplayEffect> VitalAttributes;


	//返回结构体
	FCharacterClassDefaultInfo_F GetClassDefaultInfo(ECharacterClass_F CharacterClass);


	//能力集合数组
	UPROPERTY(EditDefaultsOnly, Category="Common Class Defaults_F")
	TArray<TSubclassOf<UGameplayAbility>> CommonAbilities;


	//曲线表格，不同等级对应的护甲计算参数值（护甲值*参数值）
	UPROPERTY(EditDefaultsOnly, Category="Common Class Defaults_F|Damage")
	TObjectPtr<UCurveTable>DamageCalculationCoefficients;
};
