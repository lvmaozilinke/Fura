// Copyright Druid Mechanics

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"

#include "FuraGamePlayAbility.generated.h"

/**
 * 游戏能力
 */
UCLASS()
class AURA_API UFuraGamePlayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category="Input")
	FGameplayTag StartupInputTag;


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Damage_F")
	FScalableFloat Damage;
};
