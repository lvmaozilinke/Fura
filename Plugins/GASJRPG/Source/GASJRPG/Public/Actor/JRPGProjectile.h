// Copyright Druid Mechanics

#pragma once

#include "CoreMinimal.h"
#include "NiagaraSystem.h"
#include "AbilitySystem/JRPGAbilityTypes.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "JRPGProjectile.generated.h"

UCLASS()
class GASJRPG_API AJRPGProjectile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AJRPGProjectile();
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UProjectileMovementComponent> ProjectileMovement;

	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn = true))
	FJRPGDamageEffectParams DamageEffectParams;

	UPROPERTY()
	TObjectPtr<USceneComponent> HomingTargetSceneComponent;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintCallable)
	virtual void OnHit();
	virtual void Destroyed() override;
	UFUNCTION()
	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<USphereComponent> Sphere;

	bool IsValidOverlap(AActor* OtherActor);
	bool bHit = false;

	UPROPERTY()
	TObjectPtr<UAudioComponent> LoopingSoundComponent;


private:
	UPROPERTY(EditDefaultsOnly)
	float LifeSpan = 15.f;


	
	UPROPERTY(EditAnywhere)
	TObjectPtr<UNiagaraSystem> ImpactEffect;

	UPROPERTY(EditAnywhere)
	TObjectPtr<USoundBase> ImpactSound;

	UPROPERTY(EditAnywhere)
	TObjectPtr<USoundBase> LoopingSound;
};
