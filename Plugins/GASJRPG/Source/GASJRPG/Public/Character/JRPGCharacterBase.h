// Copyright Druid Mechanics

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "Interaction/JRPGCombatInterface.h"
#include "JRPGCharacterBase.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;
class UGameplayEffect;
class UAnimMontage;

UCLASS()
class GASJRPG_API AJRPGCharacterBase : public ACharacter, public IAbilitySystemInterface, public IJRPGCombatInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AJRPGCharacterBase();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UAttributeSet* GetAttributeSet() const { return AttributeSet; }

	//重写死亡事件（本地的）
	virtual void Die() override;

	//多人同步的死亡事件(服务器上调用)
	UFUNCTION(NetMulticast, Reliable)
	virtual void MulticastHandleDeath();

	//蒙太奇动画攻击数组，不同的攻击tag对应不同的动画，存到结构体数组里
	UPROPERTY(EditAnywhere, Category="JRPG|Combat")
	TArray<FJRPGTaggedMontage> AttachMontages;

	//重写获取血液特效
	virtual UNiagaraSystem* GetBloodEffect_Implementation() override;

	//重写获取动画蒙太奇
	virtual FJRPGTaggedMontage GetToggedMontageByTag_Implementation(const FGameplayTag& MontageTag) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//ASC
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	//AttributeSet
	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

	//武器模型
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Combat_F")
	TObjectPtr<USkeletalMeshComponent> Weapon;


	/*
	 * 攻击相关的插槽（子弹生成起点或）
	 * 根据name找到对应的插槽位置
	 */

	//武器插槽，用于远程子弹生成位置(枪口)
	UPROPERTY(EditAnywhere, Category="Combat_F")
	FName WeaponTipSocketName;

	//左手插槽，攻击使用
	UPROPERTY(EditAnywhere, Category="Combat_F")
	FName LeftHandSocketName;

	//右手插槽，攻击使用)
	UPROPERTY(EditAnywhere, Category="Combat_F")
	FName RightHandSocketName;

	//尾巴插槽，攻击使用)
	UPROPERTY(EditAnywhere, Category="Combat_F")
	FName TailSocketName;

	//是否死亡变量
	bool bDead = false;

	//获取武器插槽对应的世界位置
	virtual FVector GetCombatSocketLocation_Implementation(const FGameplayTag& MontageTag) override;

	//获取是否死亡
	virtual bool IsDead_Implementation() override;

	//获取当前this（Actor）
	virtual AActor* GetAvatar_Implementation() override;

	//战斗蒙太奇数组
	virtual TArray<FJRPGTaggedMontage> GetAttackMontages_Implementation() override;

	//（收到伤害蒙太奇）
	virtual UAnimMontage* GetHitReactMontage_Implementation() override;

	//启动能力演员信息
	virtual void InitAbilityActorInfo();


	/*
	 * 效果GamePlayEffect
	 */
	//主要效果
	//Gameplay Effect，定义了将应用的效果。它通常是一个类或数据表，定义了效果的具体属性（如伤害、治疗、状态变化等）。
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="JRPG|Attributes")
	TSubclassOf<UGameplayEffect> DefaultPrimaryAttributes;

	//次要效果
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="JRPG|Attributes")
	TSubclassOf<UGameplayEffect> DefaultSecondaryAttributes;

	//其他效果
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="JRPG|Attributes")
	TSubclassOf<UGameplayEffect> DefaultVitalAttributes;

	//添加效果到自身（效果类，等级）：添加一个伤害效果到自身，然后根据等级计算伤害
	void ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, float level) const;

	//初始化所有效果
	virtual void InitializeDefaultAttributes() const;

	//添加角色能力
	void AddCharacterAbilities();

	//收到伤害的特效
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="JRPG|Combat")
	UNiagaraSystem* BloodEffect;

	//死亡时播放的声音
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="JRPG|Combat")
	USoundBase* DeathSound;

private:
	//初始化的角色能力数组
	UPROPERTY(EditAnywhere, Category="JRPG|Attributes")
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;

	//命中反应蒙太奇
	UPROPERTY(EditAnywhere, Category="JRPG|Combat")
	TObjectPtr<UAnimMontage> HitReactMontage;
};
