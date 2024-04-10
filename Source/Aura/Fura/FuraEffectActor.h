// Copyright Druid Mechanics

#pragma once

#include "CoreMinimal.h"
#include "ActiveGameplayEffectHandle.h"
#include "GameplayEffectTypes.h"
#include "FuraAbilitySystemComponent.h"
#include "GameFramework/Actor.h"
#include "FuraEffectActor.generated.h"

class UGameplayEffect;

UENUM(BlueprintType)
enum class EEffectApplicationPolicy
{
	ApplyOnOverlap,
	ApplyOnEndOverlap,
	DoNotApply
};

UENUM(BlueprintType)
enum class EEffectRemovePolicy
{
	RemoveOnEndOverlap,
	DoNotRemove
};

UCLASS()
class AURA_API AFuraEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFuraEffectActor();

	/*
	UFUNCTION()
	virtual void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	*/


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/*UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent>Sphere;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent>Mesh;*/

	UFUNCTION(BlueprintCallable)
	void ApplyEffectToTarget(AActor* TargetActor,TSubclassOf<UGameplayEffect> GameplayEffectClass);

	
	UFUNCTION(BlueprintCallable)
	void OnOverLap(AActor* TargetActor);

	
	UFUNCTION(BlueprintCallable)
	void OnEndOverLap(AActor* TargetActor);

	

	//Instant
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Applied Effects F")
	EEffectApplicationPolicy InstantEffectApplicationPolicy=EEffectApplicationPolicy::DoNotApply;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Applied Effects F")
	TSubclassOf<UGameplayEffect> InstantGameplayEffectClass;
	
	//Duration
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Applied Effects F")
	EEffectApplicationPolicy DurationEffectApplicationPolicy=EEffectApplicationPolicy::DoNotApply;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Applied Effects F")
	TSubclassOf<UGameplayEffect> DurationGameplayEffectClass;
	
	//Infinite
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Applied Effects F")
	EEffectApplicationPolicy InfiniteEffectApplicationPolicy=EEffectApplicationPolicy::DoNotApply;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Applied Effects F")
	EEffectRemovePolicy InfiniteEffectRemovePolicy=EEffectRemovePolicy::RemoveOnEndOverlap;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Applied Effects F")
	TSubclassOf<UGameplayEffect> InfiniteGameplayEffectClass;
	
	

	
	//UFuraAbilitySystemComponent* 需要指针
	TMap<FActiveGameplayEffectHandle,UAbilitySystemComponent*> ActiveEffectHandles;


	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Applied Effects F")
	float ActorLevel=1.f;


	


	
};
