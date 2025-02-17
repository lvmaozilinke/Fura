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


	//
	UFUNCTION(BlueprintCallable, Category="JRPG|AbilitySystemLibrary|CharacterClassDefaults")
	static void InitializeCharacterDefaultAttributesFromData(const UObject* WorldContextObject, UAbilitySystemComponent* ASC,
	                                        TMap<FGameplayTag, float> FJRPGTagAttributesValue,const AJRPGCharacter* Character);

	//
	UFUNCTION(BlueprintCallable, Category="JRPG|AbilitySystemLibrary|EnemyClassDefaults")
	static void InitializeEnemyDefaultAttributesFromData(const UObject* WorldContextObject, UAbilitySystemComponent* ASC,
											TMap<FGameplayTag, float> FJRPGTagAttributesValue,const AJRPGEnemy* Enemy);

};
