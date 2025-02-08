// Copyright Druid Mechanics

#pragma once

#include "CoreMinimal.h"
#include "FuraDamageGameplayAbility.h"
#include "FuraGamePlayAbility.h"
#include "FuraProjectileSpell.generated.h"

class AFuraProjectile;
class UGameplayEffect;
struct FGameplayTag;

/**
 * 
 */
UCLASS()
class AURA_API UFuraProjectileSpell : public UFuraDamageGameplayAbility
{
	GENERATED_BODY()

protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	                             const FGameplayAbilityActivationInfo ActivationInfo,
	                             const FGameplayEventData* TriggerEventData) override;

	//生成子弹，传入子弹目标位置和插槽tag
	UFUNCTION(BlueprintCallable, Category="Projectile_F")
	void SpawnProjectile(const FVector& ProjectileTargetLocation,const FGameplayTag& SocketTag);

	//火球
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<AFuraProjectile> ProjectileClass;
};
