// Copyright Druid Mechanics

#pragma once

#include "CoreMinimal.h"
#include "JRPGGamePlayAbility.h"
#include "AbilitySystem/JRPGAbilityTypes.h"
#include "JRPGDamageGameplayAbility.generated.h"

/**
 * Damage GameplayAbility
 */
UCLASS()
class GASJRPG_API UJRPGDamageGameplayAbility : public UJRPGGamePlayAbility
{
	GENERATED_BODY()

public:
	//造成伤害
	UFUNCTION(BlueprintCallable)
	void CauseDamage(AActor* TargetActor);

	//根据等级获取本Effect的伤害值
	UFUNCTION(BlueprintPure)
	FJRPGDamageEffectParams MakeDamageEffectParamsFromClassDefaults(
		AActor* TargetActor = nullptr)const;

	//根据等级获取本Effect的伤害值
	UFUNCTION(BlueprintPure)
	float GetDamageAtLevel() const;

protected:
	//伤害效果类
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> DamageEffectClass;
	//伤害类别
	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	FGameplayTag DamageType;
	//伤害值
	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	FScalableFloat Damage;
	//负面效果机率（类似持久火焰或毒雾）
	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	float DebuffChance = 20.f;
	//负面效果伤害
	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	float DebuffDamage = 5.f;
	//负面效果频率
	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	float DebuffFrequency = 1.f;
	//负面效果持续时间
	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	float DebuffDuration = 5.f;

	UFUNCTION(BlueprintPure)
	FJRPGTaggedMontage GetRandomTaggedMontageFromArray(const TArray<FJRPGTaggedMontage>& TaggedMontages) const;
};
