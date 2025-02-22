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
	static void InitializeCharacterDefaultAttributesFromData(const UObject* WorldContextObject,
	                                                         UAbilitySystemComponent* ASC,
	                                                         TMap<FGameplayTag, float> FJRPGTagAttributesValue,
	                                                         AJRPGCharacter* Character);

	//初始化敌人类的属性数值来自曲线表格
	UFUNCTION(BlueprintCallable, Category="JRPG|AbilitySystemLibrary|EnemyClassDefaults")
	static void InitializeEnemyDefaultAttributesFromData(const UObject* WorldContextObject,
	                                                     UAbilitySystemComponent* ASC,
	                                                     TMap<FGameplayTag, float> FJRPGTagAttributesValue,
	                                                     const AJRPGEnemy* Enemy);

	//根据表格查询表格内数据并设置到角色上
	UFUNCTION(BlueprintCallable, Category="JRPG|AbilitySystemLibrary|ClassDefaults")
	static void FindUCurveTableSetAttributesValue(float Level, UCurveTable* CurveTable, UAbilitySystemComponent* ASC,
	                                              FGameplayEffectSpecHandle SpecHandle);

	/*
	 * Effect Context Getters
	 * 效果上下文获取器
	 */
	UFUNCTION(BlueprintPure, Category = "JRPG|AbilitySystemLibrary|GameplayEffects")
	static bool IsDodgedHit(const FGameplayEffectContextHandle& EffectContextHandle);

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
	UFUNCTION(BlueprintPure, Category = "JRPG|AbilitySystemLibrary|GameplayEffects")
	static bool IsCriticalHit(const FGameplayEffectContextHandle& EffectContextHandle);

	/*
	 * Effect Context Setters
	 * 效果上下文设定器
	 */

	UFUNCTION(BlueprintCallable, Category = "JRPG|AbilitySystemLibrary|GameplayEffects")
	static void SetIsDodgeHit(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle, bool bInIsDodgeHit);

	UFUNCTION(BlueprintCallable, Category = "JRPG|AbilitySystemLibrary|GameplayEffects")
	static void SetIsCriticalHit(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle, bool bInIsCriticalHit);

	UFUNCTION(BlueprintCallable, Category = "JRPG|AbilitySystemLibrary|GameplayEffects")
	static void SetIsSuccessfulDebuff(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle,
	                                  bool bInSuccessfulDebuff);

	UFUNCTION(BlueprintCallable, Category = "JRPG|AbilitySystemLibrary|GameplayEffects")
	static void SetDebuffDamage(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle, float InDamage);

	UFUNCTION(BlueprintCallable, Category = "JRPG|AbilitySystemLibrary|GameplayEffects")
	static void SetDebuffDuration(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle, float InDuration);

	UFUNCTION(BlueprintCallable, Category = "JRPG|AbilitySystemLibrary|GameplayEffects")
	static void SetDebuffFrequency(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle, float InFrequency);

	UFUNCTION(BlueprintCallable, Category = "JRPG|AbilitySystemLibrary|GameplayEffects")
	static void SetDamageType(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle,
	                          const FGameplayTag& InDamageType);

	UFUNCTION(BlueprintPure, Category = "JRPG|AbilitySystemLibrary|GameplayMechanics")
	static bool IsNotFriend(AActor* FirstActor, AActor* SecondActor);

	UFUNCTION(BlueprintCallable, Category = "JRPG|AbilitySystemLibrary|DamageEffect")
	static FGameplayEffectContextHandle ApplyDamageEffect(const FJRPGDamageEffectParams& DamageEffectParams);


	//炮弹命中后的散射角度数组？目前好像没用
	UFUNCTION(BlueprintPure, Category = "JRPG|AbilitySystemLibrary|GameplayMechanics")
	static TArray<FRotator> EvenlySpacedRotators(const FVector& Forward, const FVector& Axis, float Spread, int32 NumRotators);


	//目前猜测是击败敌人后获取敌人对应等级的经验值
	static int32 GetXPRewardForClassAndLevel(const UObject* WorldContextObject, const AJRPGEnemy* Enemy);


	/*
	* Damage Effect Params
	*/
	UFUNCTION(BlueprintCallable, Category = "AuraAbilitySystemLibrary|DamageEffect")
	static void SetTargetEffectParamsASC(UPARAM(ref) FJRPGDamageEffectParams& DamageEffectParams,
	                                     UAbilitySystemComponent* InASC);
};
