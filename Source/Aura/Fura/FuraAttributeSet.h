// Copyright Druid Mechanics

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "FuraAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)


USTRUCT()
struct FEffectProperties_F
{
	GENERATED_BODY()
	FEffectProperties_F()
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


/**
 * 
 */
UCLASS()
class AURA_API UFuraAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UFuraAttributeSet();

	//获取生命周期复制道具
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	//预分配更改
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;

	//游戏后效果执行
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	//TMap
	//TMap<FGameplayTag,TBaseStaticDelegateInstance<FGameplayAttribute(),FDefaultDelegateUserPolicy>::FFuncPtr> TagsToAttributes;
	/*FGameplayAttribute(*)():FGameplayAttribute(*)() 是值类型，表示一个返回 FGameplayAttribute 的函数指针类型。具体来说，(*)() 表示这个函数不接受任何参数，返回一个 FGameplayAttribute 类型的值。*/
	TMap<FGameplayTag, TStaticFuncPtr<FGameplayAttribute()>> TagsToAttributes;

	/*TBaseStaticDelegateInstance 是 Unreal Engine 中的一个模板类，用于实现静态委托（即全局函数或静态成员函数的委托）。
	它的模板参数是两个：
	一个是返回类型和参数类型的函数签名，另一个是用户策略。
	这里传入的第一个模板参数是 FGameplayAttribute()，表示这个委托绑定的函数返回一个 FGameplayAttribute 对象，并且不接受任何参数。*/
	//这行代码声明了一个变量 FuncPtrPointer，它是一个指向函数的指针，这个函数返回一个 FGameplayAttribute 对象，并且不接受任何参数。这个指针用于在委托实例中存储函数地址，从而允许委托调用绑定的函数。
	//https://chatgpt.com/share/647fd815-3332-4183-acfa-38f3db444ed5
	//TBaseStaticDelegateInstance<FGameplayAttribute(),FDefaultDelegateUserPolicy>::FFuncPtr FuncPtrPointer;


