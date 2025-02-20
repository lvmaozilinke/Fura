// Copyright Druid Mechanics

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "NiagaraSystem.h"
#include "GameFramework/Character.h"
#include "Interaction/JRPGCombatInterface.h"
#include "JRPGCharacterBase.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;
class UGameplayEffect;
class UAnimMontage;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnJRPGStateChanged, int32 /*StatValue*/)
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnJRPGLevelChanged, int32 /*StatValue*/, bool /*bLevelUp*/)

UCLASS()
class GASJRPG_API AJRPGCharacterBase : public ACharacter, public IAbilitySystemInterface, public IJRPGCombatInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AJRPGCharacterBase();

	//初始化 能力系统组件
	UFUNCTION(BlueprintCallable,Category="JRPG|Character Class Default")
	virtual void Init();

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

	//设置等级
	void SetLevel(int32 InLevel);
	//设置经验值
	void SetXP(int32 InXP);
	//增加等级
	void AddToLevel(int32 InLevel);
	//增加经验值
	void AddToXP(int32 InXP);

	//获取等级
	FORCEINLINE int32 GetBaseLevel() const { return Level; }
	FORCEINLINE int32 GetXP() const { return XP; }

	//XP经验值变化委托
	FOnJRPGStateChanged OnXPChangedDelegate;
	//等级变化委托
	FOnJRPGLevelChanged OnLevelChangedDelegate;

	float GetLevel() const {return Level;}

	//等级对应的能力TMap，等级对应的能力数组，例如，10级解锁10个能力
	TMap<float, TArray<TSubclassOf<UGameplayAbility>>> LevelAbilities;
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Level：玩家等级和敌人等级，设置到Base里面
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="JRPG|Class Default")
	int32 Level = 1;
	
	//经验值(击败后获得的经验值)
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="JRPG|Class Default")
	int32 XP = 0;
	
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

	//添加效果到自身（效果类，等级）：添加一个伤害效果到自身，然后根据等级计算伤害
	void ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, float level) const;

	//初始化所有效果
	virtual void InitializeDefaultAttributes() const;

	//添加角色能力
	void AddAbilities();

	//收到伤害的特效
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="JRPG|Combat")
	UNiagaraSystem* BloodEffect;

	//死亡时播放的声音
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="JRPG|Combat")
	USoundBase* DeathSound;

	//属性初始化数组（Tag对应的默认值）
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="JRPG|Class Default")
	TMap<FGameplayTag, float> FJRPGTagAttributesValue;

private:
	//初始化的角色能力数组
	UPROPERTY(EditAnywhere, Category="JRPG|Attributes")
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;

	//命中反应蒙太奇
	UPROPERTY(EditAnywhere, Category="JRPG|Combat")
	TObjectPtr<UAnimMontage> HitReactMontage;
};
