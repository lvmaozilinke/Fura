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
	FEffectProperties_F(){}

	FGameplayEffectContextHandle EffectContextHandle;
	
	UPROPERTY()
	UAbilitySystemComponent* SourceASC=nullptr;

	UPROPERTY()
	AActor* SourceAvatarActor=nullptr;

	UPROPERTY()
	AController* SourceController=nullptr;

	UPROPERTY()
	ACharacter* SourceCharacter=nullptr;

	UPROPERTY()
	UAbilitySystemComponent* TargetASC=nullptr;

	UPROPERTY()
	AActor* TargetAvatarActor=nullptr;

	UPROPERTY()
	AController* TargetController=nullptr;

	UPROPERTY()
	ACharacter* TargetCharacter=nullptr;
};

/**
 * 
 */
UCLASS()
class AURA_API UFuraAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:

	//获取生命周期复制道具
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps)const override;

	//预分配更改
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;

	//游戏后效果执行
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
	
	UFuraAttributeSet();
	
	//创建血量属性【开启网络复制】
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_HP,Category="Attribute")
	FGameplayAttributeData HP;
	ATTRIBUTE_ACCESSORS(UFuraAttributeSet, HP)
	
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_MaxHP,Category="Attribute")
	FGameplayAttributeData MaxHP;
	ATTRIBUTE_ACCESSORS(UFuraAttributeSet, MaxHP)

	//创建蓝量属性
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_MP,Category="Attribute")
	FGameplayAttributeData MP;
	ATTRIBUTE_ACCESSORS(UFuraAttributeSet, MP)

	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_MaxMP,Category="Attribute")
	FGameplayAttributeData MaxMP;
	ATTRIBUTE_ACCESSORS(UFuraAttributeSet, MaxMP)

	UFUNCTION()
	void OnRep_HP(const FGameplayAttributeData OldHP)const;
	
	UFUNCTION()
	void OnRep_MaxHP(const FGameplayAttributeData OldMaxHP)const;

	UFUNCTION()
	void OnRep_MP(const FGameplayAttributeData OldMP)const;

	UFUNCTION()
	void OnRep_MaxMP(const FGameplayAttributeData OldMaxMP)const;



private:
	void SetEffectProperties(const FGameplayEffectModCallbackData& Data,FEffectProperties_F& Props) const;
};
