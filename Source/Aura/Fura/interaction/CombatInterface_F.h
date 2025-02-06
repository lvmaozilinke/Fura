// Copyright Druid Mechanics

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GameplayTagContainer.h"
#include "CombatInterface_F.generated.h"

class UNiagaraSystem;
class UAnimMontage;
USTRUCT(BlueprintType)
struct FTaggedMontage_F
{
	GENERATED_BODY()
	//蒙太奇动画
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UAnimMontage* Montage = nullptr;
	//tag
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag MontageTag;
	//音效
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	USoundBase* ImpactSound = nullptr;
};


class UAnimMontage;
// This class does not need to be modified.
UINTERFACE(MinimalAPI, BlueprintType)
class UCombatInterface_F : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class AURA_API ICombatInterface_F
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual int32 GetPlayerLevel();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	FVector GetCombatSocketLocation(const FGameplayTag& MontageTag);

	//蓝图中实现，C++ 中创建
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void UpdateFacingTarget(const FVector& TargetLocation);

	//中用于声明一个可以在 C++ 中实现，但也可以由蓝图（Blueprints）在运行时重载的函数。
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	UAnimMontage* GetHitReactMontage();

	virtual void Die() =0;


	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool IsDead();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	AActor* GetAvatar();

	//声明接口：获取攻击蒙太奇集合，在实现接口的类里面实现对应功能
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	TArray<FTaggedMontage_F> GetAttackMontages();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	UNiagaraSystem* GetBloodEffect();
};
