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
	static void GiveStartupAbilities(const UObject* WorldContentObject, UAbilitySystemComponent* ASC,ECharacterClass_F CharacterClass);

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
};
