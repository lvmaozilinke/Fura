// Copyright Druid Mechanics

#pragma once

#include "CoreMinimal.h"
#include "FuraGamePlayAbility.h"
#include "FuraDamageGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UFuraDamageGameplayAbility : public UFuraGamePlayAbility
{
	GENERATED_BODY()

protected:
	//伤害值
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Damage_F")
	FScalableFloat Damage;

	//伤害效果
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> DamageEffectClass;

	UPROPERTY(EditDefaultsOnly, Category="FDamage")
	TMap<FGameplayTag, FScalableFloat> DamageTypes;
};
