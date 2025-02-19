// Copyright Druid Mechanics

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Character/JRPGCharacter.h"
#include "Character/JRPGEnemy.h"
#include "Data/JRPGCharacterClassInfo.h"
#include "Data/JRPGEnemyClassInfo.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "JRPGAbilitySystemLibrary.generated.h"

/**
 * 
 */
UCLASS()
class GASJRPG_API UJRPGAbilitySystemLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	/*
	 * Ability System Class Defaults
	 */
	
	//初始化角色类的默认属性
	UFUNCTION(BlueprintCallable, Category="JRPG|AbilitySystemLibrary|CharacterClassDefaults")
	static void InitializeCharacterDefaultAttributes(const UObject* WorldContentObject,
	                                                 EJRPGCharacterClass CharacterClass,
	                                                 float Level, UAbilitySystemComponent* ASC);
	//初始化敌人类的默认属性
	UFUNCTION(BlueprintCallable, Category="JRPG|AbilitySystemLibrary|EnemyClassDefaults")
	static void InitializeEnemyDefaultAttributes(const UObject* WorldContentObject, EJRPGEnemyClass EnemyClass,
	                                             float Level, UAbilitySystemComponent* ASC);

	//获取DataAsset存储的Character信息
	UFUNCTION(BlueprintCallable, Category="JRPG|AbilitySystemLibrary|CharacterClassDefaults")
	static UJRPGCharacterClassInfo* GetCharacterClassInfo(const UObject* WorldContextObject);


	//获取DataAsset存储的Enemy信息
	UFUNCTION(BlueprintCallable, Category="JRPG|AbilitySystemLibrary|CharacterClassDefaults")
	static UJRPGEnemyClassInfo* GetEnemyClassInfo(const UObject* WorldContextObject);


	//初始化角色类的属性数值来自曲线表格
	UFUNCTION(BlueprintCallable, Category="JRPG|AbilitySystemLibrary|CharacterClassDefaults")
	static void InitializeCharacterDefaultAttributesFromData(const UObject* WorldContextObject, UAbilitySystemComponent* ASC,
	                                        TMap<FGameplayTag, float> FJRPGTagAttributesValue,const AJRPGCharacter* Character);

	//初始化敌人类的属性数值来自曲线表格
	UFUNCTION(BlueprintCallable, Category="JRPG|AbilitySystemLibrary|EnemyClassDefaults")
	static void InitializeEnemyDefaultAttributesFromData(const UObject* WorldContextObject, UAbilitySystemComponent* ASC,
											TMap<FGameplayTag, float> FJRPGTagAttributesValue,const AJRPGEnemy* Enemy);

	//根据表格查询表格内数据并设置到角色上
	UFUNCTION(BlueprintCallable, Category="JRPG|AbilitySystemLibrary|ClassDefaults")
	static void FindUCurveTableSetAttributesValue(float Level,UCurveTable* CurveTable,UAbilitySystemComponent* ASC,FGameplayEffectSpecHandle SpecHandle);

	/*
	 * Effect Context Getters
	 * 效果上下文获取器
	 */
	UFUNCTION(BlueprintPure, Category = "JRPG|AbilitySystemLibrary|GameplayEffects")
	static bool IsBlockedHit(const FGameplayEffectContextHandle& EffectContextHandle);

	UFUNCTION(BlueprintPure, Category = "JRPG|AbilitySystemLibrary|GameplayEffects")
	static bool IsSuccessfulDebuff(const FGameplayEffectContextHandle& EffectContextHandle);

	UFUNCTION(BlueprintPure, Category = "JRPG|AbilitySystemLibrary|GameplayEffects")
	static float GetDebuffDamage(const FGameplayEffectContextHandle& EffectContextHandle);

	UFUNCTION(BlueprintPure, Category = "JRPG|AbilitySystemLibrary|GameplayEffects")
	static float GetDebuffDuration(const FGameplayEffectContextHandle& EffectContextHandle);

	UFUNCTION(BlueprintPure, Category = "JRPG|AbilitySystemLibrary|GameplayEffects")
	static float GetDebuffFrequency(const FGameplayEffectContextHandle& EffectContextHandle);

	UFUNCTION(BlueprintPure, Category = "JRPG|AbilitySystemLibrary|GameplayEffects")
	static FGameplayTag GetDamageType(const FGameplayEffectContextHandle& EffectContextHandle);

	//是否致命一击
	UFUNCTION(BlueprintPure, Category = "AuraAbilitySystemLibrary|GameplayEffects")
	static bool IsCriticalHit(const FGameplayEffectContextHandle& EffectContextHandle);

	/*
	 * Effect Context Setters
	 * 效果上下文设定器
	 */

	
	

};
