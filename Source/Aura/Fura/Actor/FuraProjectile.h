// Copyright Druid Mechanics

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "GameFramework/Actor.h"
#include "FuraProjectile.generated.h"

class UNiagaraSystem;
class USphereComponent;
class UProjectileMovementComponent;


UCLASS()
class AURA_API AFuraProjectile : public AActor
{
	GENERATED_BODY()

public:
	AFuraProjectile();

	//弹跳效果组件？
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UProjectileMovementComponent> ProjectileMovement;


	//伤害相关,meta=(ExposeOnSpawn=true):spawn时显示这个变量
	UPROPERTY(BlueprintReadWrite,meta=(ExposeOnSpawn=true))
	FGameplayEffectSpecHandle DamageEffectSpecHandle;

	
protected:
	virtual void BeginPlay() override;
	virtual void Destroyed() override;
	UFUNCTION()
	void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                     int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	//存在时间
	UPROPERTY(EditDefaultsOnly)
	float LifeSpan = 15.f;


	bool bHit = false;


	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent> Sphere;

	//命中特效
	UPROPERTY(EditAnywhere)
	TObjectPtr<UNiagaraSystem> ImpactEffect;

	//命中音效
	UPROPERTY(EditAnywhere)
	TObjectPtr<USoundBase> ImpactSound;

	//子弹在空中飞行的音效
	UPROPERTY(EditAnywhere)
	TObjectPtr<USoundBase> LoopingSound;

	UPROPERTY()
	TObjectPtr<UAudioComponent> LoopingSoundComponent;
};
