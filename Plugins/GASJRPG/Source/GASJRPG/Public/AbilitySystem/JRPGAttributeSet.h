#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "JRPGAttributeSet.generated.h"

// 使用 GAS 宏，简化属性访问
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
    GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
    GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
    GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
    GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

//结构体 存储来源和目标角色的信息
USTRUCT()
struct FJRPGEffectProperties
{
	GENERATED_BODY()
	FJRPGEffectProperties()
	{
	}

	FGameplayEffectContextHandle EffectContextHandle;

	UPROPERTY()
	UAbilitySystemComponent* SourceASC = nullptr;

	UPROPERTY()
	AActor* SourceAvatarActor = nullptr;

	UPROPERTY()
	AController* SourceController = nullptr;

	UPROPERTY()
	ACharacter* SourceCharacter = nullptr;

	UPROPERTY()
	UAbilitySystemComponent* TargetASC = nullptr;

	UPROPERTY()
	AActor* TargetAvatarActor = nullptr;

	UPROPERTY()
	AController* TargetController = nullptr;

	UPROPERTY()
	ACharacter* TargetCharacter = nullptr;
};

template <class T>
using TStaticFuncPtr = typename TBaseStaticDelegateInstance<T, FDefaultDelegateUserPolicy>::FFuncPtr;


