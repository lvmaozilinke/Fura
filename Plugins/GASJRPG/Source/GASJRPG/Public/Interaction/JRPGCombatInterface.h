// Copyright Druid Mechanics

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/Interface.h"
#include "JRPGCombatInterface.generated.h"

class UNiagaraSystem;
class UAnimMontage;

USTRUCT(BlueprintType)
struct FJRPGTaggedMontage
{
	GENERATED_BODY()
	//蒙太奇动画
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UAnimMontage* Montage = nullptr;
	//Montage tag
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag MontageTag;
	//Socket Tag
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag SocketTag;
	//伤害命中音效
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	USoundBase* ImpactSound = nullptr;
};

// This class does not need to be modified.
UINTERFACE(MinimalAPI, BlueprintType)
class UJRPGCombatInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 战斗相关的接口
 * 
 */
class GASJRPG_API IJRPGCombatInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual int32 GetPlayerLevel();

	//获取武器插槽位置
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	FVector GetCombatSocketLocation(const FGameplayTag& MontageTag);

	//蓝图中实现
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void UpdateFacingTarget(const FVector& TargetLocation);

	//收到命中的蒙太奇
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	UAnimMontage* GetHitReactMontage();

	//死亡
	virtual void Die() =0;

	//是否死亡
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool IsDead();

	//获取AbilitySystemComponent关联的Actor
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	AActor* GetAvatar();

	//获取攻击蒙太奇数组
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	TArray<FJRPGTaggedMontage> GetAttackMontages();
	
	//伤害流血特效
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	UNiagaraSystem* GetBloodEffect();

	//通过标签获取攻击蒙太奇
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	FJRPGTaggedMontage GetToggedMontageByTag(const FGameplayTag& MontageTag);
};
