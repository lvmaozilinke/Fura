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
public:

	//造成伤害
	UFUNCTION(BlueprintCallable)
	void CauseDamage(AActor* TargetActor);

protected:


	//伤害效果
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> DamageEffectClass;

	UPROPERTY(EditDefaultsOnly, Category="FDamage")
	TMap<FGameplayTag, FScalableFloat> DamageTypes;
};