UCLASS()
class GASJRPG_API UJRPGAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UJRPGAttributeSet();

	//获取生命周期复制道具
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	//预分配更改,在属性更改之前可以设置其限制
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;

	//游戏后效果执行
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	//通过 GameplayTag 访问角色属性。
	TMap<FGameplayTag, TStaticFuncPtr<FGameplayAttribute()>> TagsToAttributes;


	// ==========【等级相关属性】==========

	/** 玩家等级 */
	UPROPERTY(BlueprintReadOnly, Category="Level", ReplicatedUsing=OnRep_Level)
	FGameplayAttributeData Level;
	ATTRIBUTE_ACCESSORS(UJRPGAttributeSet, Level)

	/** 玩家当前血量 */
	UPROPERTY(BlueprintReadOnly, Category="Health", ReplicatedUsing=OnRep_Health)
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UJRPGAttributeSet, Health)

	/** 玩家最大血量 */
	UPROPERTY(BlueprintReadOnly, Category="Health", ReplicatedUsing=OnRep_MaxHealth)
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UJRPGAttributeSet, MaxHealth)

	/** 战斗等级 */
	UPROPERTY(BlueprintReadOnly, Category="Stats", ReplicatedUsing=OnRep_CombatLevel)
	FGameplayAttributeData CombatLevel;
	ATTRIBUTE_ACCESSORS(UJRPGAttributeSet, CombatLevel)

	/** 驾驶等级 */
	UPROPERTY(BlueprintReadOnly, Category="Stats", ReplicatedUsing=OnRep_DrivingLevel)
	FGameplayAttributeData DrivingLevel;
	ATTRIBUTE_ACCESSORS(UJRPGAttributeSet, DrivingLevel)

	/** 腕力 */
	UPROPERTY(BlueprintReadOnly, Category="Stats", ReplicatedUsing=OnRep_ArmStrength)
	FGameplayAttributeData ArmStrength;
	ATTRIBUTE_ACCESSORS(UJRPGAttributeSet, ArmStrength)

	/** 体力 */
	UPROPERTY(BlueprintReadOnly, Category="Stats", ReplicatedUsing=OnRep_Stamina)
	FGameplayAttributeData Stamina;
	ATTRIBUTE_ACCESSORS(UJRPGAttributeSet, Stamina)

	/** 速度 */
	UPROPERTY(BlueprintReadOnly, Category="Stats", ReplicatedUsing=OnRep_Speed)
	FGameplayAttributeData Speed;
	ATTRIBUTE_ACCESSORS(UJRPGAttributeSet, Speed)

	/** 男子气概 */
	UPROPERTY(BlueprintReadOnly, Category="Stats", ReplicatedUsing=OnRep_Manliness)
	FGameplayAttributeData Manliness;
	ATTRIBUTE_ACCESSORS(UJRPGAttributeSet, Manliness)

	/** 伤痕 */
	UPROPERTY(BlueprintReadOnly, Category="Stats", ReplicatedUsing=OnRep_Scars)
	FGameplayAttributeData Scars;
	ATTRIBUTE_ACCESSORS(UJRPGAttributeSet, Scars)

	//暴击率
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_CriticalHitChance, Category="Secondary Attributes")
	FGameplayAttributeData CriticalHitChance;
	ATTRIBUTE_ACCESSORS(UJRPGAttributeSet, CriticalHitChance);

	//暴击伤害
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_CriticalHitDamage, Category="Secondary Attributes")
	FGameplayAttributeData CriticalHitDamage;
	ATTRIBUTE_ACCESSORS(UJRPGAttributeSet, CriticalHitDamage);

	//暴击抵抗
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_CriticalHitResistance, Category="Secondary Attributes")
	FGameplayAttributeData CriticalHitResistance;
	ATTRIBUTE_ACCESSORS(UJRPGAttributeSet, CriticalHitResistance);

	// ==========【伤害属性】==========

	/** 物理伤害 */
	UPROPERTY(BlueprintReadOnly, Category="Damage", ReplicatedUsing=OnRep_UnarmedDamage)
	FGameplayAttributeData UnarmedDamage;
	ATTRIBUTE_ACCESSORS(UJRPGAttributeSet, UnarmedDamage)

	/** 火焰伤害 */
	UPROPERTY(BlueprintReadOnly, Category="Damage", ReplicatedUsing=OnRep_FireDamage)
	FGameplayAttributeData FireDamage;
	ATTRIBUTE_ACCESSORS(UJRPGAttributeSet, FireDamage)

	/** 子弹伤害 */
	UPROPERTY(BlueprintReadOnly, Category="Damage", ReplicatedUsing=OnRep_BulletDamage)
	FGameplayAttributeData BulletDamage;
	ATTRIBUTE_ACCESSORS(UJRPGAttributeSet, BulletDamage)

	/** 冰冻伤害 */
	UPROPERTY(BlueprintReadOnly, Category="Damage", ReplicatedUsing=OnRep_IceDamage)
	FGameplayAttributeData IceDamage;
	ATTRIBUTE_ACCESSORS(UJRPGAttributeSet, IceDamage)

	/** 闪电伤害 */
	UPROPERTY(BlueprintReadOnly, Category="Damage", ReplicatedUsing=OnRep_LightningDamage)
	FGameplayAttributeData LightningDamage;
	ATTRIBUTE_ACCESSORS(UJRPGAttributeSet, LightningDamage)

	/** 音波伤害 */
	UPROPERTY(BlueprintReadOnly, Category="Damage", ReplicatedUsing=OnRep_SonicDamage)
	FGameplayAttributeData SonicDamage;
	ATTRIBUTE_ACCESSORS(UJRPGAttributeSet, SonicDamage)

	/** 毒液伤害 */
	UPROPERTY(BlueprintReadOnly, Category="Damage", ReplicatedUsing=OnRep_PoisonDamage)
	FGameplayAttributeData PoisonDamage;
	ATTRIBUTE_ACCESSORS(UJRPGAttributeSet, PoisonDamage)

	/** 光线伤害 */
	UPROPERTY(BlueprintReadOnly, Category="Damage", ReplicatedUsing=OnRep_LaserDamage)
	FGameplayAttributeData LaserDamage;
	ATTRIBUTE_ACCESSORS(UJRPGAttributeSet, LaserDamage)

	// ==========【抗性属性】==========

	/** 物理抗性 */
	UPROPERTY(BlueprintReadOnly, Category="Resistance", ReplicatedUsing=OnRep_UnarmedResistance)
	FGameplayAttributeData UnarmedResistance;
	ATTRIBUTE_ACCESSORS(UJRPGAttributeSet, UnarmedResistance)

	/** 火焰抗性 */
	UPROPERTY(BlueprintReadOnly, Category="Resistance", ReplicatedUsing=OnRep_FireResistance)
	FGameplayAttributeData FireResistance;
	ATTRIBUTE_ACCESSORS(UJRPGAttributeSet, FireResistance)

	/** 子弹抗性 */
	UPROPERTY(BlueprintReadOnly, Category="Resistance", ReplicatedUsing=OnRep_BulletResistance)
	FGameplayAttributeData BulletResistance;
	ATTRIBUTE_ACCESSORS(UJRPGAttributeSet, BulletResistance)

	/** 冰冻抗性 */
	UPROPERTY(BlueprintReadOnly, Category="Resistance", ReplicatedUsing=OnRep_IceResistance)
	FGameplayAttributeData IceResistance;
	ATTRIBUTE_ACCESSORS(UJRPGAttributeSet, IceResistance)

	/** 闪电抗性 */
	UPROPERTY(BlueprintReadOnly, Category="Resistance", ReplicatedUsing=OnRep_LightningResistance)
	FGameplayAttributeData LightningResistance;
	ATTRIBUTE_ACCESSORS(UJRPGAttributeSet, LightningResistance)

	/** 音波抗性 */
	UPROPERTY(BlueprintReadOnly, Category="Resistance", ReplicatedUsing=OnRep_SonicResistance)
	FGameplayAttributeData SonicResistance;
	ATTRIBUTE_ACCESSORS(UJRPGAttributeSet, SonicResistance)

	/** 毒液抗性 */
	UPROPERTY(BlueprintReadOnly, Category="Resistance", ReplicatedUsing=OnRep_PoisonResistance)
	FGameplayAttributeData PoisonResistance;
	ATTRIBUTE_ACCESSORS(UJRPGAttributeSet, PoisonResistance)

	/** 光线抗性 */
	UPROPERTY(BlueprintReadOnly, Category="Resistance", ReplicatedUsing=OnRep_LaserResistance)
	FGameplayAttributeData LaserResistance;
	ATTRIBUTE_ACCESSORS(UJRPGAttributeSet, LaserResistance)

	//传入的伤害
	UPROPERTY(BlueprintReadOnly, Category="Meta Attributes_JRPG")
	FGameplayAttributeData IncomingDamage;
	ATTRIBUTE_ACCESSORS(UJRPGAttributeSet, IncomingDamage)


	//对应的Rep
	// ==========【等级相关属性】==========

	/** 当玩家等级变化时触发 */
	UFUNCTION()
	void OnRep_Level(const FGameplayAttributeData& OldLevel) const;

	/** 当玩家当前血量变化时触发 */
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldHealth) const;

	/** 当玩家最大血量变化时触发 */
	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const;

	/** 当玩家战斗等级变化时触发 */
	UFUNCTION()
	void OnRep_CombatLevel(const FGameplayAttributeData& OldCombatLevel) const;

	/** 当玩家驾驶等级变化时触发 */
	UFUNCTION()
	void OnRep_DrivingLevel(const FGameplayAttributeData& OldDrivingLevel) const;

	/** 当玩家腕力变化时触发 */
	UFUNCTION()
	void OnRep_ArmStrength(const FGameplayAttributeData& OldArmStrength) const;

	/** 当玩家体力变化时触发 */
	UFUNCTION()
	void OnRep_Stamina(const FGameplayAttributeData& OldStamina) const;

	/** 当玩家速度变化时触发 */
	UFUNCTION()
	void OnRep_Speed(const FGameplayAttributeData& OldSpeed) const;

	/** 当玩家男子气概变化时触发 */
	UFUNCTION()
	void OnRep_Manliness(const FGameplayAttributeData& OldManliness) const;

	/** 当玩家伤痕变化时触发 */
	UFUNCTION()
	void OnRep_Scars(const FGameplayAttributeData& OldScars) const;

	// ==========【暴击相关属性】==========

	/** 当玩家暴击率变化时触发 */
	UFUNCTION()
	void OnRep_CriticalHitChance(const FGameplayAttributeData& OldCriticalHitChance) const;

	/** 当玩家暴击伤害变化时触发 */
	UFUNCTION()
	void OnRep_CriticalHitDamage(const FGameplayAttributeData& OldCriticalHitDamage) const;

	/** 当玩家暴击抵抗变化时触发 */
	UFUNCTION()
	void OnRep_CriticalHitResistance(const FGameplayAttributeData& OldCriticalHitResistance) const;

	// ==========【伤害属性】==========

	/** 当空手伤害变化时触发 */
	UFUNCTION()
	void OnRep_UnarmedDamage(const FGameplayAttributeData& OldUnarmedDamage) const;

	/** 当火焰伤害变化时触发 */
	UFUNCTION()
	void OnRep_FireDamage(const FGameplayAttributeData& OldFireDamage) const;

	/** 当子弹伤害变化时触发 */
	UFUNCTION()
	void OnRep_BulletDamage(const FGameplayAttributeData& OldBulletDamage) const;

	/** 当冰冻伤害变化时触发 */
	UFUNCTION()
	void OnRep_IceDamage(const FGameplayAttributeData& OldIceDamage) const;

	/** 当闪电伤害变化时触发 */
	UFUNCTION()
	void OnRep_LightningDamage(const FGameplayAttributeData& OldLightningDamage) const;

	/** 当音波伤害变化时触发 */
	UFUNCTION()
	void OnRep_SonicDamage(const FGameplayAttributeData& OldSonicDamage) const;

	/** 当毒液伤害变化时触发 */
	UFUNCTION()
	void OnRep_PoisonDamage(const FGameplayAttributeData& OldPoisonDamage) const;

	/** 当光线伤害变化时触发 */
	UFUNCTION()
	void OnRep_LaserDamage(const FGameplayAttributeData& OldLaserDamage) const;

	// ==========【抗性属性】==========

	/** 当空手抗性变化时触发 */
	UFUNCTION()
	void OnRep_UnarmedResistance(const FGameplayAttributeData& OldUnarmedResistance) const;

	/** 当火焰抗性变化时触发 */
	UFUNCTION()
	void OnRep_FireResistance(const FGameplayAttributeData& OldFireResistance) const;

	/** 当子弹抗性变化时触发 */
	UFUNCTION()
	void OnRep_BulletResistance(const FGameplayAttributeData& OldBulletResistance) const;

	/** 当冰冻抗性变化时触发 */
	UFUNCTION()
	void OnRep_IceResistance(const FGameplayAttributeData& OldIceResistance) const;

	/** 当闪电抗性变化时触发 */
	UFUNCTION()
	void OnRep_LightningResistance(const FGameplayAttributeData& OldLightningResistance) const;

	/** 当音波抗性变化时触发 */
	UFUNCTION()
	void OnRep_SonicResistance(const FGameplayAttributeData& OldSonicResistance) const;

	/** 当毒液抗性变化时触发 */
	UFUNCTION()
	void OnRep_PoisonResistance(const FGameplayAttributeData& OldPoisonResistance) const;

	/** 当光线抗性变化时触发 */
	UFUNCTION()
	void OnRep_LaserResistance(const FGameplayAttributeData& OldLaserResistance) const;

private:
	void SetEffectProperties(const FGameplayEffectModCallbackData& Data, FJRPGEffectProperties& Props) const;

	//显示
	void ShowFloatingText(const FJRPGEffectProperties& Props, float Damage, bool bBlockedHit, bool bCriticalHit) const;
};
