// Copyright Druid Mechanics

#pragma once

#include "CoreMinimal.h"
#include "FuraGamePlayAbility.h"
#include "Aura/Fura/interaction/CombatInterface_F.h"
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

	//随机从蒙太奇动画数组中选择一个返回
	UFUNCTION(BlueprintPure)
	FTaggedMontage_F GetRandomTaggedMontageFromArray(const TArray<FTaggedMontage_F>& TaggedMontages) const;
};
