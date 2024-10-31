// Copyright Druid Mechanics

#pragma once

#include "CoreMinimal.h"
#include "Data/CharacterClassInfo_F.h"
#include "Engine/Classes/Kismet/BlueprintFunctionLibrary.h"
#include "Widget/OverlayWidgetController_F.h"
#include "AbilitySystemComponent.h"
#include "FuraAbilitySystemLibrary.generated.h"

class UAttributeMenuWidgetController_F;
/**
 * 
 */
UCLASS()
class AURA_API UFuraAbilitySystemLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category="FuraAbilitySystemLibrary|Widgetcontroller")
	static UOverlayWidgetController_F* GetOverlayWidgetController_F(const UObject* WorldContentObject);

	UFUNCTION(BlueprintPure, Category="FuraAbilitySystemLibrary|Widgetcontroller")
	static UAttributeMenuWidgetController_F* GetAttributeMenuWidgetController_F(const UObject* WorldContentObject);

	UFUNCTION(BlueprintCallable, Category="FuraAbilitySystemLibrary|CharacterClassDefaults")
	static void InitializeDefaultAttributes(const UObject* WorldContentObject, ECharacterClass_F CharacterClass,
	                                        float Level, UAbilitySystemComponent* ASC);

	//赋予能力
	UFUNCTION(BlueprintCallable, Category="FuraAbilitySystemLibrary|CharacterClassDefaults")
	static void GiveStartupAbilities(const UObject* WorldContentObject, UAbilitySystemComponent* ASC,
	                                 ECharacterClass_F CharacterClass);

	UFUNCTION(BlueprintCallable, Category="FuraAbilitySystemLibrary|CharacterClassDefaults")
	static UCharacterClassInfo_F* GetCharacterClassInfo(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, Category="FuraAbilitySystemLibrary|GameplayEffects")
	static bool IsBlockedHit(const FGameplayEffectContextHandle& EffectContextHandle);

	UFUNCTION(BlueprintPure, Category="FuraAbilitySystemLibrary|GameplayEffects")
	static bool IsCriticalHit(const FGameplayEffectContextHandle& EffectContextHandle);

	UFUNCTION(BlueprintCallable, Category="FuraAbilitySystemLibrary|GameplayEffects")
	static void SetBlockedHit(UPARAM(ref)FGameplayEffectContextHandle& EffectContextHandle, bool bInIsBlockedHit);

	UFUNCTION(BlueprintCallable, Category="FuraAbilitySystemLibrary|GameplayEffects")
	static void SetCriticalHit(UPARAM(ref)FGameplayEffectContextHandle& EffectContextHandle, bool bInIsCriticalHit);

	/*
	 * 获得半径内的玩家
	 * WorldContextObject：指向当前世界上下文的对象，通常用于在游戏世界中执行查找或操作（例如 GetWorld() 调用需要这个）。
	 * OutOverlappingActors：输出参数，用来存储在指定范围内找到的符合条件的玩家或角色（即返回值）。
	 * ActorsToIgnore：传入的数组，包含需要忽略的角色或物体（这些物体不会被检测到）。
	 * Radius：查找范围的半径，单位是 Unreal 单位（厘米），即搜索半径。
	 * SphereOrigin：用于检测的球体的中心位置（即查找范围的中心点）。
	 */
	UFUNCTION(BlueprintCallable, Category="FuraAbilitySystemLibrary|GameplayMechanics")
	static void GetLivePlayersWithinRadius(const UObject* WorldContextObject, TArray<AActor*>& OutOverlappingActors,
	                                       const TArray<AActor*>& ActorsToIgnore, float Radius,
	                                       const FVector& SphereOrigin);


	//判断FirstActor和SecondActor的Tag是否为不同（是否不是友方？）
	UFUNCTION(BlueprintPure, Category="FuraAbilitySystemLibrary|GameplayMechanics")
	static bool IsNotFriend(AActor* FirstActor, AActor* SecondActor);
};
