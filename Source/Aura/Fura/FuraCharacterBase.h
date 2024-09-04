// Copyright Druid Mechanics

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "Fura/interaction/CombatInterface_F.h"
#include "GameFramework/Character.h"
#include "FuraCharacterBase.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;
class UGameplayEffect;

UCLASS(Abstract)
class AURA_API AFuraCharacterBase : public ACharacter, public IAbilitySystemInterface, public ICombatInterface_F
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFuraCharacterBase();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UAttributeSet* GetAttributeSet() const { return AttributeSet; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

	UPROPERTY(EditAnywhere, Category="FCombat")
	TObjectPtr<USkeletalMeshComponent> Weapon;

	//启动能力演员信息
	virtual void InitAbilityActorInfo();


	//主要属性
	//Gameplay Effect，定义了将应用的效果。它通常是一个类或数据表，定义了效果的具体属性（如伤害、治疗、状态变化等）。
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Attributes_f")
	TSubclassOf<UGameplayEffect> DefaultPrimaryAttributes;
	//次要属性
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Attributes_f")
	TSubclassOf<UGameplayEffect> DefaultSecondaryAttributes;

	//必不可少的
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Attributes_f")
	TSubclassOf<UGameplayEffect> DefaultVitalAttributes;

	void ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, float level) const;

	//初始化所有属性(主要加次要)
	void InitializeDefaultAttributes() const;

	//添加角色能力
	void AddCharacterAbilities();
	

private:
	
	//角色能力数组
	UPROPERTY(EditAnywhere,Category="Attributes_f")
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;
};