	/*
	* Primary Attributes
	* 力量
	* 基本属性之一
	*/
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_Strength, Category="Primary Attributes")
	FGameplayAttributeData Strength;
	ATTRIBUTE_ACCESSORS(UFuraAttributeSet, Strength);


	//智力
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_Intelligence, Category="Primary Attributes")
	FGameplayAttributeData Intelligence;
	ATTRIBUTE_ACCESSORS(UFuraAttributeSet, Intelligence);

	//Resilience 韧性
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_Resilience, Category="Primary Attributes")
	FGameplayAttributeData Resilience;
	ATTRIBUTE_ACCESSORS(UFuraAttributeSet, Resilience);

	//活力
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_Vigor, Category="Primary Attributes")
	FGameplayAttributeData Vigor;
	ATTRIBUTE_ACCESSORS(UFuraAttributeSet, Vigor);


	/*
	* Vital Attributes
	* 重要属性
	*/

	//创建血量属性【开启网络复制】
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_HP, Category="Attribute")
	FGameplayAttributeData HP;
	ATTRIBUTE_ACCESSORS(UFuraAttributeSet, HP)

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_MaxHP, Category="Attribute")
	FGameplayAttributeData MaxHP;
	ATTRIBUTE_ACCESSORS(UFuraAttributeSet, MaxHP)

	//创建蓝量属性
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_MP, Category="Attribute")
	FGameplayAttributeData MP;
	ATTRIBUTE_ACCESSORS(UFuraAttributeSet, MP)

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_MaxMP, Category="Attribute")
	FGameplayAttributeData MaxMP;
	ATTRIBUTE_ACCESSORS(UFuraAttributeSet, MaxMP)


	/*
	* Secondary Attributes
	* 次要属性
	*/

	//盔甲
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_Armor, Category="Secondary Attributes")
	FGameplayAttributeData Armor;
	ATTRIBUTE_ACCESSORS(UFuraAttributeSet, Armor);

	//穿甲(破甲)
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_ArmorPenetration, Category="Secondary Attributes")
	FGameplayAttributeData ArmorPenetration;
	ATTRIBUTE_ACCESSORS(UFuraAttributeSet, ArmorPenetration);

	//
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_BlockChance, Category="Secondary Attributes")
	FGameplayAttributeData BlockChance;
	ATTRIBUTE_ACCESSORS(UFuraAttributeSet, BlockChance);

	//暴击率
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_CriticalHitChance, Category="Secondary Attributes")
	FGameplayAttributeData CriticalHitChance;
	ATTRIBUTE_ACCESSORS(UFuraAttributeSet, CriticalHitChance);

	//暴击伤害
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_CriticalHitDamage, Category="Secondary Attributes")
	FGameplayAttributeData CriticalHitDamage;
	ATTRIBUTE_ACCESSORS(UFuraAttributeSet, CriticalHitDamage);

	//暴击抵抗
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_CriticalHitResistance, Category="Secondary Attributes")
	FGameplayAttributeData CriticalHitResistance;
	ATTRIBUTE_ACCESSORS(UFuraAttributeSet, CriticalHitResistance);


	//
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_HpRegeneration, Category="Secondary Attributes")
	FGameplayAttributeData HpRegeneration;
	ATTRIBUTE_ACCESSORS(UFuraAttributeSet, HpRegeneration);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_MpRegeneration, Category="Secondary Attributes")
	FGameplayAttributeData MpRegeneration;
	ATTRIBUTE_ACCESSORS(UFuraAttributeSet, MpRegeneration);


	/* 
	 * Meta Attributes 元属性
	 */

	//传入的伤害
	UPROPERTY(BlueprintReadOnly,Category="Meta Attributes_F")
	FGameplayAttributeData IncomingDamage;
	ATTRIBUTE_ACCESSORS(UFuraAttributeSet,IncomingDamage)

	UFUNCTION()
	void OnRep_HP(const FGameplayAttributeData& OldHP) const;

	UFUNCTION()
	void OnRep_MaxHP(const FGameplayAttributeData& OldMaxHP) const;

	UFUNCTION()
	void OnRep_MP(const FGameplayAttributeData& OldMP) const;

	UFUNCTION()
	void OnRep_MaxMP(const FGameplayAttributeData& OldMaxMP) const;

	UFUNCTION()
	void OnRep_Strength(const FGameplayAttributeData& OldStrength) const;

	UFUNCTION()
	void OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence) const;

	UFUNCTION()
	void OnRep_Resilience(const FGameplayAttributeData& OldResilience) const;

	UFUNCTION()
	void OnRep_Vigor(const FGameplayAttributeData& OldVigor) const;

	UFUNCTION()
	void OnRep_Armor(const FGameplayAttributeData& OldArmor) const;

	UFUNCTION()
	void OnRep_ArmorPenetration(const FGameplayAttributeData& OldArmorPenetration) const;

	UFUNCTION()
	void OnRep_BlockChance(const FGameplayAttributeData& OldBlockChance) const;

	UFUNCTION()
	void OnRep_CriticalHitChance(const FGameplayAttributeData& OldCriticalHitChance) const;

	UFUNCTION()
	void OnRep_CriticalHitDamage(const FGameplayAttributeData& OldCriticalHitDamage) const;

	UFUNCTION()
	void OnRep_CriticalHitResistance(const FGameplayAttributeData& OldCriticalHitResistance) const;

	UFUNCTION()
	void OnRep_HpRegeneration(const FGameplayAttributeData& OldHpRegeneration) const;

	UFUNCTION()
	void OnRep_MpRegeneration(const FGameplayAttributeData& OldMpRegeneration) const;

private:
	void SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties_F& Props) const;

	//显示
	void ShowFloatingText(const FEffectProperties_F& Props,float Damage,bool bBlockedHit,bool bCriticalHit) const;
	
};
